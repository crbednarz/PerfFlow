#pragma once
#include "wx/wxprec.h"
#include <memory>


namespace PerfFlow
{

	
class VisualizerPane;
class SymbolRepository;
class SamplerOutputQueue;
class SamplingTask;


class MainWindow : public wxFrame
{
public:
	MainWindow(const wxString& title, const wxPoint& position, const wxSize& size);

private:
	void onAttachToProcess(wxCommandEvent& event);
	void onExit(wxCommandEvent& event);

	VisualizerPane* _visualizerPane;
	std::shared_ptr<SymbolRepository> _symbolRepository;
	std::shared_ptr<SamplerOutputQueue> _samplerOutput;
	std::unique_ptr<SamplingTask> _samplingTask;

	wxDECLARE_EVENT_TABLE();
};


}
