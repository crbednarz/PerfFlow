#pragma once
#include <array>
#include "ThreadSample.h"


namespace PerfFlow
{
	

class ProcessSample
{
public:


private:
	static const size_t MAX_THREADS = 32;
	std::array<ThreadSample, MAX_THREADS> _threads;
};


}
