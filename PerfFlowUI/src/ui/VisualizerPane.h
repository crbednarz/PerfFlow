#pragma once

#include "wx/wxprec.h"
#include "utilities/GLIncludes.h"
#include "wx/glcanvas.h"
#include <memory>


namespace PerfFlow
{


class IVisualizer;


class VisualizerPane : public wxGLCanvas
{
public:
	VisualizerPane(wxFrame* parent);

	void onPaint(wxPaintEvent& paintEvent);
	void onSize(wxSizeEvent& sizeEvent);

	void setVisualizer(std::unique_ptr<IVisualizer> visualizer);

private:
	std::unique_ptr<wxGLContext> _context;
	std::unique_ptr<IVisualizer> _visualizer;

	wxDECLARE_EVENT_TABLE();
};


}
