#include "stdafx.h"
#include "SymbolRepository.h"
#include <cassert>


void PerfFlow::SymbolRepository::addSymbol(SymbolId id, const Symbol& symbol)
{
	assert(!hasSymbol(id));
	_symbols.insert(std::make_pair(id, symbol));
}


const PerfFlow::Symbol* PerfFlow::SymbolRepository::tryGetSymbol(SymbolId id) const
{
	auto it = _symbols.find(id);

	if (it != _symbols.end())
		return &it->second;

	return nullptr;
}


bool PerfFlow::SymbolRepository::hasSymbol(SymbolId id) const
{
	return _symbols.find(id) != _symbols.end();
}


size_t PerfFlow::SymbolRepository::totalSymbols() const
{
	return _symbols.size();
}
