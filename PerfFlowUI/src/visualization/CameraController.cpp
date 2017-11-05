#include "stdafx.h"
#include "CameraController.h"
#include "wx/wxprec.h"


PerfFlow::CameraController::CameraController() :
	_zoom(400.0f)
{
}


void PerfFlow::CameraController::processResize(wxSizeEvent& sizeEvent)
{
	_camera.setSize(glm::vec2(sizeEvent.GetSize().x, sizeEvent.GetSize().y) / _zoom);
}


void PerfFlow::CameraController::processInput(wxMouseEvent& mouseEvent)
{
	const auto wxMousePosition = mouseEvent.GetPosition();
	const auto mousePosition = glm::vec2(wxMousePosition.x, wxMousePosition.y);

	if (mouseEvent.LeftDown())
	{
		_lastMousePosition = mousePosition;
		return;
	}

	if (mouseEvent.LeftIsDown())
		_camera.moveBy(-(mousePosition - _lastMousePosition) / _zoom);

	_lastMousePosition = mousePosition;
}


