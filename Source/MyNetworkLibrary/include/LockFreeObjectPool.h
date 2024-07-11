#pragma once
#include "MyWindow.h"
#include <utility>
template <typename T ,bool _bPlacementNew>
class LockFreeObjectPool
{
private:
	union Top
	{
		struct BitPartial
		{
			LONG64 pTopNode : 47;
			LONG64 cnt : 17;
		}bitPartial;
		LONG64 entire = NULL;
	};
	struct Node
	{
		T data;
		Node* pNext = nullptr;
	};
	alignas(64)Top _top;
public:
	LockFreeObjectPool() {};
	virtual	~LockFreeObjectPool() 
	{
		Node* pNode = (Node*)(_top.bitPartial.pTopNode);
		while (pNode)
		{
			T* pData = (T*)pNode;
			if constexpr (_bPlacementNew==false)
			{
				pData->~T();
			}

			Node* pDelete = pNode;
			pNode = pNode->pNext;
			_aligned_free(pDelete);
		}
	};
	//�������� ���ø��� ���ڸ� void�� �Ҷ� rep stos byte ptr [rdi] �������� �Ҵ����ִ� �ּҸ� 0���� �о��ִµ�
	//�̰� ������ť���� �ΰ��̻��� �����尡 �Ҵ����ִ� �ּҿ� ���⸦ �õ��� ��  byte������ mov�� �ؼ� ������ ����ų �� �ִ�. 
	template<typename... Args>
	T* Alloc(Args&&... args)
	{
		Node* pNode = nullptr;
		Top oldTop;
		Top newTop;
		while (1)
		{
			oldTop.entire = _top.entire;
			if (oldTop.bitPartial.pTopNode == NULL)
			{
				pNode = (Node*)_aligned_malloc(sizeof(Node),16);
				new (pNode)T(std::forward<Args>(args)...);
				return (T*)pNode;
			}
			newTop.entire = (LONG64)(((Node*)(oldTop.bitPartial.pTopNode))->pNext);
			newTop.bitPartial.cnt = oldTop.bitPartial.cnt + 1;
			if (InterlockedCompareExchange64(&_top.entire, newTop.entire, oldTop.entire) == oldTop.entire)
			{
				break;
			}
		}
		pNode = (Node*)oldTop.bitPartial.pTopNode;
		if constexpr (_bPlacementNew)
		{
			new (pNode)T(std::forward<Args>(args)...);
		}
		return (T*)pNode;
	}
	T* Alloc(void)
	{
		Node* pNode = nullptr;
		Top oldTop;
		Top newTop;
		while (1)
		{
			oldTop.entire = _top.entire;
			if (oldTop.bitPartial.pTopNode == NULL)
			{
				pNode = (Node*)_aligned_malloc(sizeof(Node),16);
				new (pNode)T;
				return (T*)pNode;
			}
			newTop.entire = (LONG64)(((Node*)(oldTop.bitPartial.pTopNode))->pNext);
			newTop.bitPartial.cnt = oldTop.bitPartial.cnt + 1;
			if (InterlockedCompareExchange64(&_top.entire, newTop.entire, oldTop.entire) == oldTop.entire)
			{
				break;
			}
		}
		pNode = (Node*)oldTop.bitPartial.pTopNode;
		if constexpr (_bPlacementNew)
		{
			new (pNode)T;
		}
		return (T*)pNode;
	}

	bool Free(T* pData)
	{
		if constexpr (_bPlacementNew)
		{
			pData->~T();
		}
		Node* pNode = (Node*)pData;
		Top oldTop;
		Top newTop;
		newTop.entire = (LONG64)pData;
		while (1)
		{
			oldTop.entire = _top.entire;
			pNode->pNext = (Node*)(oldTop.bitPartial.pTopNode);
			newTop.bitPartial.cnt = oldTop.bitPartial.cnt + 1;
			if (InterlockedCompareExchange64(&_top.entire, newTop.entire, oldTop.entire) == oldTop.entire)
			{
				break;
			}
		}
		return true;
	}
};






