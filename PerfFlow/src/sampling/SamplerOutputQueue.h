#pragma once
#include <vector>
#include "ProcessSample.h"


namespace PerfFlow
{
	

class SamplerOutputQueue
{
public:
	explicit SamplerOutputQueue(size_t capacity);

	bool tryEnqueue(const ProcessSample& sample);
	bool tryDequeue(ProcessSample& outputSample);

	size_t capacity() const;

private:
	std::vector<ProcessSample> _samples;

	/// The next available index
	volatile uint32_t _head;

	/// The oldest in-use index.
	volatile uint32_t _tail;

	uint32_t nextListIndex(uint32_t index) const;

};


}
