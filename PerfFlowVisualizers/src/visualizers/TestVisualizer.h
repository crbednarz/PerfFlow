#pragma once
#include "visualization/IVisualizer.h"
#include <memory>
#include "utilities/GLIncludes.h"


namespace PerfFlow
{
class SamplingContext;


class TestVisualizer : public IVisualizer
{
public:
	explicit TestVisualizer(std::shared_ptr<SamplingContext> symbolRepository);

	void onSampleReceived(const ProcessSample& sample) override;

	void render() override;
	

private:
	static const int GRID_WIDTH = 64;
	static const int GRID_HEIGHT = 64;

	std::shared_ptr<SamplingContext> _context;
	bool _isInitialized;

	oglplus::Shader _vertexShader;
	oglplus::Shader _fragmentShader;
	oglplus::Program _shaderProgram;

	oglplus::VertexArray _vertexVAO;
	oglplus::Buffer _positions;
	oglplus::Buffer _indices;
	oglplus::Buffer _colors;

	std::vector<GLfloat> _colorData;

	void ensureInitialized();
};


}
