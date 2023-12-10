#pragma once

#include "Layer.h"

class Window;

class ImguiLayer : public Layer
{
public:
	ImguiLayer();

	~ImguiLayer() override;

	void Init() override;
	void Shutdown() override;
	static void Begin();
	static void End();
	void Update(float delta_time) override;
	void OnWindowResizedEvent(const WindowResizedEvent* event) override;

protected:
	bool show_demo_window = true;
};
