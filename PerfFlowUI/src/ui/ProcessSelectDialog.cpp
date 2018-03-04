#include "stdafx.h"
#include "ProcessSelectDialog.h"
#include <wx/srchctrl.h>


PerfFlow::ProcessSelectDialog::ProcessSelectDialog(wxWindow* parent, const wxString& title) :
	wxDialog(parent, -1, title, wxDefaultPosition, wxSize(250, 230))
{
	auto sizer = new wxBoxSizer(wxVERTICAL);


	// List
	const auto listPanel = new wxPanel(this, -1);
	const auto panelBorder = new wxStaticBox(listPanel, -1, wxT("Processes..."), wxPoint(5, 5), wxSize(240, 150));
	const auto searchBar = new wxSearchCtrl(listPanel, -1);
	sizer->Add(listPanel, 1);


	// Buttons
	const auto cancelButton = new wxButton(this, -1, "Cancel", wxDefaultPosition, wxSize(70, 25));
	const auto attachButton = new wxButton(this, -1, "Attach", wxDefaultPosition, wxSize(70, 25));

	const auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(cancelButton, 1);
	buttonSizer->Add(attachButton, 1, wxRIGHT);
	sizer->Add(buttonSizer, 0, wxBOTTOM | wxRIGHT, 5);

	// Finalize
	SetSizer(sizer);
}
