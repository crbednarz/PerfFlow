#pragma once
#include "symbols/SymbolId.h"


namespace PerfFlow
{
	

class StackFrame
{
public:
	StackFrame();
	explicit StackFrame(size_t instructionPointer);
	StackFrame(size_t instructionPointer, SymbolId symbolId);

	size_t instructionPointer() const;
	SymbolId getSymbolId() const;
	void setSymbolId(const SymbolId& symbol);

private:
	size_t _instructionPointer;
	SymbolId _symbolId;
};


}


inline size_t PerfFlow::StackFrame::instructionPointer() const
{
	return _instructionPointer;
}


inline PerfFlow::SymbolId PerfFlow::StackFrame::getSymbolId() const
{
	return _symbolId;
}


inline void PerfFlow::StackFrame::setSymbolId(const SymbolId& symbol)
{
	_symbolId = symbol;
}
