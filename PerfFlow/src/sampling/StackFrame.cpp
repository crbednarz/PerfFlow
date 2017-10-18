#include "stdafx.h"
#include "StackFrame.h"


PerfFlow::StackFrame::StackFrame() :
	_instructionPointer(NULL),
	_symbolId(SymbolId::None)
{
}


PerfFlow::StackFrame::StackFrame(size_t instructionPointer) :
	_instructionPointer(instructionPointer),
	_symbolId(SymbolId::None)
{
}


PerfFlow::StackFrame::StackFrame(size_t instructionPointer, SymbolId symbolId) :
	_instructionPointer(instructionPointer),
	_symbolId(symbolId)
{

}