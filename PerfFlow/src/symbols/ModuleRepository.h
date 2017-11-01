#pragma once
#include <unordered_map>
#include "ProcessModule.h"
#include <mutex>


namespace PerfFlow
{
	

class ModuleRepository
{
public:
	ModuleRepository() = default;

	void add(const std::string& name, size_t address, size_t size, size_t index);
	const ProcessModule* tryGetAtAddress(size_t address);
	bool hasAtAddress(size_t address);
	size_t count();

private:
	std::unordered_map<size_t, ProcessModule> _modules;
	std::mutex _mutex;

};


}
