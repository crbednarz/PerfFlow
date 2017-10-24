#include "stdafx.h"
#include "SamplerOutputQueue.h"


PerfFlow::SamplerOutputQueue::SamplerOutputQueue(size_t capacity) :
	_samples(capacity + 1, ProcessSample()),
	_top(0),
	_bottom(0)
{

}


bool PerfFlow::SamplerOutputQueue::hasWorkingSample() const
{
	return nextListIndex(_bottom) != _top;
}


PerfFlow::ProcessSample& PerfFlow::SamplerOutputQueue::workingSample()
{
	assert(hasWorkingSample());
	return _samples[_bottom];
}


void PerfFlow::SamplerOutputQueue::commit()
{
	assert(hasWorkingSample());
	_bottom = nextListIndex(_bottom);
}


bool PerfFlow::SamplerOutputQueue::canPeek() const
{
	return _top != _bottom;
}


const PerfFlow::ProcessSample& PerfFlow::SamplerOutputQueue::peek() const
{
	assert(canPeek());
	return _samples[_top];
}


void PerfFlow::SamplerOutputQueue::pop()
{
	assert(canPeek());
	_samples[_top].clear();
	_top = nextListIndex(_top);
}


size_t PerfFlow::SamplerOutputQueue::capacity() const
{
	return _samples.size() - 1;
}


uint32_t PerfFlow::SamplerOutputQueue::nextListIndex(uint32_t index) const
{
	return (index + 1) % _samples.size();
}


