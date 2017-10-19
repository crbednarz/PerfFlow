#pragma once
#include <memory>
#include "ISampler.h"
#include "SamplerOutputQueue.h"
#include <thread>


namespace PerfFlow
{
	

class SamplingTask
{
public:
	SamplingTask(std::unique_ptr<ISampler> sampler, std::shared_ptr<SamplerOutputQueue> outputQueue);

	void begin();
	void end();

private:
	std::unique_ptr<ISampler> _sampler;
	std::shared_ptr<SamplerOutputQueue> _outputQueue;
	volatile bool _shouldEnd;
	volatile bool _isThreadRunning;
	std::thread _samplingThread;

	void waitForThreadShutdown() const;
};


}
