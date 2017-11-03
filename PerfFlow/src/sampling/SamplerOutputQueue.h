#pragma once
#include <vector>
#include "ProcessSample.h"
#include <atomic>


namespace PerfFlow
{
	
/// Queue for ProcessSamples where producer and consumer may be different threads from one another
class SamplerOutputQueue
{
public:
	explicit SamplerOutputQueue(size_t capacity);


	/// Returns true if there is enough space left in the queue to allow for a working sample.
	bool hasWorkingSample() const;

	/// Returns reference to a the next sample to be committed. Call hasWorkingSample() before using.
	ProcessSample& workingSample();
	
	/// Pushes working sample onto the bottom of the queue.
	void commit();
	

	/// Checks if there is any samples in the queue to peek.
	bool canPeek() const;

	/// Returns reference to the sample at the top of the queue.
	const ProcessSample& peek() const;

	/// Consumes top sample of the queue.
	void pop();

	size_t capacity() const;

private:
	std::vector<ProcessSample> _samples;

	/// The oldest in-use index.
	std::atomic<uint32_t> _top;

	/// The next available index
	std::atomic<uint32_t> _bottom;

	uint32_t nextListIndex(uint32_t index) const;

};


}
