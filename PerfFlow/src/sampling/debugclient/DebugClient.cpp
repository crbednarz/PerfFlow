#include "stdafx.h"
#include "DebugClient.h"
#include "system/Process.h"
#include "sampling/ThreadSample.h"
#include "utilities/ComHelper.h"
#include "ComCallStack.h"
#include <thread>
#include <vector>


PerfFlow::DebugClient::DebugClient(const Process& process) :
	_isValid(false)
{
	ComPtr<IDebugClient> debugClient;
	if (ComHelper::failed(DebugCreate(__uuidof(IDebugClient), &debugClient)))
		return;

	const ULONG64 LOCAL_SERVER = 0;
	auto flags = DEBUG_ATTACH_NONINVASIVE | DEBUG_ATTACH_NONINVASIVE_NO_SUSPEND;

	if (ComHelper::failed(debugClient->AttachProcess(LOCAL_SERVER, process.id(), flags)))
		return;


	ComPtr<IDebugControl> debugControl;
	if (ComHelper::failed(debugClient.As(&debugControl)))
		return;

	ComPtr<IDebugSystemObjects> systemObjects;
	if (ComHelper::failed(debugClient.As(&systemObjects)))
		return;

	ComPtr<IDebugSymbols> symbols;
	if (ComHelper::failed(debugClient.As(&symbols)))
		return;

	if (ComHelper::failed(waitForClientToAttach(debugControl)))
		return;

	_client = std::move(debugClient);
	_control = std::move(debugControl);
	_systemObjects = std::move(systemObjects);
	_symbols = std::move(symbols);
	_isValid = true;

}


void PerfFlow::DebugClient::sample(std::vector<ComThreadSample>& outputThreads)
{
	ULONG threadCount = 0;
	if (ComHelper::failed(_systemObjects->GetNumberThreads(&threadCount)))
		return;

	_threadIds.resize(threadCount);
	outputThreads.resize(threadCount);

	if (ComHelper::failed(_systemObjects->GetThreadIdsByIndex(0, threadCount, _threadIds.data(), nullptr)))
		return;

	auto successfulSamples = 0;
	for (ULONG i = 0; i < threadCount; i++)
	{
		if (outputThreads[successfulSamples].sample(_threadIds[i], _control, _systemObjects))
			successfulSamples++;
	}

	outputThreads.resize(successfulSamples);
}


void PerfFlow::DebugClient::exportSample(const ComThreadSample& rawSample, ThreadSample& outputSample, SamplingContext& context) const
{
	const auto& rawCallStack = rawSample.callstack();

	for (size_t frameIndex = 0; frameIndex < rawCallStack.frameCount(); ++frameIndex)
	{
		const auto& rawFrame = rawCallStack.getFrame(frameIndex);
		auto instructionPointer = rawFrame.InstructionOffset;
		auto symbolId = createInstructionSymbols(instructionPointer, context);

		outputSample.push(StackFrame(instructionPointer, symbolId));
	}

}


bool PerfFlow::DebugClient::waitForClientToAttach(const ComPtr<IDebugControl>& debugControl)
{
	// TODO: Investigate use of SetExecutionStatus.
	// It was advised in this post: https://www.codeproject.com/Articles/371137/A-Mixed-Mode-Stackwalk-with-the-IDebugClient-Inter
	// that calling SetExecutionStatus would more consistently get the debugger attached.
	// However in practice it seems to have no effect either way.
	// debugControl->SetExecutionStatus(DEBUG_STATUS_GO);
	return ComHelper::succeeded(debugControl->WaitForEvent(DEBUG_WAIT_DEFAULT, INFINITE));
}


PerfFlow::SymbolId PerfFlow::DebugClient::createInstructionSymbols(ULONG64 instructionPointer, SamplingContext& context) const
{
	const ULONG NAME_BUFFER_SIZE = 128;
	char nameBuffer[NAME_BUFFER_SIZE];

	ULONG nameSize;
	ULONG64 displacement;
	if (FAILED(_symbols->GetNameByOffset(instructionPointer,
		nameBuffer,
		NAME_BUFFER_SIZE,
		&nameSize,
		&displacement)))
		return SymbolId::None;

	SymbolId symbolId(instructionPointer - displacement);
	auto& symbols = context.symbols();

	if (!symbols.has(symbolId))
	{
		ULONG moduleIndex;
		ULONG64 moduleBase;
		if (FAILED(_symbols->GetModuleByOffset(instructionPointer,
			0,
			&moduleIndex,
			&moduleBase)))
			return SymbolId::None;


		symbols.add(symbolId, std::string(nameBuffer, nameSize));
	}



	return symbolId;
}
