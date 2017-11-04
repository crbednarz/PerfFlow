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


void PerfFlow::QuadBatch::add(oglplus::Vec2f position, oglplus::Vec2f size)
{
	using namespace oglplus;

	_positionData[_count * 4 + 0] = position;
	_positionData[_count * 4 + 1] = position + Vec2f(size.x(), 0.0f);
	_positionData[_count * 4 + 2] = position + Vec2f(0.0f, size.y());
	_positionData[_count * 4 + 3] = position + Vec2f(size.x(), size.y());



	_colorData[_count * 4 + 0] = Vec4f(1.0f);
	_colorData[_count * 4 + 1] = Vec4f(1.0f);
	_colorData[_count * 4 + 2] = Vec4f(1.0f);
	_colorData[_count * 4 + 3] = Vec4f(1.0f);
	_count++;
	
}


void PerfFlow::QuadBatch::draw() const
{
	using namespace oglplus;

	if (_count == 0)
		return;
	
	_vertexVAO.Bind();
	_positionBuffer.Bind(Buffer::Target::Array);
	Buffer::SubData(Buffer::Target::Array, 0, _count * 4, _positionData.data());

	_colorBuffer.Bind(Buffer::Target::Array);
	Buffer::SubData(Buffer::Target::Array, 0, _count * 4, _colorData.data());

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
		varying vec4 vColor; \
		void main(void) \
		{ \
			vColor = aColor; \
			gl_Position = vec4(aPosition, 0.0, 1.0); \
		} \
		",
		"\
		#version 120\n \
		varying vec4 vColor; \
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
