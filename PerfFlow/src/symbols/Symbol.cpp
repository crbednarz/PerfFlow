#include "stdafx.h"
#include "Symbol.h"



PerfFlow::Symbol::Symbol(const size_t address, const std::string& name, const ModuleId moduleId) :
	_address(address),
	_name(name),
	_moduleId(moduleId)
{
}
