#include "stdafx.h"
#include "MainWindow.h"
#include "sampling/debugclient/ComSampler.h"
#include "sampling/ProcessSample.h"
#include "system/Process.h"
#include <memory>
#include <thread>
#include <chrono>
#include "sampling/SamplerOutputQueue.h"
#include "sampling/SamplingTask.h"


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
	Process process(25356);
	auto sampler = std::make_unique<ComSampler>(process);
	auto symbols = std::make_shared<SymbolRepository>();
	auto samples = std::make_shared<SamplerOutputQueue>(1000);
	sampler->setSymbolOutput(symbols);

	auto samplingTask = std::make_unique<SamplingTask>(std::move(sampler), samples);

	samplingTask->begin();

	int c = 0;

	auto sample = std::make_unique<ProcessSample>();
	while (true)
	{
		
		if (!samples->tryDequeue(*sample))
			continue;

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
		c++;

		if (c == 1000)
			return;
	}
}


void PerfFlow::MainWindow::onExit(wxCommandEvent& event)
{

	Close(true);
}
