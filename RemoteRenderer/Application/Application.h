#pragma once

#include <memory>

#include "Singleton.h"

#include "Window/Window.h"

class Application : public Singleton<Application>
{
public:
	void Init();
	void Shutdown();
	void Run();

private:
	std::unique_ptr<Window> m_window = nullptr;
};
