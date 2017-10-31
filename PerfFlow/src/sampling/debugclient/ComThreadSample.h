#pragma once
#include "ComCallStack.h"


namespace PerfFlow
{
	

class ComThreadSample
{
public:
	ComThreadSample();

	bool sample(ULONG threadId, const ComPtr<IDebugControl>& debugControl, const ComPtr<IDebugSystemObjects>& systemObjects);

	const ComCallStack& callstack() const;
	ULONG threadId() const;

private:
	ComCallStack _callStack;
	ULONG _threadId;

};


}


inline const PerfFlow::ComCallStack& PerfFlow::ComThreadSample::callstack() const
{
	return _callStack;
}


inline ULONG PerfFlow::ComThreadSample::threadId() const
{
	return _threadId;
}