#include "stdafx.h"
#include "OrbVisualizer.h"
#include "sampling/ProcessSample.h"
#include "sampling/SamplingContext.h"
#include "utilities/GLIncludes.h"
#include "graphics/QuadBatch.h"
#include "graphics/Camera.h"
#include "visualization/IUISymbolList.h"


PerfFlow::OrbVisualizer::OrbVisualizer(const std::shared_ptr<SamplingContext> context, IUISymbolList* listController) :
	_context(context),
	_uiList(listController),
	_isInitialized(false),
	_orbs(_context->symbols().createStorage<Orb>()),
	_anchors(_context->modules().createStorage<ModuleAnchor>())
{

}



void PerfFlow::OrbVisualizer::onSampleReceived(const ProcessSample& sample)
{
	using namespace oglplus;

	for (size_t threadIndex = 0; threadIndex < sample.threadCount(); threadIndex++)
	{
		auto thread = sample.getThread(threadIndex);

		for (size_t frameIndex = 0; frameIndex < thread.frameCount(); frameIndex++)
		{
			auto frame = thread.getFrame(frameIndex);
			auto symbolId = frame.symbolId();

			if (symbolId == SymbolId::None)
				continue;

			if (!_orbs.has(symbolId))
			{
				const auto& symbol = _context->symbols().get(symbolId);

				if (!_anchors.has(symbol.moduleId()))
					createAnchor(symbol.moduleId());

				createOrb(symbolId, symbol);
			}

			auto& orb = _orbs[symbolId];
			orb._radius = std::min(orb._radius + 4.0f, 12.0f);
		}
	}
}


void PerfFlow::OrbVisualizer::render(const Camera& camera)
{
	using namespace oglplus;
	ensureInitialized();
	_batcher->setViewMatrix(camera.createViewMatrix());
	_batcher->clear();
	
	int i = 0;
	for (auto& orb : _orbs)
	{
		auto diff = orb._position;

		if (orb._anchor != ModuleId::None)
			diff -= _anchors[orb._anchor]._position;
		float dist = glm::length(diff);
		dist = std::max(1.0f, dist);
		auto normalizedDiff = diff / dist;

		orb._velocity -= normalizedDiff * std::min(4.0f, 4.0f / (dist * dist));

		orb._radius *= 0.95f;
		orb._radius = std::max(orb._radius, 1.0f);
		orb._velocity *= 0.999f;
		orb._position += orb._velocity * 0.05f;
	}
	for (auto it = _orbs.begin(); it != _orbs.end(); ++it)
	{
		auto& orb = *it;
		auto otherIt = it;
		++otherIt;
		for (; otherIt != _orbs.end(); ++otherIt)
		{
			auto& otherOrb = *otherIt;

			auto diff = otherOrb._position - orb._position;
			auto distance = glm::length(diff);

			if (distance < orb._radius + otherOrb._radius)
			{
				auto normal = diff / distance;

				orb._velocity = glm::reflect(orb._velocity, normal) * 0.9f;
				otherOrb._velocity = glm::reflect(otherOrb._velocity, normal) * 0.9f;

				if (otherOrb._radius < orb._radius)
					otherOrb._position = orb._position + normal * (orb._radius + otherOrb._radius + 0.001f);
				else
					orb._position = otherOrb._position - normal * (otherOrb._radius + orb._radius + 0.001f);
			}
		}
	}
	std::vector<int> test;
	for (auto it = _orbs.cbegin(); it != _orbs.cend(); ++it)
	{
		auto& orb = *it;

		auto color = _anchors[orb._anchor]._color;
		if (it.id() == _uiList->getSelected())
			color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		_batcher->add(orb._position - orb._radius, glm::vec2(orb._radius * 2.0f), color);
		i++;
		if (i == _batcher->capacity())
			break;
	}


	_batcher->draw();
}


void PerfFlow::OrbVisualizer::ensureInitialized()
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


void PerfFlow::OrbVisualizer::createAnchor(const ModuleId id)
{
	static const std::vector<glm::vec4> COLORS
	{
		glm::vec4(1.0f, 0.7f, 0.7f, 1.0f),
		glm::vec4(0.7f, 1.0f, 0.7f, 1.0f),
		glm::vec4(0.7f, 0.7f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.7f, 1.0f),
		glm::vec4(1.0f, 0.7f, 1.0f, 1.0f),
		glm::vec4(0.7f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 0.3f, 0.3f, 1.0f),
		glm::vec4(0.3f, 1.0f, 0.3f, 1.0f),
		glm::vec4(0.3f, 0.3f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.3f, 1.0f),
		glm::vec4(1.0f, 0.3f, 1.0f, 1.0f),
		glm::vec4(0.3f, 1.0f, 1.0f, 1.0f)
	};

	ModuleAnchor anchor;
	const float angle = id.index() * 0.7f;
	anchor._position = glm::vec2(glm::cos(angle), glm::sin(angle)) * 100.0f + 50.0f * (id.index() / 4 );
	anchor._color = COLORS[id.index() % COLORS.size()];
	_anchors.create(id, anchor);
}


void PerfFlow::OrbVisualizer::createOrb(const SymbolId id, const Symbol& symbol)
{
	const auto& processModule = _context->modules().get(symbol.moduleId());

	Orb newBall;
	const auto address = symbol.address();
	const auto minAddress = processModule.address();
	const auto maxAddress = processModule.size() + minAddress;

	const auto relativeAddress = (address - minAddress) / static_cast<float>(maxAddress - minAddress);

	const auto angle = relativeAddress * 3.141592f * 2.0f;
	const auto distance = 10.0f;

	newBall._position = glm::vec2(glm::cos(angle) * distance, glm::sin(angle) * distance) + _anchors[symbol.moduleId()]._position;
	newBall._velocity = glm::vec2(0.0f, glm::cos(angle) * 4.0f);
	newBall._radius = 0.0f;
	newBall._anchor = symbol.moduleId();
	_uiList->addSymbol(id);

	_orbs.create(id, newBall);

}

