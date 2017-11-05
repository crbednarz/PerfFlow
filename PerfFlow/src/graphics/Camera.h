#pragma once
#include "glm.hpp"


namespace PerfFlow
{
	

class Camera
{
public:
	Camera();


	float left() const;
	float top() const;
	float right() const;
	float bottom() const;
	float width() const;
	float height() const;


	glm::vec2 center() const;
	glm::vec2 topLeft() const;
	glm::vec2 bottomRight() const;

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


inline float PerfFlow::Camera::left() const
{
	return _center.x - _size.x * 0.5f;
}


inline float PerfFlow::Camera::top() const
{
	return _center.y - _size.y * 0.5f;
}


inline float PerfFlow::Camera::right() const
{
	return _center.x + _size.x * 0.5f;
}


inline float PerfFlow::Camera::bottom() const
{
	return _center.y + _size.y * 0.5f;
}


inline float PerfFlow::Camera::width() const
{
	return _size.x;
}


inline float PerfFlow::Camera::height() const
{
	return _size.y;
}


inline glm::vec2 PerfFlow::Camera::center() const
{
	return _center;
}


inline glm::vec2 PerfFlow::Camera::topLeft() const
{
	return _center - _size * 0.5f;
}


inline glm::vec2 PerfFlow::Camera::bottomRight() const
{
	return _center + _size * 0.5f;
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
