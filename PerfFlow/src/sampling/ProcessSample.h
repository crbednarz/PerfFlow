#pragma once
#include <array>
#include "ThreadSample.h"


namespace PerfFlow
{
	

class ProcessSample
{
public:
	static const size_t MAX_THREADS = 32;

	ProcessSample();

	ThreadSample& addThread();
	void clear();

	size_t threadCount() const;


private:
	std::array<ThreadSample, MAX_THREADS> _threads;
	size_t _threadCount;
};


}


inline size_t PerfFlow::ProcessSample::threadCount() const
{
	return _threadCount;
}