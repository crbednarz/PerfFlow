#include "stdafx.h"
#include "ModuleRepository.h"


void PerfFlow::ModuleRepository::add(const std::string& name, size_t address, size_t size, size_t index)
{
	if (!hasAtAddress(address))
	{
		std::lock_guard<std::mutex> lockGuard(_mutex);
		_modules.insert(std::make_pair(address, ProcessModule(name, address, size, index)));
	}
}


const PerfFlow::ProcessModule* PerfFlow::ModuleRepository::tryGetAtAddress(size_t address)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	auto it = _modules.find(address);

	if (it != _modules.end())
		return &it->second;

	return nullptr;
}


bool PerfFlow::ModuleRepository::hasAtAddress(size_t address)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _modules.find(address) != _modules.end();
}


size_t PerfFlow::ModuleRepository::count()
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _modules.size();
}
