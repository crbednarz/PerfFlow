#pragma once

#include "visualization/IVisualizer.h"
#include <memory>


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
	std::shared_ptr<SamplingContext> _context;
	std::unique_ptr<QuadBatch> _batcher;
	bool _isInitialized;

	void ensureInitialized();
};


}
