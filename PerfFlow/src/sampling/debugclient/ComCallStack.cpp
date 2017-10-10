#include "stdafx.h"
#include "ComCallStack.h"


PerfFlow::ComCallStack::ComCallStack() :
	_frames(),
	_frameCount(0)
{
}


bool PerfFlow::ComCallStack::sample(const ComPtr<IDebugControl>& debugControl)
{
	_frameCount = 0;
	ULONG filled;
	if (FAILED(debugControl->GetStackTrace(0, 0, 0, _frames.data(), _frames.size(), &filled)))
		return false;

	_frameCount = filled;
	return true;
}
