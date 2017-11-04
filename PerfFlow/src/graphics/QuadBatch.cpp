#include "stdafx.h"
#include "QuadBatch.h"


PerfFlow::QuadBatch::QuadBatch(size_t capacity) :
	_capacity(capacity),
	_count(0),
	_positionData(capacity * 4),
	_colorData(capacity * 4)
{
	setup();
}


void PerfFlow::QuadBatch::add(glm::vec2 position, glm::vec2 size)
{
	_positionData[_count * 4 + 0] = oglplus::Vec2f(position.x, position.y);
	_positionData[_count * 4 + 1] = oglplus::Vec2f(position.x + size.x, position.y);
	_positionData[_count * 4 + 2] = oglplus::Vec2f(position.x, position.y + size.y);
	_positionData[_count * 4 + 3] = oglplus::Vec2f(position.x + size.x, position.y + size.y);

	_colorData[_count * 4 + 0] = oglplus::Vec4f(1.0f);
	_colorData[_count * 4 + 1] = oglplus::Vec4f(1.0f);
	_colorData[_count * 4 + 2] = oglplus::Vec4f(1.0f);
	_colorData[_count * 4 + 3] = oglplus::Vec4f(1.0f);

	_count++;
}


void PerfFlow::QuadBatch::clear()
{
	_count = 0;
}


void PerfFlow::QuadBatch::draw() const
{
	using namespace oglplus;

	if (_count == 0)
		return;
	
	_vertexVAO.Bind();
	_positionBuffer.Bind(Buffer::Target::Array);
	Buffer::Data(Buffer::Target::Array, _count * 4, _positionData.data());

	_colorBuffer.Bind(Buffer::Target::Array);
	Buffer::Data(Buffer::Target::Array, _count * 4, _colorData.data());

	Context gl;
	gl.DrawElements(
		PrimitiveType::Triangles,
		_count * 6,
		DataType::UnsignedInt);
}


void PerfFlow::QuadBatch::setup()
{
	using namespace oglplus;

	_shader.build(" \
		#version 120\n \
		attribute vec2 aPosition; \
		attribute vec4 aColor; \
		attribute vec2 aTextureCoord; \
		varying vec4 vColor; \
		varying vec2 vTextureCoord; \
		void main(void) \
		{ \
			vColor = aColor; \
			vTextureCoord = aTextureCoord; \
			gl_Position = vec4(aPosition, 0.0, 1.0); \
		} \
		",
		"\
		#version 120\n \
		varying vec4 vColor; \
		varying vec2 vTextureCoord; \
		void main(void) \
		{ \
			gl_FragColor = vColor; \
		} \
		");

	_vertexVAO.Bind();

	_positionBuffer.Bind(Buffer::Target::Array);
	Buffer::Resize(Buffer::Target::Array, _positionData.capacity());
	_shader.enableVertexAttribute<Vec2f>("aPosition", 1);

	_colorBuffer.Bind(Buffer::Target::Array);
	Buffer::Resize(Buffer::Target::Array, _colorData.capacity());
	_shader.enableVertexAttribute<Vec4f>("aColor", 1);

	std::vector<Vec2f> textureCoords(_capacity * 4);
	for (auto i = 0; i < _capacity; i++)
	{
		textureCoords[i * 4 + 0] = Vec2f(0.0f, 0.0f);
		textureCoords[i * 4 + 1] = Vec2f(1.0f, 0.0f);
		textureCoords[i * 4 + 2] = Vec2f(0.0f, 1.0f);
		textureCoords[i * 4 + 3] = Vec2f(1.0f, 1.0f);
	}

	_textureBuffer.Bind(Buffer::Target::Array);
	Buffer::Data(Buffer::Target::Array, textureCoords);
	_shader.enableVertexAttribute<Vec2f>("aTextureCoord", 1);

	std::vector<GLuint> indices(_capacity * 6);
	for (auto i = 0; i < _capacity; i++)
	{
		indices[i * 6 + 0] = i * 4 + 0;
		indices[i * 6 + 1] = i * 4 + 1;
		indices[i * 6 + 2] = i * 4 + 2;
		indices[i * 6 + 3] = i * 4 + 3;
		indices[i * 6 + 4] = i * 4 + 2;
		indices[i * 6 + 5] = i * 4 + 1;
	}

	_indexBuffer.Bind(Buffer::Target::ElementArray);
	Buffer::Data(Buffer::Target::ElementArray, indices);

}
