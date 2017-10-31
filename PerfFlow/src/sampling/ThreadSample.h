#pragma once
#include <array>
#include "StackFrame.h"
#include <cassert>


namespace PerfFlow
{
	

class ThreadSample
{
public:
	static const size_t MaxFrames = 64;

	ThreadSample();
	
	void push(StackFrame stackFrame);
	void clear();

	const StackFrame& getFrame(size_t index) const;
	size_t frameCount() const;
	

private:
	std::array<StackFrame, MaxFrames> _frames;
	size_t _frameCount;
};


}


inline const PerfFlow::StackFrame& PerfFlow::ThreadSample::getFrame(size_t index) const
{
	assert(index < frameCount());
	return _frames[index];
}


inline size_t PerfFlow::ThreadSample::frameCount() const
{
	return _frameCount;
}