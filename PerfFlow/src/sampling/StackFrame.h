#pragma once
#include "symbols/Symbol.h"


namespace PerfFlow
{
	

class StackFrame
{
public:
	StackFrame();
	explicit StackFrame(size_t instructionPointer, const Symbol* symbol = nullptr);

	size_t instructionPointer() const;
	const Symbol* symbol() const;

private:
	size_t _instructionPointer;
	const Symbol* _symbol;
};


}


inline size_t PerfFlow::StackFrame::instructionPointer() const
{
	return _instructionPointer;
}


inline const PerfFlow::Symbol* PerfFlow::StackFrame::symbol() const
{
	return _symbol;
}
