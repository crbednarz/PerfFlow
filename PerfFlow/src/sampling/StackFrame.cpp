#include "stdafx.h"
#include "StackFrame.h"


PerfFlow::StackFrame::StackFrame() :
	_instructionPointer(NULL),
	_symbol(nullptr)
{
}


PerfFlow::StackFrame::StackFrame(const size_t instructionPointer, const Symbol* symbol) :
	_instructionPointer(instructionPointer),
	_symbol(symbol)
{
}

