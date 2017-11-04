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
	~SamplingTask();

	SamplingTask(const SamplingTask& other) = default;
	SamplingTask(SamplingTask&& other) = default;
	SamplingTask& operator=(const SamplingTask& other) = default;
	SamplingTask& operator=(SamplingTask&& other) = default;

	void begin();
	void end();

private:
	std::unique_ptr<ISampler> _sampler;
	std::shared_ptr<SamplerOutputQueue> _outputQueue;
	std::atomic<bool> _shouldEnd;
	std::atomic<bool> _isThreadRunning;
	std::thread _samplingThread;

	void waitForThreadShutdown() const;
};


}
