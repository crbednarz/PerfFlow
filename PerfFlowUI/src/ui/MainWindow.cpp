#include "stdafx.h"
#include "MainWindow.h"

enum
{
	MenuIdAttachToProcess = 1
};

wxBEGIN_EVENT_TABLE(PerfFlow::MainWindow, wxFrame)
	EVT_MENU(MenuIdAttachToProcess, PerfFlow::MainWindow::onAttachToProcess)
	EVT_MENU(wxID_EXIT, PerfFlow::MainWindow::onExit)
wxEND_EVENT_TABLE()



PerfFlow::MainWindow::MainWindow(const wxString& title, const wxPoint& position, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, position, size)
{
	auto menuFile = new wxMenu;
	menuFile->Append(MenuIdAttachToProcess, "&Attach To Process...\tCtrl-O");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	auto menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	SetMenuBar(menuBar);
}


void PerfFlow::MainWindow::onAttachToProcess(wxCommandEvent& event)
{

}


void PerfFlow::MainWindow::onExit(wxCommandEvent& event)
{

	Close(true);
}
