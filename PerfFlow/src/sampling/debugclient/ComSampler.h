#pragma once
#include "sampling/ISampler.h"
#include "DebugClient.h"


namespace PerfFlow
{
class SamplingContext;

/// Sampler based on the COM IDebugClient component.
class ComSampler : public ISampler
{
public:
	explicit ComSampler(std::shared_ptr<SamplingContext> context);

	void sample(ProcessSample& outputSample) override;

private:
	DebugClient _debugClient;

	std::vector<ComThreadSample> _rawThreadSamples;
	std::shared_ptr<SamplingContext> _context;
};


}
