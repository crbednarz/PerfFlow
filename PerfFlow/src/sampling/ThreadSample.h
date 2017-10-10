#pragma once
#include <array>
#include "StackFrame.h"


namespace PerfFlow
{
	

class ThreadSample
{
public:
	ThreadSample();
	
	void push(StackFrame stackFrame);

	const StackFrame& getFrame(size_t index) const;
	size_t frameCount() const;


private:
	static const size_t MAX_FRAMES = 64;
	std::array<StackFrame, MAX_FRAMES> _frames;
	size_t _frameCount;
};


}


inline const PerfFlow::StackFrame& PerfFlow::ThreadSample::getFrame(size_t index) const
{
	return _frames[index];
}


inline size_t PerfFlow::ThreadSample::frameCount() const
{
	return _frameCount;
}