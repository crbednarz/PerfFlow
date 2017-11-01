#include "stdafx.h"
#include "ProcessModule.h"


PerfFlow::ProcessModule::ProcessModule(const std::string& name, size_t base, size_t size, size_t index) :
	_name(name),
	_address(base),
	_size(size),
	_index(index)
{

}
