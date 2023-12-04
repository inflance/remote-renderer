#pragma once
#include "Application/ImguiLayer.h"

class RemoteRendererGui final : public ImguiLayer
{
public:
	explicit RemoteRendererGui(Window* window);

	~RemoteRendererGui() override;
	void Init() override;
	void Shutdown() override;
	void Update(float delta_time) override;
	bool Event() override;
	void ShowMenuBar();
	static void ShowFpsWindow();
	void HandelPause();
	void HandelExit() const;
	static void HandelVSync();
};
