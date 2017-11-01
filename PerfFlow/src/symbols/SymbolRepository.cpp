#include "stdafx.h"
#include "SymbolRepository.h"
#include <cassert>


void PerfFlow::SymbolRepository::add(SymbolId id, const std::string& name, const ProcessModule* processModule)
{
	if (!has(id))
	{
		std::lock_guard<std::mutex> lockGuard(_mutex);
		_symbols.insert(std::make_pair(id, Symbol(name, processModule)));
	}
}


const PerfFlow::Symbol* PerfFlow::SymbolRepository::tryGet(SymbolId id)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	auto it = _symbols.find(id);

	if (it != _symbols.end())
		return &it->second;

	return nullptr;
}


bool PerfFlow::SymbolRepository::has(SymbolId id)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _symbols.find(id) != _symbols.end();
}


size_t PerfFlow::SymbolRepository::count()
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _symbols.size();
}
