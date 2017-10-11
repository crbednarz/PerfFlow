#pragma once
#include "sampling/ISampler.h"
#include "DebugClient.h"


namespace PerfFlow
{
	

/// Sampler based on the COM IDebugClient component.
class ComSampler : ISampler
{
public:
	explicit ComSampler(const Process& process);

	void sample(ProcessSample& outputSample) override;

private:
	DebugClient _debugClient;

	std::vector<ComThreadSample> _rawThreadSamples;
};


}
