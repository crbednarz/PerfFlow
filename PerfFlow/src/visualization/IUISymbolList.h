#pragma once
#include "symbols/SymbolRepository.h"


namespace PerfFlow
{


class IUISymbolList
{
public:
	IUISymbolList() = default;
	virtual ~IUISymbolList() = default;

	IUISymbolList(const IUISymbolList& other) = default;
	IUISymbolList(IUISymbolList&& other) = default;
	IUISymbolList& operator=(const IUISymbolList& other) = default;
	IUISymbolList& operator=(IUISymbolList&& other) = default;

	virtual void addSymbol(SymbolId symbolId) = 0;
	virtual void removeSymbol(SymbolId symbolId) = 0;
	virtual SymbolId getSelected() const = 0;
	virtual void select(SymbolId symbolId) = 0;

};


}
