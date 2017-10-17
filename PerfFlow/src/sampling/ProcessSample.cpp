#include "stdafx.h"
#include "ProcessSample.h"


PerfFlow::ProcessSample::ProcessSample() :
	_threadCount(0)
{
}


PerfFlow::ThreadSample& PerfFlow::ProcessSample::addThread()
{
	return _threads[_threadCount++];
}


void PerfFlow::ProcessSample::clear()
{
	for (auto i = 0; i < _threadCount; i++)
		_threads[i].clear();

	_threadCount = 0;
}


const PerfFlow::ThreadSample& PerfFlow::ProcessSample::getThread(size_t index) const
{
	assert(index < _threadCount);
	return _threads[index];
}
