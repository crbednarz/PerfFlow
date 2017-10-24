#pragma once
#include "visualization/IVisualizer.h"


namespace PerfFlow
{
	

class TestVisualizer : public IVisualizer
{
public:
	TestVisualizer() = default;

	void onSampleReceived(const ProcessSample& sample) override;
	void render() override;
};


}
