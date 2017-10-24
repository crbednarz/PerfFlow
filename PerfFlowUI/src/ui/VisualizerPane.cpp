#include "stdafx.h"
#include "VisualizerPane.h"
#include "visualization/IVisualizer.h"


wxBEGIN_EVENT_TABLE(PerfFlow::VisualizerPane, wxGLCanvas)
	EVT_PAINT(PerfFlow::VisualizerPane::onPaint)
	EVT_SIZE(PerfFlow::VisualizerPane::onSize)
wxEND_EVENT_TABLE()


PerfFlow::VisualizerPane::VisualizerPane(wxFrame* parent) :
	wxGLCanvas(parent)
{

	wxGLContextAttrs contextAttributes;
	contextAttributes.PlatformDefaults().OGLVersion(3, 2).EndList();
	auto context = std::make_unique<wxGLContext>(this, nullptr, &contextAttributes);

	if (!context->IsOK())
	{
		wxLogFatalError("Failed to initialize OpenGL context.");
		return;
	}

	_context = std::move(context);
	SetCurrent(*_context);

	if (!gladLoadGL())
	{
		wxLogFatalError("Unable to initialize OpenGL.");
		return;
	}
}


void PerfFlow::VisualizerPane::onPaint(wxPaintEvent& paintEvent)
{
	oglplus::Context gl;
	wxPaintDC dc(this);

	gl.ClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	gl.Clear().ColorBuffer();


	SwapBuffers();
}


void PerfFlow::VisualizerPane::onSize(wxSizeEvent& sizeEvent)
{

}


void PerfFlow::VisualizerPane::setVisualizer(std::unique_ptr<IVisualizer> visualizer)
{
	_visualizer = std::move(visualizer);
}
