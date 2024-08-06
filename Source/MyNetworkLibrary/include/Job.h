#pragma once
#include <memory>
#include <functional>
using CallbackType = std::function<void()>;
class Job
{
public:
	virtual ~Job() {};
	Job(CallbackType&& callback) : _callback(std::move(callback))
	{
	}
	template<typename T, typename Ret, typename... Args>
	Job(T* owner, Ret(T::* memFunc)(Args...),const Args&... args)
	{
		_callback = [owner, memFunc, args...]()
		{
			(owner->*memFunc)(args...);
		};
	}
	void Execute()
	{
		_callback();
	}
private:
	CallbackType _callback;
};