#pragma once


namespace PerfFlow
{
class Camera;
class ProcessSample;


class IVisualizer
{
public:
	IVisualizer() = default;
	virtual ~IVisualizer() = default;

	IVisualizer(const IVisualizer& other) = default;
	IVisualizer(IVisualizer&& other) = default;
	IVisualizer& operator=(const IVisualizer& other) = default;
	IVisualizer& operator=(IVisualizer&& other) = default;

	virtual void onSampleReceived(const ProcessSample&) = 0;
	virtual void render(const Camera& camera) = 0;

};


}