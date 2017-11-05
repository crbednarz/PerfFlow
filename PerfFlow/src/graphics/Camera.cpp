#include "stdafx.h"
#include "Camera.h"
#include "gtc/matrix_transform.hpp"


PerfFlow::Camera::Camera() :
	_size(4.0f, 4.0f)
{
}


void PerfFlow::Camera::moveBy(const glm::vec2 offset)
{
	_center += offset;
}


glm::mat4 PerfFlow::Camera::createViewMatrix() const
{
	return glm::ortho(_center.x - _size.x * 0.5f, _center.x + _size.x * 0.5f, _center.y + _size.y * 0.5f, _center.y - _size.y * 0.5f);
}
