#pragma once
#include "MyWindow.h"
class SpinLock
{
private:
	CHAR _lock=false;
public:
	void Acquire()
	{
		while (1)
		{
			if (_lock == false)
			{
				if (InterlockedExchange8(&_lock, true) == false)
				{
					break;
				}
			}
			YieldProcessor();
		}
	}
	void Release()
	{
		_lock = false;
	}
};