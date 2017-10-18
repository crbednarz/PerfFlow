#pragma once
#include <memory>
#include "symbols/SymbolRepository.h"


namespace PerfFlow
{
class ProcessSample;


class ISampler
{
public:
	ISampler() = default;
	virtual ~ISampler() = default;

	ISampler(const ISampler& other) = default;
	ISampler(ISampler&& other) = default;
	ISampler& operator=(const ISampler& other) = default;
	ISampler& operator=(ISampler&& other) = default;

	virtual void sample(ProcessSample& outputSample) = 0;
	virtual void setSymbolOutput(std::shared_ptr<SymbolRepository> symbolRepository) = 0;
	virtual void clearSymbolOutput() = 0;
};


}
