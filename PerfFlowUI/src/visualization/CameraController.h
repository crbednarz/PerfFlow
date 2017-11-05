#pragma once
#include "graphics/Camera.h"


class wxSizeEvent;
class wxMouseEvent;


namespace PerfFlow
{
	

class CameraController
{
public:
	CameraController();

	void processResize(wxSizeEvent& sizeEvent);
	void processInput(wxMouseEvent& mouseEvent);

	Camera& camera();

private:
	Camera _camera;
	glm::vec2 _lastMousePosition;
	float _zoom;
};


}


inline PerfFlow::Camera& PerfFlow::CameraController::camera()
{
	return _camera;
}