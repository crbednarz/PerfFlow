#pragma once
#include "visualization/IVisualizer.h"
#include <memory>


namespace PerfFlow
{
	

class SymbolRepository;

class TestVisualizer : public IVisualizer
{
public:
	explicit TestVisualizer(std::shared_ptr<SymbolRepository> symbolRepository);

	void onSampleReceived(const ProcessSample& sample) override;
	void render() override;

private:
	std::shared_ptr<SymbolRepository> _symbolRepository;
};


}
