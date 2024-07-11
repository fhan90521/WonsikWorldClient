#pragma once
#include "Malloc.h"
#include "MyWindow.h"
#include <utility>
template <typename T>
class GlobalObjectPool
{
private:
	inline static LONG allocatingCnt = 0;
public:

	template<typename Type, typename ...Args>
	friend Type* New(Args &&... args);
	
	template<typename Type>
	friend void Delete(Type* ptr);
	
	template<typename Type>
	friend int GetAllocatingCnt();
};

template<typename Type,typename ...Args>
Type* New(Args &&... args)
{
	Type* retP = (Type*)Malloc(sizeof(Type));
	new (retP) Type(std::forward<Args>(args)...);
	InterlockedIncrement(&GlobalObjectPool<Type>::allocatingCnt);
	return retP;
}

template<typename Type>
void Delete(Type* ptr)
{
	InterlockedDecrement(&GlobalObjectPool<Type>::allocatingCnt);
	ptr->~Type();
	Free(ptr);
}

template<typename Type>
inline int GetAllocatingCnt()
{
	return GlobalObjectPool<Type>::allocatingCnt;
}
