#pragma once
#include "wx/wxprec.h"
#include "wx/dataview.h"
#include "visualization/IUISymbolList.h"
#include <unordered_map>


namespace PerfFlow
{
class Symbol;
class ProcessModule;


class SymbolsListModel : public wxDataViewModel
{
public:
	SymbolsListModel();

	unsigned GetColumnCount() const override;
	wxString GetColumnType(unsigned col) const override;
	void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned col) const override;
	bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned col) override;
	wxDataViewItem GetParent(const wxDataViewItem& item) const override;
	bool IsContainer(const wxDataViewItem& item) const override;
	unsigned GetChildren(const wxDataViewItem& item, wxDataViewItemArray& children) const override;


	void addSymbol(const Symbol* symbol);
	void removeSymbol(const Symbol* symbol);
	const Symbol* getSelected() const;
	void select(const Symbol* symbol);
	bool isModule(const wxDataViewItem& item);

private:
	std::unordered_map<const ProcessModule*, std::vector<const Symbol*>> _symbolByModule;
};


}
