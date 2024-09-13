#pragma once
#include "Job.h"
//#include "LockQueue.h"
#include "MPSCQueue.h"
#include <memory>
#include "MyNew.h"
#include "MyStlContainer.h"
class JobQueue : public std::enable_shared_from_this<JobQueue>
{
private:
	friend class IOCPServer;
	friend class WorkThreadPool;
	HANDLE _hCompletionPort;
	MPSCQueue<Job*> _jobQueue;
	char _bProcessing = false;
	SharedPtr<JobQueue> _selfPtr;
	LONG _processedJobCnt = 0;
	ULONG64 _currentTime = 0;
	void ProcessJob();
protected:
	ULONG64 GetCurTime()
	{
		return _currentTime;
	}
	bool GetPopAuthority();
	virtual ~JobQueue();
	JobQueue(HANDLE hCompletionPort = NULL) :_hCompletionPort(hCompletionPort) {};
	void PostJob();
public:
	void DoAsync(CallbackType&& callback)
	{
		_jobQueue.Enqueue(New<Job>(std::move(callback)));
		if (GetPopAuthority() == true)
		{
			PostJob();
		}
	}
	template<typename T, typename Ret, typename... Params, typename... Args>
	void DoAsync(Ret(T::* memFunc)(Params...), Args&&... args)
	{
		_jobQueue.Enqueue(New<Job>((T*)this, memFunc, std::forward<Args>(args)...));
		if (GetPopAuthority() == true)
		{
			PostJob();
		}
	}
	int GetProcessedJobCnt();
	size_t GetJobQueueLen();
	// Client��
	template<typename T, typename Ret, typename... Params, typename... Args>
	void PushJob(Ret(T::* memFunc)(Params...), Args&&... args)
	{
		_jobQueue.Enqueue(New<Job>((T*)this, memFunc, std::forward<Args>(args)...));
	}
	bool PopJob(Job** pJob)
	{
		return _jobQueue.Dequeue(pJob);
	}
};