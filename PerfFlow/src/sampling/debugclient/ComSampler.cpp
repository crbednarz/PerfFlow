#include "stdafx.h"
#include "ComSampler.h"
#include "sampling/ProcessSample.h"


PerfFlow::ComSampler::ComSampler(const Process& process) :
	_debugClient(process)
{
}


void PerfFlow::ComSampler::sample(ProcessSample& outputSample)
{
	_debugClient.sample(_rawCallStackCache);

	for (size_t threadIndex = 0; threadIndex < _rawCallStackCache.size(); ++threadIndex)
	{
		auto& thread = outputSample.addThread();
		auto& rawCallStack = _rawCallStackCache[threadIndex];

		for (size_t frameIndex = 0; frameIndex < thread.frameCount(); ++frameIndex)
		{
			thread.push(StackFrame(rawCallStack.getFrame(frameIndex).InstructionOffset));
		}
	}
}
