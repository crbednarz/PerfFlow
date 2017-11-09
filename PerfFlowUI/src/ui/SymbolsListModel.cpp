#include "stdafx.h"
#include "SymbolsListModel.h"
#include "symbols/Symbol.h"
#include "symbols/ProcessModule.h"


PerfFlow::SymbolsListModel::SymbolsListModel() 
{
}


unsigned PerfFlow::SymbolsListModel::GetColumnCount() const
{
	return 1;
}


wxString PerfFlow::SymbolsListModel::GetColumnType(unsigned col) const
{
	return "string";
}


void PerfFlow::SymbolsListModel::GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned col) const
{
	const auto processModule = reinterpret_cast<const ProcessModule*>(item.GetID());

	const auto it = _symbolByModule.find(processModule);

	if (it != _symbolByModule.end())
	{
		variant = it->first->name();
		return;
	}

	variant = reinterpret_cast<const Symbol*>(item.GetID())->name();
}


bool PerfFlow::SymbolsListModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned col)
{
	return false;
}


wxDataViewItem PerfFlow::SymbolsListModel::GetParent(const wxDataViewItem& item) const
{
	if (item.GetID() == nullptr)
		return wxDataViewItem(nullptr);

	const auto processModule = reinterpret_cast<const ProcessModule*>(item.GetID());

	const auto it = _symbolByModule.find(processModule);
	
	if (it != _symbolByModule.end())
		return wxDataViewItem(nullptr);
	
	auto symbol = reinterpret_cast<const Symbol*>(item.GetID());
	return wxDataViewItem(const_cast<ProcessModule*>(&symbol->processModule()));
}


bool PerfFlow::SymbolsListModel::IsContainer(const wxDataViewItem& item) const
{
	if (item.GetID() == nullptr)
		return true;

	const auto processModule = reinterpret_cast<const ProcessModule*>(item.GetID());
	return _symbolByModule.find(processModule) != _symbolByModule.end();

}


unsigned PerfFlow::SymbolsListModel::GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const
{
	if (item.GetID() == nullptr)
	{
		for (const auto& pair : _symbolByModule)
			children.Add(wxDataViewItem(const_cast<ProcessModule*>(pair.first)));

		return _symbolByModule.size();
	}

	const auto processModule = reinterpret_cast<const ProcessModule*>(item.GetID());
	const auto it = _symbolByModule.find(processModule);

	if (it == _symbolByModule.end())
		return 0;

	const auto& symbolList = it->second;

	for (const auto& symbol : symbolList)
		children.Add(wxDataViewItem(const_cast<Symbol*>(symbol)));

	return symbolList.size();
}


void PerfFlow::SymbolsListModel::addSymbol(const Symbol* symbol)
{
	void* moduleId = const_cast<ProcessModule*>(&symbol->processModule());
	void* symbolId = const_cast<Symbol*>(symbol);

	auto it = _symbolByModule.find(&symbol->processModule());

	if (it == _symbolByModule.end())
	{
		_symbolByModule.insert(std::make_pair(&symbol->processModule(), std::vector<const Symbol*> { symbol }));

		ItemAdded(wxDataViewItem(nullptr), wxDataViewItem(moduleId));
	}
	else
	{
		it->second.push_back(symbol);
	}


	ItemAdded(wxDataViewItem(moduleId), wxDataViewItem(symbolId));
}


void PerfFlow::SymbolsListModel::removeSymbol(const Symbol* symbol)
{
}


const PerfFlow::Symbol* PerfFlow::SymbolsListModel::getSelected() const
{
	return nullptr;
}


void PerfFlow::SymbolsListModel::select(const Symbol* symbol)
{
}


bool PerfFlow::SymbolsListModel::isModule(const wxDataViewItem& item)
{
	const auto processModule = reinterpret_cast<const ProcessModule*>(item.GetID());
	return _symbolByModule.find(processModule) != _symbolByModule.end();
}
