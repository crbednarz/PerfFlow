#include "stdafx.h"
#include "StackFrame.h"


PerfFlow::StackFrame::StackFrame() :
	_instructionPointer(NULL)
{
}


PerfFlow::StackFrame::StackFrame(size_t instructionPointer) :
	_instructionPointer(instructionPointer)
{

}
