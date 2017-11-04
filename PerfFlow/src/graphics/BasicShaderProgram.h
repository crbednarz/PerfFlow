#pragma once
#include "utilities/GLIncludes.h"
#include "BufferedAttribute.h"


namespace PerfFlow
{
	

/// Acts as a light-weight wrapper for a vertex and fragment shader linked to a shader program.
class BasicShaderProgram
{
public:
	BasicShaderProgram();

	void build(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	void use() const;

	oglplus::Program& get();

	template <typename TElementType>
	void enableVertexAttribute(const std::string& name, GLuint elementCount) const;

	template <typename TElementType>
	BufferedAttribute<TElementType> createBufferedAttribute(const std::string& name, GLuint elementCount) const;

private:
	bool _isBuilt;

	oglplus::Shader _vertexShader;
	oglplus::Shader _fragmentShader;
	oglplus::Program _shaderProgram;

};


}


template <typename TElementType>
void PerfFlow::BasicShaderProgram::enableVertexAttribute(const std::string& name, GLuint elementCount) const
{
	oglplus::VertexArrayAttrib attribute(_shaderProgram, name);
	attribute.Setup<TElementType>(elementCount);
	attribute.Enable();
}


template <typename TElementType>
PerfFlow::BufferedAttribute<TElementType> PerfFlow::BasicShaderProgram::createBufferedAttribute(const std::string& name, GLuint elementCount) const
{
	oglplus::VertexArrayAttrib attribute(_shaderProgram, name);
	attribute.Setup<TElementType>(elementCount);
	attribute.Enable();

	return BufferedAttribute<TElementType>(attribute);
}
