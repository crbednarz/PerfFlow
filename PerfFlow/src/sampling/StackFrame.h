#pragma once
#include "symbols/SymbolRepository.h"


namespace PerfFlow
{
	

class StackFrame
{
public:
	StackFrame();
	explicit StackFrame(size_t instructionPointer);
	StackFrame(size_t instructionPointer, SymbolId symbolId);

	size_t instructionPointer() const;
	SymbolId symbolId() const;

private:
	size_t _instructionPointer;
	SymbolId _symbolId;
};


}


inline size_t PerfFlow::StackFrame::instructionPointer() const
{
	return _instructionPointer;
}


inline PerfFlow::SymbolId PerfFlow::StackFrame::symbolId() const
{
	return _symbolId;
}
