#pragma once
#include "Application/ImguiLayer.h"

class RemoteRendererGui final : public ImguiLayer
{
public:
	RemoteRendererGui();

	~RemoteRendererGui() override;
	void Init() override;
	void Shutdown() override;
	void Update(float delta_time) override;

	void ShowMenuBar();
	static void ShowFpsWindow();
	void HandelPause();
	static void HandelExit();
	static void HandelVSync();
};
