#include "stdafx.h"
#include "VisualizerPane.h"


wxBEGIN_EVENT_TABLE(VisualizerPane, wxGLCanvas)
	EVT_PAINT(VisualizerPane::onPaint)
	EVT_SIZE(VisualizerPane::onSize)
wxEND_EVENT_TABLE()


VisualizerPane::VisualizerPane(wxFrame* parent) :
	wxGLCanvas(parent)
{
}


void VisualizerPane::onPaint(wxPaintEvent& paintEvent)
{
}


void VisualizerPane::onSize(wxSizeEvent& sizeEvent)
{
	wxLogMessage("test?");

}
