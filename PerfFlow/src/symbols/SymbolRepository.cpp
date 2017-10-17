#include "stdafx.h"
#include "SymbolRepository.h"


size_t PerfFlow::SymbolRepository::totalSymbols() const
{
	return _symbols.size();
}
