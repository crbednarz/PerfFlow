#pragma once

#include "wx/wxprec.h"
#include "wx/glcanvas.h"
#include <memory>


class VisualizerPane : public wxGLCanvas
{
public:
	VisualizerPane(wxFrame* parent);

private:
	std::unique_ptr<wxGLContext> _context;
};
