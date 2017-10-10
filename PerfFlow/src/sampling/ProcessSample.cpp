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
