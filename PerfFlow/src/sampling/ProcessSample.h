#pragma once
#include <array>
#include "ThreadSample.h"


namespace PerfFlow
{
	

class ProcessSample
{
public:
	ProcessSample();

	ThreadSample& addThread();

private:
	static const size_t MAX_THREADS = 32;
	std::array<ThreadSample, MAX_THREADS> _threads;
	size_t _threadCount;
};


}
