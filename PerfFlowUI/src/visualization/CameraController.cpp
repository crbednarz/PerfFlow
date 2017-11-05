#include "stdafx.h"
#include "CameraController.h"
#include "wx/wxprec.h"


PerfFlow::CameraController::CameraController() :
	_zoom(1.0f)
{
}


void PerfFlow::CameraController::processResize(wxSizeEvent& sizeEvent)
{
	_resolution = glm::vec2(sizeEvent.GetSize().x, sizeEvent.GetSize().y);
	_camera.setSize(_resolution / _zoom);
}


void PerfFlow::CameraController::processInput(wxMouseEvent& mouseEvent)
{
	const auto wxMousePosition = mouseEvent.GetPosition();
	const auto mousePosition = glm::vec2(wxMousePosition.x, wxMousePosition.y);

	const auto mouseWheelRotation = mouseEvent.GetWheelRotation();

	if (mouseWheelRotation != 0)
	{
		// While this will typically produce in increments of 1 or -1
		// The documentation makes mention of potential high resolution scrolls where a partial scroll wheel might be possible.
		const auto relativeZoom = mouseWheelRotation / static_cast<float>(mouseEvent.GetWheelDelta());
		const auto oldZoom = _zoom;
		_zoom *= std::pow(1.1f, relativeZoom);

		_camera.setSize(_resolution / _zoom);
		
		// Corrects the camera position so we zoom into the cursor rather than the center.
		_camera.moveBy((mousePosition - _resolution * 0.5f) / oldZoom - (mousePosition - _resolution * 0.5f) / _zoom);
	}

	// We ignore moving the Camera if LeftDown is true, as it means the left mouse was just pressed down, and _lastMousePosition is not accurate.
	if (!mouseEvent.LeftDown() && mouseEvent.LeftIsDown())
	{
		_camera.moveBy(-(mousePosition - _lastMousePosition) / _zoom);
	}

	_lastMousePosition = mousePosition;
}


