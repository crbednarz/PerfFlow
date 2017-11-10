#include "stdafx.h"
#include "SymbolsListModel.h"
#include "symbols/Symbol.h"
#include "symbols/ProcessModule.h"
#include "sampling/SamplingContext.h"
#include <xlocmon>


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
	if (isModule(item))
		variant = _context->modules().get(asModuleId(item)).name();
	else
		variant = _context->symbols().get(asSymbolId(item)).name();
}


bool PerfFlow::SymbolsListModel::SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned col)
{
	return false;
}


wxDataViewItem PerfFlow::SymbolsListModel::GetParent(const wxDataViewItem& item) const
{
	if (item.GetID() == nullptr || isModule(item))
		return wxDataViewItem(nullptr);

	return createItem(_context->symbols().get(asSymbolId(item)).moduleId());
}


bool PerfFlow::SymbolsListModel::IsContainer(const wxDataViewItem& item) const
{
	return item.GetID() == nullptr || isModule(item);

}


unsigned PerfFlow::SymbolsListModel::GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const
{
	if (item.GetID() == nullptr)
	{
		for (const auto& pair : _symbolByModule)
			children.Add(createItem(pair.first));

		return _symbolByModule.size();
	}

	if (!isModule(item))
		return 0;


	const auto it = _symbolByModule.find(asModuleId(item));

	if (it == _symbolByModule.end())
		return 0;

	const auto& symbolList = it->second;

	for (const auto& symbolId : symbolList)
		children.Add(createItem(symbolId));

	return symbolList.size();
}


void PerfFlow::SymbolsListModel::addSymbol(const SymbolId symbolId)
{
	assert(symbolId != SymbolId::None);

	const auto& symbol = _context->symbols().get(symbolId);

	auto it = _symbolByModule.find(symbol.moduleId());

	if (it == _symbolByModule.end())
	{
		_symbolByModule.insert(std::make_pair(symbol.moduleId(), std::vector<SymbolId> { symbolId }));

		ItemAdded(wxDataViewItem(nullptr), createItem(symbol.moduleId()));
	}
	else
	{
		it->second.push_back(symbolId);
	}


	ItemAdded(createItem(symbol.moduleId()), createItem(symbolId));
}


void PerfFlow::SymbolsListModel::removeSymbol(const SymbolId symbolId)
{
	// Not yet implemented
	assert(false);
}


bool PerfFlow::SymbolsListModel::isModule(const wxDataViewItem& item)
{
	const auto moduleId = static_cast<uint32_t>(reinterpret_cast<size_t>(item.GetID()));
	return (moduleId & MODULE_ID_FLAG) == MODULE_ID_FLAG;
}


PerfFlow::SymbolId PerfFlow::SymbolsListModel::asSymbolId(const wxDataViewItem& item)
{
	assert(!isModule(item));
	auto symbolId = static_cast<uint32_t>(reinterpret_cast<size_t>(item.GetID()));
	symbolId &= ~MODULE_ID_FLAG;
	return SymbolId(symbolId);
}


PerfFlow::ModuleId PerfFlow::SymbolsListModel::asModuleId(const wxDataViewItem& item)
{
	assert(isModule(item));
	auto moduleId = static_cast<uint32_t>(reinterpret_cast<size_t>(item.GetID()));
	moduleId &= ~MODULE_ID_FLAG;
	return ModuleId(moduleId);

}


void PerfFlow::SymbolsListModel::setContext(const std::shared_ptr<SamplingContext> context)
{
	_context = context;
}


wxDataViewItem PerfFlow::SymbolsListModel::createItem(const SymbolId symbolId)
{
	assert(symbolId != SymbolId::None);

	const size_t id = symbolId.index();
	return wxDataViewItem(reinterpret_cast<void*>(id));
}


wxDataViewItem PerfFlow::SymbolsListModel::createItem(const ModuleId moduleId)
{
	assert(moduleId != ModuleId::None);

	size_t id = moduleId.index();
	id |= MODULE_ID_FLAG;
	return wxDataViewItem(reinterpret_cast<void*>(id));
}
