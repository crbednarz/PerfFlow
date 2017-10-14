#pragma once


namespace PerfFlow
{
	

class StackFrame
{
public:
	StackFrame();
	explicit StackFrame(size_t instructionPointer);

	size_t instructionPointer() const;

private:
	size_t _instructionPointer;
};


}


inline size_t PerfFlow::StackFrame::instructionPointer() const
{
	return _instructionPointer;
}