#include "stdafx.h"
#include "MainWindow.h"
#include "sampling/debugclient/ComSampler.h"
#include "sampling/ProcessSample.h"
#include "system/Process.h"
#include <memory>
#include <thread>
#include <chrono>


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
	Process process(33020);
	auto sampler = std::make_unique<ComSampler>(process);
	auto symbols = std::make_shared<SymbolRepository>();
	auto sample = std::make_unique<ProcessSample>();
	sampler->setSymbolOutput(symbols);
	
	sampler->sample(*sample);


	for (size_t threadIndex = 0; threadIndex < sample->threadCount(); threadIndex++)
	{
		const auto& thread = sample->getThread(threadIndex);

		for (size_t frameIndex = 0; frameIndex < thread.frameCount(); frameIndex++)
		{
			auto& frame = thread.getFrame(frameIndex);
			wxLogMessage(symbols->tryGetSymbol(frame.getSymbolId())->name().c_str());
		}
	}

	sample->clear();
}


void PerfFlow::MainWindow::onExit(wxCommandEvent& event)
{

	Close(true);
}
