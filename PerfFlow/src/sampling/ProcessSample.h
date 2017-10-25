#pragma once
#include <array>
#include "ThreadSample.h"


namespace PerfFlow
{
	

class ProcessSample
{
public:
	static const size_t MaxThreads = 64;

	ProcessSample();

	ThreadSample& addThread();
	void clear();

	size_t threadCount() const;
	const ThreadSample& getThread(size_t index) const;


private:
	std::array<ThreadSample, MaxThreads> _threads;
	size_t _threadCount;
};


}


inline size_t PerfFlow::ProcessSample::threadCount() const
{
	return _threadCount;
}