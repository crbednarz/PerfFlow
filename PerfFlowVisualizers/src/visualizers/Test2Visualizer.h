#pragma once

#include "visualization/IVisualizer.h"
#include <memory>
#include "glm.hpp"
#include <deque>
#include "symbols/SymbolRepository.h"


namespace PerfFlow
{
class SamplingContext;
class QuadBatch;
class IUISymbolList;
class Symbol;


class Test2Visualizer : public IVisualizer
{
public:
	explicit Test2Visualizer(std::shared_ptr<SamplingContext> context, IUISymbolList* uiList);

	void onSampleReceived(const ProcessSample& sample) override;

	void render(const Camera& camera) override;


private:
	struct Ball
	{
		glm::vec2 _position;
		glm::vec2 _velocity;
		float _radius;
		Ball* _attractedTo;
		SymbolId _symbol;
	};

	std::shared_ptr<SamplingContext> _context;
	std::unique_ptr<QuadBatch> _batcher;
	IUISymbolList* _uiList;

	std::deque<Ball> _balls;
	bool _isInitialized;

	void ensureInitialized();
};


}
