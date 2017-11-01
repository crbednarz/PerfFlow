#pragma once
#include "symbols/SymbolRepository.h"
#include "system/Process.h"
#include "symbols/ModuleRepository.h"


namespace PerfFlow
{
	

class SamplingContext
{
public:
	explicit SamplingContext(Process process);

	const Process& process() const;
	SymbolRepository& symbols();
	ModuleRepository& modules();

private:
	Process _process;
	SymbolRepository _symbolRepository;
	ModuleRepository _moduleRepository;

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

inline PerfFlow::ModuleRepository& PerfFlow::SamplingContext::modules()
{
	return _moduleRepository;
}