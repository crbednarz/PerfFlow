#pragma once

#include "wx/wxprec.h"
#include "utilities/GLIncludes.h"
#include "wx/glcanvas.h"
#include <memory>


class VisualizerPane : public wxGLCanvas
{
public:
	VisualizerPane(wxFrame* parent);

	void onPaint(wxPaintEvent& paintEvent);
	void onSize(wxSizeEvent& sizeEvent);

private:
	std::unique_ptr<wxGLContext> _context;

	wxDECLARE_EVENT_TABLE();
};
