#include "stdafx.h"
#include "ComSampler.h"
#include "sampling/ProcessSample.h"
#include "sampling/SamplingContext.h"

PerfFlow::ComSampler::ComSampler(std::shared_ptr<SamplingContext> context) :
	_debugClient(context->process()),
	_context(context)
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

		_debugClient.exportFrameSymbols(thread, _context->symbols());
	}
}