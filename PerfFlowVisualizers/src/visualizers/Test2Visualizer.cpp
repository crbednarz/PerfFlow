#include "stdafx.h"
#include "Test2Visualizer.h"
#include "sampling/ProcessSample.h"
#include "sampling/SamplingContext.h"
#include "utilities/GLIncludes.h"
#include "graphics/QuadBatch.h"
#include "graphics/Camera.h"


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

		Ball* lastBall = nullptr;
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

			float angle = relativeAddress * 3.141592f * 2.0f;
			float distance = (frameIndex + 1) / (float)thread.frameCount();

			auto it = _balls.find(symbolId);
			if (it == _balls.end())
			{
				Ball newBall;

				newBall._position = glm::vec2(glm::cos(angle) * distance, glm::sin(angle) * distance);
				newBall._velocity = glm::vec2(0.0f, glm::cos(angle) * 4.0f);
				newBall._radius = 0.0f;
				_balls.insert(std::make_pair(symbolId, newBall));
				it = _balls.find(symbolId);
				
			}

			auto& ball = it->second;

			ball._radius = std::min(ball._radius + 4.0f, 12.0f);
			ball._attractedTo = lastBall;
			lastBall = &ball;
		}
	}
}


void PerfFlow::Test2Visualizer::render(const Camera& camera)
{
	using namespace oglplus;
	ensureInitialized();
	_batcher->setViewMatrix(camera.createViewMatrix());
	_batcher->clear();
	
	int i = 0;
	for (auto& pair : _balls)
	{
		auto& ball = pair.second;
		auto diff = ball._position;

		if (ball._attractedTo != nullptr)
			diff -= ball._attractedTo->_position;
		float dist = glm::length(diff);
		auto normalizedDiff = diff / dist;

		ball._velocity -= normalizedDiff * std::min(4.0f, 4.0f / (dist * dist));

		ball._radius *= 0.95f;
		ball._radius = std::max(ball._radius, 1.0f);
		ball._velocity *= 0.999f;
		ball._position += ball._velocity * 0.05f;
	}
	for (auto& pair : _balls)
	{

		auto& ball = pair.second;

		for (auto& collisionPair : _balls)
		{
			auto& otherBall = collisionPair.second;

			if (&otherBall == &ball)
				continue;

			auto diff = otherBall._position - ball._position;
			auto distance = glm::length(diff);

			if (distance < ball._radius + otherBall._radius)
			{
				auto normal = diff / distance;

				ball._velocity = glm::reflect(ball._velocity, normal) * 0.9f;
				otherBall._velocity = glm::reflect(otherBall._velocity, normal) * 0.9f;

				if (otherBall._radius < ball._radius)
					otherBall._position = ball._position + normal * (ball._radius + otherBall._radius + 0.001f);
				else
					ball._position = otherBall._position - normal * (otherBall._radius + ball._radius + 0.001f);

			}
		}
	}
	for (auto& pair : _balls)
	{

		auto& ball = pair.second;
		_batcher->add(ball._position - ball._radius, glm::vec2(ball._radius * 2.0f));
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
	Context::Enable(Capability::Blend);
	Context::BlendFunc(BlendFn::SrcAlpha, BlendFn::OneMinusSrcAlpha);

	_isInitialized = true;


}

