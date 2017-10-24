#include "stdafx.h"
#include "SymbolRepository.h"
#include <cassert>


void PerfFlow::SymbolRepository::addSymbol(SymbolId id, const Symbol& symbol)
{
	if (!hasSymbol(id))
	{
		std::lock_guard<std::mutex> lockGuard(_mutex);
		_symbols.insert(std::make_pair(id, symbol));
	}
}


const PerfFlow::Symbol* PerfFlow::SymbolRepository::tryGetSymbol(SymbolId id)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	auto it = _symbols.find(id);

	if (it != _symbols.end())
		return &it->second;

	return nullptr;
}


bool PerfFlow::SymbolRepository::hasSymbol(SymbolId id)
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _symbols.find(id) != _symbols.end();
}


size_t PerfFlow::SymbolRepository::totalSymbols()
{
	std::lock_guard<std::mutex> lockGuard(_mutex);
	return _symbols.size();
}
