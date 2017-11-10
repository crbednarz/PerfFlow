#pragma once
#include "wx/wxprec.h"
#include "wx/dataview.h"
#include "visualization/IUISymbolList.h"
#include <unordered_map>
#include "symbols/ModuleRepository.h"


namespace PerfFlow
{
class Symbol;
class ProcessModule;
class SamplingContext;


class SymbolsListModel : public wxDataViewModel
{
public:
	SymbolsListModel() = default;

	unsigned GetColumnCount() const override;
	wxString GetColumnType(unsigned col) const override;
	void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned col) const override;
	bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned col) override;
	wxDataViewItem GetParent(const wxDataViewItem& item) const override;
	bool IsContainer(const wxDataViewItem& item) const override;
	unsigned GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;


	void addSymbol(SymbolId symbolId);
	void removeSymbol(SymbolId symbolId);

	static bool isModule(const wxDataViewItem& item);
	static SymbolId asSymbolId(const wxDataViewItem& item);
	static ModuleId asModuleId(const wxDataViewItem& item);

	void setContext(std::shared_ptr<SamplingContext> context);

private:
	static constexpr size_t MODULE_ID_FLAG = 0x70000000UL;

	std::unordered_map<ModuleId, std::vector<SymbolId>> _symbolByModule;
	std::shared_ptr<SamplingContext> _context;

	static wxDataViewItem createItem(SymbolId symbolId);
	static wxDataViewItem createItem(ModuleId moduleId);
};


}
