#include "stdafx.h"
#include "Symbol.h"



PerfFlow::Symbol::Symbol(const std::string& name, const ProcessModule* processModule) :
	_name(name),
	_processModule(processModule)
{
}
