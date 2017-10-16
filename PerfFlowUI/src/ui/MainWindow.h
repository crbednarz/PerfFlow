#pragma once
#include "wx/wxprec.h"


namespace PerfFlow
{


class MainWindow : public wxFrame
{
public:
	MainWindow(const wxString& title, const wxPoint& position, const wxSize& size);
private:
	void onAttachToProcess(wxCommandEvent& event);
	void onExit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};


}
