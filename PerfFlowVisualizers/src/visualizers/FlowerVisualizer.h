#pragma once
#include "visualization/IVisualizer.h"
#include <memory>
#include "glm.hpp"
#include "symbols/SymbolRepository.h"


namespace PerfFlow
{
class QuadBatch;
class SamplingContext;
class IUISymbolList;
	

class FlowerVisualizer : public IVisualizer
{
public:
	explicit FlowerVisualizer(std::shared_ptr<SamplingContext> context, IUISymbolList* uiList);

	void onSampleReceived(const ProcessSample& sample) override;

	void render(const Camera& camera) override;
	
private:
	bool _isInitialized;

	std::shared_ptr<SamplingContext> _context;
	std::unique_ptr<QuadBatch> _batcher;
	IUISymbolList* _uiList;

	struct Petal
	{
		glm::vec2 _position;
	};

	struct Anchor
	{
		glm::vec2 _position;
	};


	SymbolStorage<Anchor> _petal;
	ModuleStorage<Petal> _anchors;

	void ensureInitialized();

	void addAnchor(const SymbolId id, const Symbol& symbol);
};


}