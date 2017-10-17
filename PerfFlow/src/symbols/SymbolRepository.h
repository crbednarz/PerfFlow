#pragma once
#include "SymbolId.h"
#include "Symbol.h"
#include <unordered_map>


namespace PerfFlow
{
	

class SymbolRepository
{
public:
	SymbolRepository() = default;


	void addSymbol(SymbolId id, const Symbol& symbol);
	
	size_t totalSymbols() const;

private:
	std::unordered_map<SymbolId, Symbol> _symbols;

};


}
