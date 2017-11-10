#include "stdafx.h"
#include "SymbolListControl.h"
#include "SymbolsListModel.h"


PerfFlow::SymbolListControl::SymbolListControl(wxWindow* parent) :
	wxDataViewCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_NO_HEADER | wxDV_SINGLE)
{
	SetSize(200, 200);
	wxDataViewTextRenderer* renderer = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
	auto column = new wxDataViewColumn("Symbols", renderer, 0, 100, wxAlignment(wxALIGN_LEFT | wxALIGN_TOP), 0);
	AppendColumn(column);
	SetExpanderColumn(column);
	_model = new SymbolsListModel();
	AssociateModel(_model.get());
}


void PerfFlow::SymbolListControl::addSymbol(const SymbolId symbolId)
{
	_model->addSymbol(symbolId);
}


void PerfFlow::SymbolListControl::removeSymbol(const SymbolId symbolId)
{
	_model->removeSymbol(symbolId);
}


PerfFlow::SymbolId PerfFlow::SymbolListControl::getSelected() const
{
	auto selectedItem = GetSelection();

	if (selectedItem == nullptr)
		return SymbolId::None;

	if (_model->isModule(selectedItem))
		return SymbolId::None;

	return _model->asSymbolId(selectedItem);
}


void PerfFlow::SymbolListControl::select(const SymbolId symbolId)
{
}


void PerfFlow::SymbolListControl::setContext(const std::shared_ptr<SamplingContext> context) const
{
	_model->setContext(context);
}
