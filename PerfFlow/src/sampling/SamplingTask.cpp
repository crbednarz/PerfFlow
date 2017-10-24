#include "stdafx.h"
#include "SamplingTask.h"


PerfFlow::SamplingTask::SamplingTask(std::unique_ptr<ISampler> sampler, std::shared_ptr<SamplerOutputQueue> outputQueue) :
	_sampler(std::move(sampler)),
	_outputQueue(outputQueue),
	_shouldEnd(false),
	_isThreadRunning(false)
{
	assert(_sampler != nullptr);
	assert(_outputQueue != nullptr);
}


void PerfFlow::SamplingTask::begin()
{
	assert(!_isThreadRunning);

	_samplingThread = std::thread([this]()
	{
		while (!_shouldEnd)
		{
			if (!_outputQueue->hasWorkingSample())
				continue;
			_sampler->sample(_outputQueue->workingSample());
			_outputQueue->commit();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		_shouldEnd = false;
		_isThreadRunning = false;
	});

	_samplingThread.detach();
}


void PerfFlow::SamplingTask::end()
{
	assert(_isThreadRunning);

	_shouldEnd = true;
	waitForThreadShutdown();
}


void PerfFlow::SamplingTask::waitForThreadShutdown() const
{
	while (_isThreadRunning)
	{
		// Wait for thread to finish.
	}
}
