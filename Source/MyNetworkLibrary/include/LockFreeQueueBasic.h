#pragma once
#include "MyWindow.h"
#include"LockFreeObjectPool.h"
#include "TlsObjectPool.h"
template <typename T>
class LockFreeQueueBasic
{
private:
    union Next
    {
        struct BitPartial
        {
            LONG64 pNode : 47;
            LONG64 id : 17;
        }bitPartial;
        LONG64 entire;
    };
    struct Node
    {
        T data;
        Next next;
    };
    union Edge
    {
        struct BitPartial
        {
            LONG64 pNode : 48;
            LONG64 cnt : 16;
        }bitPartial;
        LONG64 entire=0;
    };
    SHORT _id;
    alignas(64) Edge _head;
    alignas(64) Edge _tail;
    alignas(64) LONG _size = 0;
    inline static SHORT _newId = 0;
    static TlsObjectPool<Node,false> _objectPool;
public:
    LockFreeQueueBasic()
    {
        _id = InterlockedIncrement16(&_newId);
        Node* pNode = _objectPool.Alloc();
        (pNode->next).bitPartial.id = _id;
        (pNode->next).bitPartial.pNode = NULL;
        _head.entire = (LONG64)pNode;
        _tail.entire = _head.entire;
    }
    ~LockFreeQueueBasic()
    {
        T tmp;
        while (Dequeue(&tmp));
    }
    void Enqueue(const T& inPar)
    {
        Node* pNewNode = _objectPool.Alloc();
        pNewNode->data = inPar;
        (pNewNode->next).bitPartial.id = _id;
        (pNewNode->next).bitPartial.pNode = NULL;
        
        Edge oldTail;
        Edge newTail;

        Next oldTailNext;
        Next newNext;
        newNext.entire = (LONG64)pNewNode;
        newNext.bitPartial.id = _id;
        while (true)
        {
           
            oldTail = _tail;
            oldTailNext = ((Node*)oldTail.bitPartial.pNode)->next;
            if (oldTailNext.bitPartial.pNode == NULL)
            {
                newTail.entire = (LONG64)pNewNode;
                newTail.bitPartial.cnt = oldTail.bitPartial.cnt+1;
                //oldTail dequeue �ǰ� alloc�Ǿ� nullptr�� �ʱ�ȭ�Ǽ� �ڿ� �ٴ� ��찡 ����
                if (InterlockedCompareExchange64(&((((Node*)oldTail.bitPartial.pNode)->next).entire), newNext.entire, oldTailNext.entire) == oldTailNext.entire)
                {
                    InterlockedIncrement(&_size);
                    InterlockedCompareExchange64(&_tail.entire, newTail.entire, oldTail.entire);
                    break;
                }
            }
            else
            {
                //2��° CAS�� �����ؼ� TAIL�� NEXT�� NULLPTR�� �ƴ� ��
                //tail�� �׻� �ֽ�ȭ �����־�� �Ѵ�.
                newTail.entire = oldTailNext.bitPartial.pNode;
                newTail.bitPartial.cnt = oldTail.bitPartial.cnt + 1;
                InterlockedCompareExchange64(&_tail.entire, newTail.entire, oldTail.entire);
            }
        }
    }

    bool Dequeue(T* outPar)
    {
        int size = InterlockedDecrement(&_size);
        if(size < 0)
        {
            InterlockedIncrement(&_size);
            return false;
        }

        Edge oldHead;
        Edge newHead;
        Edge oldTail;
        Edge newTail;

        Next oldHeadNext;
        Next oldTailNext;
        while (1)
        {
            oldHead = _head;
            oldHeadNext = ((Node*)oldHead.bitPartial.pNode)->next;
            oldTail = _tail;
            oldTailNext = ((Node*)oldTail.bitPartial.pNode)->next;
           
       
            // tail�� �׻� �ֽ�ȭ ���� head�� tail�ڷ� �� �Ѿ�� �Ѵ� tail�� head���� ���߿� load�ؾ� tail�� head�� ���Ͽ� �׻� �� �ֽ�ȭ�Ǿ� ���� �� �ִ�
            if (oldTailNext.bitPartial.pNode != NULL)
            {
                newTail.entire = oldTailNext.bitPartial.pNode;
                newTail.bitPartial.cnt = oldTail.bitPartial.cnt + 1;
                InterlockedCompareExchange64(&_tail.entire, newTail.entire, oldTail.entire);
                continue;
            }

            if (oldHeadNext.bitPartial.pNode == NULL)
            {
                //case 1 oldHead�� �ٸ� �����忡 ���� dequeue �ǰ� alloc�Ǿ� pNext�� �ʱ�ȭ�� ��Ȳ
                //case 2 �ڿ� ������ ���� enqueue �Ǿ� size!=0������ ���� ������ �ȵȰ�� [] []->[]->[]
                continue;
            }

            newHead.entire = oldHeadNext.bitPartial.pNode;
            newHead.bitPartial.cnt = oldHead.bitPartial.cnt+1;
                
            *outPar = ((Node*)oldHeadNext.bitPartial.pNode)->data;
            if (InterlockedCompareExchange64(&_head.entire, newHead.entire, oldHead.entire) == oldHead.entire)
            {
                //�̻��̿��� newHead(pOldHeadpNext)�� dequeu enqueue�Ǹ鼭 pOldHeadpNext data�� �������.
                //outPar = pOldHeadpNext->data;
                _objectPool.Free((Node*)oldHead.bitPartial.pNode);
                break;
            }
            
        }
        return true;
    }
    
    LONG Size()
    {
        return _size;
    }
};
template<typename T>
TlsObjectPool<typename LockFreeQueueBasic<T>::Node, false> LockFreeQueueBasic<T>::_objectPool;