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

	for (size_t threadIndex = 0; threadIndex < _rawThreadSamples.size(); ++threadIndex)
	{
		auto& thread = outputSample.addThread();
		auto& rawThreadSample = _rawThreadSamples[threadIndex];


		rawThreadSample.copyTo(thread);
	}
}
