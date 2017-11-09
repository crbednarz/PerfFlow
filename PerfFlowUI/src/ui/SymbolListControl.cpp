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


void PerfFlow::SymbolListControl::addSymbol(const Symbol* symbol)
{
	_model->addSymbol(symbol);
}


void PerfFlow::SymbolListControl::removeSymbol(const Symbol* symbol)
{
	_model->removeSymbol(symbol);
}


const PerfFlow::Symbol* PerfFlow::SymbolListControl::getSelected() const
{
	auto selectedItem = GetSelection();

	if (selectedItem == nullptr)
		return nullptr;

	if (_model->isModule(selectedItem))
		return nullptr;

	return reinterpret_cast<const Symbol*>(selectedItem.GetID());
}


void PerfFlow::SymbolListControl::select(const Symbol* symbol)
{
}
