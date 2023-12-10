#pragma once

#include <string>

#include "Event.h"

class Layer
{
public:
	explicit Layer(std::string name = {});
	virtual ~Layer();

	virtual void Init(){}
	virtual void Shutdown(){}
	virtual void Update(float delta_time) {}

	virtual void OnEvent(const ::Event* event){}

	virtual void OnKeyReleasedEvent(const KeyReleasedEvent* event){}
	virtual void OnKeyPressedEvent(const KeyPressedEvent* event){}

	virtual void OnAppClosedEvent(const AppLaunchedEvent* event){}
	virtual void OnAppLaunchedEvent(const AppLaunchedEvent* event){}

	virtual void OnMouseScrolledEvent(const MouseScrolledEvent* event){}
	virtual void OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent* event){}
	virtual void OnMouseButtonPressedEvent(const MouseButtonPressedEvent* event) {}
	virtual void OnMouseMovedEvent(const MouseMovedEvent* event) {}

	virtual void OnWindowResizedEvent(const WindowResizedEvent* event) {}
	virtual void OnWindowClosedEvent(const WindowClosedEvent* event) {}

private:
	std::string m_name{};
};
