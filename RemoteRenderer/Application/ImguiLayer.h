#pragma once

#include "Layer.h"

class Window;

class ImguiLayer : public Layer
{
public:
	explicit ImguiLayer(Window* window);

	~ImguiLayer() override;

	void Init() override;
	void Shutdown() override;
	static void Begin();
	static void End();
	void Update(float delta_time) override;
	bool Event() override;

protected:
	Window* m_window = nullptr;
	bool show_demo_window = true;
};
