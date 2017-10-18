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

	void setSymbolOutput(std::shared_ptr<SymbolRepository> symbolRepository) override;
	void clearSymbolOutput() override;

private:
	DebugClient _debugClient;

	std::vector<ComThreadSample> _rawThreadSamples;
	std::shared_ptr<SymbolRepository> _symbolRepository;
};


}
