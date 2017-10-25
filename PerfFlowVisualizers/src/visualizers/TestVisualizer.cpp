#include "stdafx.h"
#include "TestVisualizer.h"


PerfFlow::TestVisualizer::TestVisualizer(std::shared_ptr<SymbolRepository> symbolRepository) :
	_symbolRepository(symbolRepository)
{

}


void PerfFlow::TestVisualizer::onSampleReceived(const ProcessSample& sample)
{

}


void PerfFlow::TestVisualizer::render()
{

}
