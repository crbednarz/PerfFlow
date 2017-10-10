#pragma once


namespace PerfFlow
{
	

class StackFrame
{
public:
	StackFrame();
	explicit StackFrame(size_t instructionPointer);

private:
	size_t _instructionPointer;
};


}