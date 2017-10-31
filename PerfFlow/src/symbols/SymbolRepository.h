#pragma once
#include "SymbolId.h"
#include "Symbol.h"
#include <unordered_map>
#include <mutex>


namespace PerfFlow
{
	

class SymbolRepository
{
public:
	SymbolRepository() = default;


	void addSymbol(SymbolId id, const Symbol& symbol);
	const Symbol* tryGetSymbol(SymbolId id);
	bool hasSymbol(SymbolId id);
	
	size_t totalSymbols();

private:
	std::unordered_map<SymbolId, Symbol> _symbols;
	std::mutex _mutex;

};


}
