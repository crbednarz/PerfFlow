#include "stdafx.h"
#include "TestVisualizer.h"
#include "sampling/ProcessSample.h"


PerfFlow::TestVisualizer::TestVisualizer(std::shared_ptr<SamplingContext> context) :
	_context(context),
	_isInitialized(false),
	_vertexShader(oglplus::ShaderType::Vertex),
	_fragmentShader(oglplus::ShaderType::Fragment),
	_minAddress(~size_t(0)),
	_maxAddress(0)
{

}


void PerfFlow::TestVisualizer::onSampleReceived(const ProcessSample& sample)
{
	using namespace oglplus;

	for (size_t threadIndex = 0; threadIndex < sample.threadCount(); threadIndex++)
	{
		auto thread = sample.getThread(threadIndex);

		for (size_t frameIndex = 0; frameIndex < thread.frameCount(); frameIndex++)
		{
			auto frame = thread.getFrame(frameIndex);

			auto symbolId = frame.getSymbolId();
			size_t address = frame.instructionPointer();
			if (address < 1000 || address > ~int32_t(0) - 1000)
				continue;

			_minAddress = std::min(address, _minAddress);
			_maxAddress = std::max(address, _maxAddress);

			if (_minAddress == _maxAddress)
				continue;

			auto relativeAddress = (address - _minAddress) / static_cast<float>(_maxAddress - _minAddress);

			auto index = static_cast<int>(relativeAddress * (GRID_WIDTH * GRID_HEIGHT - 1));
			
			if (frameIndex == thread.frameCount() - 1)
				_colorData[index * 4 + 0] = 1.0f;

			if (frameIndex > thread.frameCount() - 2)
				_colorData[index * 4 + 1] = 1.0f;
			_colorData[index * 4 + 2] = 1.0f;

		}
	}
}


void PerfFlow::TestVisualizer::render()
{
	using namespace oglplus;
	ensureInitialized();

	Context gl;
	gl.DrawElements(
		PrimitiveType::Triangles,
		(GRID_WIDTH - 1) * (GRID_HEIGHT - 1) * 6,
		DataType::UnsignedInt
	);

	auto i = 0;
	for (auto y = 0; y < GRID_HEIGHT; y++)
	{
		for (auto x = 0; x < GRID_WIDTH; x++)
		{
			_colorData[i + 0] = std::max(0.0f, _colorData[i + 0] - 0.01f);
			_colorData[i + 1] = std::max(0.0f, _colorData[i + 1] - 0.01f);
			_colorData[i + 2] = std::max(0.0f, _colorData[i + 2] - 0.01f);
			i += 4;
		}
	}

	_colors.Bind(Buffer::Target::Array);
	Buffer::Data(Buffer::Target::Array, _colorData.size(), _colorData.data());
}


void PerfFlow::TestVisualizer::ensureInitialized()
{
	using namespace oglplus;
	if (_isInitialized)
		return;

	 _vertexShader.Source(" \
		#version 120\n \
		attribute vec3 aPosition; \
		attribute vec4 aColor; \
		varying vec4 vColor; \
		void main(void) \
		{ \
			vColor = aColor; \
			gl_Position = vec4(aPosition, 1.0); \
		} \
		").Compile(std::nothrow).Done();

	_fragmentShader.Source("\
		#version 120\n \
		varying vec4 vColor; \
		void main(void) \
		{ \
			gl_FragColor = vColor; \
		} \
	").Compile(std::nothrow).Done();

	_shaderProgram.AttachShaders(MakeGroup(_vertexShader, _fragmentShader));
	_shaderProgram.Link();
	_shaderProgram.Use();

	_vertexVAO.Bind();

	std::vector<GLfloat> positions(GRID_WIDTH * GRID_HEIGHT * 3, 0.0f);
	_colorData = std::vector<GLfloat>(GRID_WIDTH * GRID_HEIGHT * 4, 0.0f);
	for (auto y = 0; y < GRID_HEIGHT; y++)
	{
		for (auto x = 0; x < GRID_WIDTH; x++)
		{
			positions[(y * GRID_WIDTH + x) * 3 + 0] = 2.0f * x / static_cast<float>(GRID_WIDTH - 1) - 1.0f;
			positions[(y * GRID_WIDTH + x) * 3 + 1] = 2.0f * y / static_cast<float>(GRID_HEIGHT - 1) - 1.0f;
			positions[(y * GRID_WIDTH + x) * 3 + 2] = 0.0f;


			_colorData[(y * GRID_WIDTH + x) * 4 + 0] = 0.0f;
			_colorData[(y * GRID_WIDTH + x) * 4 + 1] = 0.0f;
			_colorData[(y * GRID_WIDTH + x) * 4 + 2] = 0.0f;
			_colorData[(y * GRID_WIDTH + x) * 4 + 3] = 1.0f;
		}
	}


	_positions.Bind(Buffer::Target::Array);
	Buffer::Data(Buffer::Target::Array, positions.size(), positions.data());
	
	VertexArrayAttrib vertexAttribute(_shaderProgram, "aPosition");
	vertexAttribute.Setup<GLfloat>(3);
	vertexAttribute.Enable();


	_colors.Bind(Buffer::Target::Array);
	Buffer::Data(Buffer::Target::Array, _colorData.size(), _colorData.data());

	VertexArrayAttrib colorAttribute(_shaderProgram, "aColor");
	colorAttribute.Setup<GLfloat>(4);
	colorAttribute.Enable();


	std::vector<GLuint> indices((GRID_WIDTH - 1) * (GRID_HEIGHT - 1) * 6);

	auto i = 0;
	for (auto y = 0; y < GRID_HEIGHT - 1; y++)
	{
		for (auto x = 0; x < GRID_WIDTH - 1; x++)
		{
			indices[i++] = (y + 0) * GRID_WIDTH + x + 0;
			indices[i++] = (y + 1) * GRID_WIDTH + x + 0;
			indices[i++] = (y + 0) * GRID_WIDTH + x + 1;
			indices[i++] = (y + 1) * GRID_WIDTH + x + 1;
			indices[i++] = (y + 0) * GRID_WIDTH + x + 1;
			indices[i++] = (y + 1) * GRID_WIDTH + x + 0;
		}
	}
	_indices.Bind(Buffer::Target::ElementArray);
	Buffer::Data(Buffer::Target::ElementArray, indices.size(), indices.data());


	Context::Disable(Capability::DepthTest);
	Context::Disable(Capability::CullFace);

	_isInitialized = true;

	
}

