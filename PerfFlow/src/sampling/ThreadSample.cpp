#include "stdafx.h"
#include "ThreadSample.h"


PerfFlow::ThreadSample::ThreadSample() :
	_frameCount(0)
{

}


void PerfFlow::ThreadSample::setSymbolForFrame(size_t index, SymbolId symbol)
{
	assert(index < _frameCount);

	_frames[index].setSymbolId(symbol);
}


void PerfFlow::ThreadSample::push(StackFrame stackFrame)
{
	assert(_frameCount != MAX_FRAMES);
	_frames[_frameCount++] = stackFrame;
}


void PerfFlow::ThreadSample::clear()
{
	_frameCount = 0;
}
