#include "stdafx.h"
#include "ThreadSample.h"


PerfFlow::ThreadSample::ThreadSample() :
	_frameCount(0)
{

}


void PerfFlow::ThreadSample::push(StackFrame stackFrame)
{
	_frames[_frameCount++] = stackFrame;
}
