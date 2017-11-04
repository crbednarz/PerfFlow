#include "stdafx.h"
#include "BasicShaderProgram.h"


PerfFlow::BasicShaderProgram::BasicShaderProgram() :
	_isBuilt(false),
	_vertexShader(oglplus::ShaderType::Vertex),
	_fragmentShader(oglplus::ShaderType::Fragment)
{
}


void PerfFlow::BasicShaderProgram::build(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	assert(!_isBuilt);

	_vertexShader.Source(vertexShaderSource).Compile(std::nothrow).Done();
	_fragmentShader.Source(fragmentShaderSource).Compile(std::nothrow).Done();

	_shaderProgram.AttachShaders(MakeGroup(_vertexShader, _fragmentShader));
	_shaderProgram.Link();
	_shaderProgram.Use();

	_isBuilt = true;
}


void PerfFlow::BasicShaderProgram::use() const
{
	assert(_isBuilt);
	_shaderProgram.Use();
}


oglplus::Program& PerfFlow::BasicShaderProgram::get()
{
	return _shaderProgram;
}
