#pragma once
#include "glm.hpp"


namespace PerfFlow
{
	

class Camera
{
public:
	Camera();

	void centerAt(glm::vec2 position);
	void moveBy(glm::vec2 offset);

	void setSize(glm::vec2 size);
	glm::vec2 getSize() const;

	glm::mat4 createViewMatrix() const;

private:
	glm::vec2 _center;
	glm::vec2 _size;
};


}


inline void PerfFlow::Camera::centerAt(const glm::vec2 position)
{
	_center = position;
}


inline void PerfFlow::Camera::setSize(const glm::vec2 size)
{
	_size = size;
}


inline glm::vec2 PerfFlow::Camera::getSize() const
{
	return _size;
}
