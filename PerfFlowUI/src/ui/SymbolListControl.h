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

	void addSymbol(SymbolId symbolId) override;
	void removeSymbol(SymbolId symbolId) override;
	SymbolId getSelected() const override;
	void select(SymbolId symbolId) override;

	void setContext(std::shared_ptr<SamplingContext> context) const;

private:
	wxObjectDataPtr<SymbolsListModel> _model;

};


}
