#pragma once
#include "visualization/IVisualizer.h"
#include <memory>
#include "utilities/GLIncludes.h"
#include "graphics/BasicShaderProgram.h"


namespace PerfFlow
{
class SamplingContext;


class TestVisualizer : public IVisualizer
{
public:
	explicit TestVisualizer(std::shared_ptr<SamplingContext> symbolRepository);

	void onSampleReceived(const ProcessSample& sample) override;

	void render(const Camera& camera) override;
	

private:
	static const int GRID_WIDTH = 64;
	static const int GRID_HEIGHT = 64;

	std::shared_ptr<SamplingContext> _context;
	bool _isInitialized;

	BasicShaderProgram _shader;

	oglplus::VertexArray _vertexVAO;
	oglplus::Buffer _positions;
	oglplus::Buffer _indices;
	oglplus::Buffer _colors;

	std::vector<GLfloat> _colorData;

	void ensureInitialized();
};


}
