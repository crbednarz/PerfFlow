#include "stdafx.h"
#include "SamplerOutputQueue.h"


PerfFlow::SamplerOutputQueue::SamplerOutputQueue(size_t capacity) :
	_samples(capacity + 1, ProcessSample()),
	_head(0),
	_tail(0)
{

}


bool PerfFlow::SamplerOutputQueue::tryEnqueue(const ProcessSample& sample)
{
	auto nextHead = nextListIndex(_head);
	if (nextHead == _tail)
		return false;

	_samples[_head] = sample;
	_head = nextHead;

	return true;
}


bool PerfFlow::SamplerOutputQueue::tryDequeue(ProcessSample& outputSample)
{
	if (_tail == _head)
		return false;

	outputSample = _samples[_tail];

	_tail = nextListIndex(_tail);

	return true;
}


size_t PerfFlow::SamplerOutputQueue::capacity() const
{
	return _samples.size() - 1;
}


uint32_t PerfFlow::SamplerOutputQueue::nextListIndex(uint32_t index) const
{
	return (index + 1) % _samples.size();
}


