#include "stdafx.h"
#include "ComSampler.h"
#include "sampling/ProcessSample.h"


PerfFlow::ComSampler::ComSampler(const Process& process) :
	_debugClient(process)
{
}


void PerfFlow::ComSampler::sample(ProcessSample& outputSample)
{
	_debugClient.sample(_rawThreadSamples);

	for (size_t threadIndex = 0; threadIndex < std::min(ProcessSample::MaxThreads, _rawThreadSamples.size()); ++threadIndex)
	{
		auto& thread = outputSample.addThread();
		auto& rawThreadSample = _rawThreadSamples[threadIndex];

		rawThreadSample.copyTo(thread);

		if (_symbolRepository != nullptr)
			_debugClient.exportSymbols(thread, *_symbolRepository);
	}
}


void PerfFlow::ComSampler::setSymbolOutput(std::shared_ptr<SymbolRepository> symbolRepository)
{
	_symbolRepository = symbolRepository;
}


void PerfFlow::ComSampler::clearSymbolOutput()
{
	_symbolRepository = nullptr;
}
