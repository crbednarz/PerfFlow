#pragma once

#include "visualization/IVisualizer.h"
#include <memory>
#include <vector>
#include "symbols/SymbolId.h"
#include "glm.hpp"
#include <deque>


namespace PerfFlow
{
class SamplingContext;
class QuadBatch;


class Test2Visualizer : public IVisualizer
{
public:
	explicit Test2Visualizer(std::shared_ptr<SamplingContext> symbolRepository);

	void onSampleReceived(const ProcessSample& sample) override;

	void render(const Camera& camera) override;


private:
	struct Ball
	{
		glm::vec2 _position;
		glm::vec2 _velocity;
		float _radius;
		Ball* _attractedTo;
	};

	std::shared_ptr<SamplingContext> _context;
	std::unique_ptr<QuadBatch> _batcher;

	std::deque<Ball> _balls;
	bool _isInitialized;

	void ensureInitialized();
};


}
