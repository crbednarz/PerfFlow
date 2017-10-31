#include "stdafx.h"
#include "ComThreadSample.h"
#include "utilities/ComHelper.h"
#include "sampling/StackFrame.h"
#include "sampling/ThreadSample.h"


PerfFlow::ComThreadSample::ComThreadSample() :
	_threadId(0)
{
}


bool PerfFlow::ComThreadSample::sample(ULONG threadId, const ComPtr<IDebugControl>& control, const ComPtr<IDebugSystemObjects>& systemObjects)
{
	_threadId = threadId;

	if (ComHelper::failed(systemObjects->SetCurrentThreadId(threadId)))
		return false;

	return _callStack.sample(control);
}
