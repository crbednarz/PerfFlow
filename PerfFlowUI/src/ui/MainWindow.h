#pragma once
#include "wx/wxprec.h"
#include "wx/aui/aui.h"
#include <memory>
#include "SymbolsListModel.h"
#include "SymbolListControl.h"


namespace PerfFlow
{

	
class VisualizerPane;
class SamplerOutputQueue;
class SamplingTask;


class MainWindow : public wxFrame
{
public:
	MainWindow(const wxString& title, const wxPoint& position, const wxSize& size);
	~MainWindow();

	MainWindow(const MainWindow& other) = delete;
	MainWindow(MainWindow&& other) = delete;
	MainWindow& operator=(const MainWindow& other) = delete;
	MainWindow& operator=(MainWindow&& other) = delete;

private:
	void onAttachToProcess(wxCommandEvent& event);
	void onExit(wxCommandEvent& event);

	VisualizerPane* _visualizerPane;
	wxAuiManager _auiManager;

	std::shared_ptr<SamplerOutputQueue> _samplerOutput;
	std::unique_ptr<SamplingTask> _samplingTask;
	SymbolListControl* _symbolListControl;

	wxDECLARE_EVENT_TABLE();
};


}
