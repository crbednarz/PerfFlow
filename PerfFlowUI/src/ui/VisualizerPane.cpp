#include "stdafx.h"
#include "VisualizerPane.h"
#include "visualization/IVisualizer.h"
#include "sampling/SamplerOutputQueue.h"


wxBEGIN_EVENT_TABLE(PerfFlow::VisualizerPane, wxGLCanvas)
	EVT_PAINT(PerfFlow::VisualizerPane::onPaint)
	EVT_SIZE(PerfFlow::VisualizerPane::onSize)
	EVT_IDLE(PerfFlow::VisualizerPane::onIdle)
	EVT_MOUSE_EVENTS(PerfFlow::VisualizerPane::onMouseEvent)
wxEND_EVENT_TABLE()


PerfFlow::VisualizerPane::VisualizerPane(wxFrame* parent, std::shared_ptr<SamplerOutputQueue> samplerOutput) :
	wxGLCanvas(parent),
	_samplerOutput(samplerOutput)
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
	wxPaintDC dc(this);

	render();
}


void PerfFlow::VisualizerPane::onSize(wxSizeEvent& sizeEvent)
{
	using namespace oglplus;
	Context::Viewport(sizeEvent.GetSize().GetWidth(), sizeEvent.GetSize().GetHeight());

	_cameraController.processResize(sizeEvent);
}


void PerfFlow::VisualizerPane::onIdle(wxIdleEvent& idleEvent)
{
	wxClientDC dc(this);
	render();
	idleEvent.RequestMore(); // render continuously, not only once on idle
}


void PerfFlow::VisualizerPane::onMouseEvent(wxMouseEvent& mouseEvent)
{
	mouseEvent.Skip();
	_cameraController.processInput(mouseEvent);
}


void PerfFlow::VisualizerPane::setVisualizer(std::unique_ptr<IVisualizer> visualizer)
{
	_visualizer = std::move(visualizer);
}

void PerfFlow::VisualizerPane::render()
{

	oglplus::Context gl;

	gl.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gl.Clear().ColorBuffer();

	if (_visualizer)
	{
		while (_samplerOutput->canPeek())
		{
			_visualizer->onSampleReceived(_samplerOutput->peek());
			_samplerOutput->pop();
		}

		_visualizer->render(_cameraController.camera());
	}

	SwapBuffers();
}