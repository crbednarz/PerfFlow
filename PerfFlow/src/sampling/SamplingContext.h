#pragma once
#include "symbols/SymbolRepository.h"
#include "system/Process.h"


namespace PerfFlow
{
class SymbolRepository;
	

class SamplingContext
{
public:
	explicit SamplingContext(Process process);

	const Process& process() const;
	SymbolRepository& symbols();

private:
	Process _process;
	SymbolRepository _symbolRepository;

};


}


inline const PerfFlow::Process& PerfFlow::SamplingContext::process() const
{
	return _process;
}


inline PerfFlow::SymbolRepository& PerfFlow::SamplingContext::symbols()
{
	return _symbolRepository;
}