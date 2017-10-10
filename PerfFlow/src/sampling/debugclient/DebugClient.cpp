#include "stdafx.h"
#include "DebugClient.h"
#include "system/Process.h"
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

	if (ComHelper::failed(waitForClientToAttach(debugControl)))
		return;

	_client = std::move(debugClient);
	_control = std::move(debugControl);
	_systemObjects = std::move(systemObjects);
	_isValid = true;

}


void PerfFlow::DebugClient::sample(std::vector<ComCallStack>& outputCallstacks)
{
	ULONG threadCount = 0;
	if (ComHelper::failed(_systemObjects->GetNumberThreads(&threadCount)))
		return;

	_threadIds.resize(threadCount);
	outputCallstacks.resize(threadCount);

	if (ComHelper::failed(_systemObjects->GetThreadIdsByIndex(0, threadCount, _threadIds.data(), nullptr)))
		return;

	int successfulSamples = 0;
	for (auto i = 0; i < threadCount; i++)
	{
		if (ComHelper::failed(_systemObjects->SetCurrentThreadId(_threadIds[i])))
			continue;


		ULONG filled = 0;
		if (!outputCallstacks[i].sample(_control))
		{
			i--;
			continue;
		}

		successfulSamples++;
	}

	outputCallstacks.resize(successfulSamples);
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
