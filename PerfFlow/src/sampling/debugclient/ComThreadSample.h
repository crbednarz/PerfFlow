#pragma once
#include "ComCallStack.h"


namespace PerfFlow
{
	

class ComThreadSample
{
public:
	ComThreadSample();

	bool sample(ULONG threadId, const ComPtr<IDebugControl>& debugControl, const ComPtr<IDebugSystemObjects>& systemObjects);
	void copyTo(ThreadSample& thread) const;

private:
	ComCallStack _callStack;
	ULONG _threadId;

};


}
