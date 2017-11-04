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


		}
	}
}


void PerfFlow::Test2Visualizer::render()
{
	using namespace oglplus;
	ensureInitialized();

	_batcher->draw();
}


void PerfFlow::Test2Visualizer::ensureInitialized()
{
	using namespace oglplus;
	if (_isInitialized)
		return;

	_batcher = std::make_unique<QuadBatch>(200);
	_batcher->add(Vec2f(0.0f, 0.0f), Vec2f(0.5f, 0.5f));
	Context::Disable(Capability::DepthTest);
	Context::Disable(Capability::CullFace);

	_isInitialized = true;


}

