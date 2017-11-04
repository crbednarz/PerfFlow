#include "stdafx.h"
#include "Test2Visualizer.h"
#include "sampling/ProcessSample.h"
#include "sampling/SamplingContext.h"
#include "utilities/GLIncludes.h"
#include "graphics/QuadBatch.h"


PerfFlow::Test2Visualizer::Test2Visualizer(std::shared_ptr<SamplingContext> context) :
	_context(context),
	_isInitialized(false)
{

}


void PerfFlow::Test2Visualizer::onSampleReceived(const ProcessSample& sample)
{
	using namespace oglplus;

	for (size_t threadIndex = 0; threadIndex < sample.threadCount(); threadIndex++)
	{
		auto thread = sample.getThread(threadIndex);

		for (size_t frameIndex = 0; frameIndex < thread.frameCount(); frameIndex++)
		{
			auto frame = thread.getFrame(frameIndex);

			auto symbolId = frame.getSymbolId();
			auto symbol = _context->symbols().tryGet(symbolId);

			if (symbol == nullptr)
				continue;

			size_t address = frame.instructionPointer();
			size_t minAddress = symbol->processModule().address();
			size_t maxAddress = symbol->processModule().size() + minAddress;

			auto relativeAddress = (address - minAddress) / static_cast<float>(maxAddress - minAddress);

			auto it = _balls.find(symbolId);
			if (it == _balls.end())
			{
				_balls.insert(std::make_pair(symbolId, Ball()));
				it = _balls.find(symbolId);
			}

			float angle = relativeAddress * 3.141592f * 2.0f;
			float distance = frameIndex / (float)thread.frameCount();

			it->second._position = glm::vec2(glm::cos(angle) * distance, glm::sin(angle) * distance);
		}
	}
}


void PerfFlow::Test2Visualizer::render()
{
	using namespace oglplus;
	ensureInitialized();

	_batcher->clear();
	
	int i = 0;
	for (auto pair : _balls)
	{
		_batcher->add(pair.second._position - glm::vec2(0.025f, 0.025f), glm::vec2(0.05f, 0.05f));
		i++;
		if (i == _batcher->capacity())
			break;
	}

	_batcher->draw();
}


void PerfFlow::Test2Visualizer::ensureInitialized()
{
	using namespace oglplus;
	if (_isInitialized)
		return;

	_batcher = std::make_unique<QuadBatch>(2000);
	Context::Disable(Capability::DepthTest);
	Context::Disable(Capability::CullFace);

	_isInitialized = true;


}

