#pragma once

#include "wx/wxprec.h"
#include "utilities/GLIncludes.h"
#include "wx/glcanvas.h"
#include <memory>


namespace PerfFlow
{


class IVisualizer;
class SamplerOutputQueue;


class VisualizerPane : public wxGLCanvas
{
public:
	VisualizerPane(wxFrame* parent, std::shared_ptr<SamplerOutputQueue> samplerOutput);

	void onPaint(wxPaintEvent& paintEvent);
	void onSize(wxSizeEvent& sizeEvent);
	void onIdle(wxIdleEvent& idleEvent);

	void setVisualizer(std::unique_ptr<IVisualizer> visualizer);

private:
	std::unique_ptr<wxGLContext> _context;
	std::unique_ptr<IVisualizer> _visualizer;
	std::shared_ptr<SamplerOutputQueue> _samplerOutput;

	void render();

	wxDECLARE_EVENT_TABLE();
};


}
