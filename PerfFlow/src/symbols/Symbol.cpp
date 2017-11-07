#include "stdafx.h"
#include "Symbol.h"



PerfFlow::Symbol::Symbol(const size_t address, const std::string& name, const ProcessModule* processModule) :
	_address(address),
	_name(name),
	_processModule(processModule)
{
}
