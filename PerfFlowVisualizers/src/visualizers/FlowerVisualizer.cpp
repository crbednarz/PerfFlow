#include "stdafx.h"
#include "FlowerVisualizer.h"
#include "utilities/GLIncludes.h"
#include "graphics/QuadBatch.h"
#include "graphics/Camera.h"


PerfFlow::FlowerVisualizer::FlowerVisualizer(const std::shared_ptr<SamplingContext> context, IUISymbolList* uiList) :
	_isInitialized(false),
	_context(context),
	_uiList(uiList)
{
}


void PerfFlow::FlowerVisualizer::onSampleReceived(const ProcessSample& sample)
{
}


void PerfFlow::FlowerVisualizer::render(const Camera& camera)
{
	using namespace oglplus;
	ensureInitialized();
	_batcher->setViewMatrix(camera.createViewMatrix());
	_batcher->clear();
}


void PerfFlow::FlowerVisualizer::ensureInitialized()
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
