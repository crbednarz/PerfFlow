#pragma once
#include "visualization/IVisualizer.h"
#include <memory>
#include "utilities/GLIncludes.h"


namespace PerfFlow
{
	
	
class SymbolRepository;

class TestVisualizer : public IVisualizer
{
public:
	explicit TestVisualizer(std::shared_ptr<SymbolRepository> symbolRepository);

	void onSampleReceived(const ProcessSample& sample) override;

	void render() override;
	

private:
	static const int GRID_WIDTH = 64;
	static const int GRID_HEIGHT = 64;

	std::shared_ptr<SymbolRepository> _symbolRepository;
	bool _isInitialized;

	oglplus::Shader _vertexShader;
	oglplus::Shader _fragmentShader;
	oglplus::Program _shaderProgram;

	oglplus::VertexArray _vertexVAO;
	oglplus::Buffer _positions;
	oglplus::Buffer _indices;
	oglplus::Buffer _colors;

	std::vector<GLfloat> _colorData;

	size_t _minAddress;
	size_t _maxAddress;

	void ensureInitialized();
};


}
