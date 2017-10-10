#pragma once
#include <DbgEng.h>
#include "utilities/ComIncludes.h"
#include <array>


namespace PerfFlow
{
class ThreadSample;


// Raw collection of stack frames from an IDebugControl object.
class ComCallStack
{
public:
	ComCallStack();

	/// Fills frames with stack trace from debugControl. Returns true on success.
	bool sample(const ComPtr<IDebugControl>& debugControl);

	const DEBUG_STACK_FRAME& getFrame(size_t index) const;
	size_t frameCount() const;

private:
	static const size_t MAX_FRAMES = 64;
	std::array<DEBUG_STACK_FRAME, MAX_FRAMES> _frames;
	size_t _frameCount;
};


}


inline const DEBUG_STACK_FRAME& PerfFlow::ComCallStack::getFrame(size_t index) const
{
	return _frames[index];
}


inline size_t PerfFlow::ComCallStack::frameCount() const
{
	return _frameCount;
}

