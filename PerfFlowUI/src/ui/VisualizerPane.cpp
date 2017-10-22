#include "stdafx.h"
#include "VisualizerPane.h"


wxBEGIN_EVENT_TABLE(VisualizerPane, wxGLCanvas)
	EVT_PAINT(VisualizerPane::onPaint)
	EVT_SIZE(VisualizerPane::onSize)
wxEND_EVENT_TABLE()


VisualizerPane::VisualizerPane(wxFrame* parent) :
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


void VisualizerPane::onPaint(wxPaintEvent& paintEvent)
{
	oglplus::Context gl;
	wxPaintDC dc(this);

	gl.ClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	gl.Clear().ColorBuffer();

	SwapBuffers();
}


void VisualizerPane::onSize(wxSizeEvent& sizeEvent)
{

}
