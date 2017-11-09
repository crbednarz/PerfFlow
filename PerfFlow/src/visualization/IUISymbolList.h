#pragma once


namespace PerfFlow
{
class Symbol;


class IUISymbolList
{
public:
	IUISymbolList() = default;
	virtual ~IUISymbolList() = default;

	IUISymbolList(const IUISymbolList& other) = default;
	IUISymbolList(IUISymbolList&& other) = default;
	IUISymbolList& operator=(const IUISymbolList& other) = default;
	IUISymbolList& operator=(IUISymbolList&& other) = default;

	virtual void addSymbol(const Symbol* symbol) = 0;
	virtual void removeSymbol(const Symbol* symbol) = 0;
	virtual const Symbol* getSelected() const = 0;
	virtual void select(const Symbol* symbol) = 0;

};


}