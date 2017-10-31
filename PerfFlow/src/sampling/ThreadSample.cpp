#include "stdafx.h"
#include "ThreadSample.h"


PerfFlow::ThreadSample::ThreadSample() :
	_frameCount(0)
{

}


void PerfFlow::ThreadSample::push(StackFrame stackFrame)
{
	assert(_frameCount != MaxFrames);
	_frames[_frameCount++] = stackFrame;
}


void PerfFlow::ThreadSample::clear()
{
	_frameCount = 0;
}
