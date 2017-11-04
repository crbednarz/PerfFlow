#pragma once


namespace PerfFlow
{
	

template <typename T>
class BufferedAttribute
{
public:
	explicit BufferedAttribute(oglplus::VertexArrayAttrib attribute);

	void bind() const;

private:
	oglplus::VertexArrayAttrib _attribute;
	oglplus::Buffer _buffer;
	std::vector<GLfloat> _positionData;
};


}


template <typename T>
PerfFlow::BufferedAttribute<T>::BufferedAttribute(oglplus::VertexArrayAttrib attribute) :
	_attribute(attribute)
{
}


template <typename T>
void PerfFlow::BufferedAttribute<T>::bind() const
{
	using namespace oglplus;
	_buffer.Bind(Buffer::Target::Array);
}
