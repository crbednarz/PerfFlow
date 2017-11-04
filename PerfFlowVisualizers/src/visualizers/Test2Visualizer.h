#pragma once

#include "visualization/IVisualizer.h"
#include <memory>
#include <unordered_map>
#include "symbols/SymbolId.h"
#include "glm.hpp"


namespace PerfFlow
{
class SamplingContext;
class QuadBatch;


class Test2Visualizer : public IVisualizer
{
public:
	explicit Test2Visualizer(std::shared_ptr<SamplingContext> symbolRepository);

	void onSampleReceived(const ProcessSample& sample) override;

	void render() override;


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

	std::unordered_map<SymbolId, Ball> _balls;
	bool _isInitialized;

	void ensureInitialized();
};


}
