#pragma once
#include "utilities/ComIncludes.h"
#include <vector>
#include "ComThreadSample.h"
#include "sampling/SamplingContext.h"


namespace PerfFlow
{
class Process;


/// Wraps functionality of COM's IDebugClient and related classes.
class DebugClient
{
public:
	explicit DebugClient(const Process& process);

	void sample(std::vector<ComThreadSample>& outputCallstacks);

	bool isValid() const;

	void exportSample(const ComThreadSample& rawSample, ThreadSample& outputSample, SamplingContext& context) const;

private:
	bool _isValid;
	ComPtr<IDebugClient> _client;
	ComPtr<IDebugControl> _control;
	ComPtr<IDebugSystemObjects> _systemObjects;
	ComPtr<IDebugSymbols> _symbols;
	std::vector<ULONG> _threadIds;

	static bool waitForClientToAttach(const ComPtr<IDebugControl>& debugControl);

	const Symbol* createInstructionSymbols(ULONG64 instructionPointer, SamplingContext& context) const;
	const ProcessModule* tryAddModuleWithIndex(ULONG moduleIndex, ModuleRepository& modules) const;
};


}


inline bool PerfFlow::DebugClient::isValid() const
{
	return _isValid;
}
