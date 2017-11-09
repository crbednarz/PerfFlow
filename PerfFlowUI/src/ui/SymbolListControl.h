#pragma once
#include "visualization/IUISymbolList.h"
#include "wx/wxprec.h"
#include "wx/dataview.h"
#include "SymbolsListModel.h"


namespace PerfFlow
{
	

class SymbolListControl : public wxDataViewCtrl, public IUISymbolList
{
public:
	explicit SymbolListControl(wxWindow* parent);

	void addSymbol(const Symbol* symbol) override;
	void removeSymbol(const Symbol* symbol) override;
	const Symbol* getSelected() const override;
	void select(const Symbol* symbol) override;

private:
	wxObjectDataPtr<SymbolsListModel> _model;

};


}
