#pragma once
#include "utilities/GLIncludes.h"
#include "BasicShaderProgram.h"
#include "glm.hpp"

namespace PerfFlow
{


class QuadBatch
{
public:
	explicit QuadBatch(size_t capacity);

	void add(glm::vec2 position, glm::vec2 size, glm::vec4 color);
	void clear();

	void setViewMatrix(const glm::mat4& viewMatrix);

	void draw() const;

	size_t capacity() const;
	size_t count() const;

private:
	size_t _capacity;
	size_t _count;

	BasicShaderProgram _shader;

	oglplus::VertexArray _vertexVAO;

	oglplus::Buffer _positionBuffer;
	oglplus::Buffer _colorBuffer;
	oglplus::Buffer _textureBuffer;
	oglplus::Buffer _indexBuffer;

	std::vector<oglplus::Vec2f> _positionData;
	std::vector<oglplus::Vec4f> _colorData;

	void setup();
};


}


inline size_t PerfFlow::QuadBatch::capacity() const
{
	return _capacity;
}

inline size_t PerfFlow::QuadBatch::count() const
{
	return _count;
}