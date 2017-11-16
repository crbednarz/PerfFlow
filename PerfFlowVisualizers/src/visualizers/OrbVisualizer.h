#pragma once

#include "visualization/IVisualizer.h"
#include <memory>
#include "glm.hpp"
#include <deque>
#include "symbols/SymbolRepository.h"


namespace PerfFlow
{
class ThreadSample;
class SamplingContext;
class QuadBatch;
class IUISymbolList;
class Symbol;


class OrbVisualizer : public IVisualizer
{
public:
	explicit OrbVisualizer(std::shared_ptr<SamplingContext> context, IUISymbolList* uiList);

	void onSampleReceived(const ProcessSample& sample) override;

	void render(const Camera& camera) override;

private:
	struct Orb
	{
		glm::vec2 _position;
		glm::vec2 _velocity;
		float _radius;
		ModuleId _anchor;
	};

	struct ModuleAnchor
	{
		glm::vec2 _position;
		glm::vec4 _color;
	};

	std::shared_ptr<SamplingContext> _context;
	std::unique_ptr<QuadBatch> _batcher;
	IUISymbolList* _uiList;

	SymbolStorage<Orb> _orbs;
	ModuleStorage<ModuleAnchor> _anchors;

	bool _isInitialized;

	void ensureInitialized();

	void createAnchor(ModuleId id);
	void createOrb(SymbolId symbolId, const Symbol& symbol);
};


}
