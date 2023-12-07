#pragma once

#include <cstdint>
#include <sstream>
#include <string>

constexpr uint32_t Bit(uint32_t size)
{
	return 1 << size;
}

class Event
{
public:
	virtual ~Event() = default;

	enum EventType
	{
		None = 0,
		MouseEvent = Bit(0),
		KeyEvent = Bit(1),
		WindowEvent = Bit(2),
		ApplicationEvent = Bit(3),
	};

	[[nodiscard]] virtual int GetType() const = 0;
	[[nodiscard]] virtual std::string GetName() const = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;

	static EventType GetStaticType() { return None; }
};

class MouseEvent : public Event
{
public:
	enum MouseEventType
	{
		MouseMoved,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled,
	};

	~MouseEvent() override = default;

	[[nodiscard]] virtual MouseEventType GetMouseEventType() const = 0;

	[[nodiscard]] int GetType() const override { return EventType::MouseEvent; }

	static EventType GetStaticType() { return EventType::MouseEvent; }

	[[nodiscard]] std::string GetName() const override { return "MouseEvent"; }
	[[nodiscard]] std::string ToString() const override { return GetName(); }
};

class MouseButtonPressedEvent final : public MouseEvent
{
public:
	explicit MouseButtonPressedEvent(const int button, const int mods = 0)
		: m_button(button), m_mods(mods)
	{
	}

	[[nodiscard]] MouseEventType GetMouseEventType() const override { return MouseButtonPressed; }

	[[nodiscard]] int GetButton() const { return m_button; }
	[[nodiscard]] int GetMods() const { return m_mods; }

	[[nodiscard]] std::string GetName() const override { return "MouseButtonPressedEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": button=" << m_button << ",mods=" << m_mods;
		return ssm.str();
	}

private:
	int m_button;
	int m_mods;
};

class MouseButtonReleasedEvent final : public MouseEvent
{
public:
	explicit MouseButtonReleasedEvent(const int button, const int mods = 0)
		: m_button(button),m_mods(mods)
	{
	}

	[[nodiscard]] MouseEventType GetMouseEventType() const override { return MouseButtonReleased; }

	[[nodiscard]] int GetButton() const { return m_button; }
	[[nodiscard]] int GetMods() const { return m_mods; }

	[[nodiscard]] std::string GetName() const override { return "MouseButtonReleasedEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": button=" << m_button << ",mods=" << m_mods;
		return ssm.str();
	}

private:
	int m_button;
	int m_mods;
};

class MouseMovedEvent final : public MouseEvent
{
public:
	MouseMovedEvent(const float x, const float y)
		: m_x(x), m_y(y)
	{
	}

	[[nodiscard]] MouseEventType GetMouseEventType() const override { return MouseMoved; }

	[[nodiscard]] float GetX() const { return m_x; }
	[[nodiscard]] float GetY() const { return m_y; }

	[[nodiscard]] std::string GetName() const override { return "MouseMovedEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": x=" << m_x << ",y=" << m_y;
		return ssm.str();
	}

private:
	float m_x, m_y;
};

class MouseScrolledEvent final : public MouseEvent
{
public:
	MouseScrolledEvent(const float x_offset, const float y_offset)
		: m_x_offset(x_offset), m_y_offset(y_offset)
	{
	}

	[[nodiscard]] MouseEventType GetMouseEventType() const override { return MouseScrolled; }

	[[nodiscard]] float GetXOffset() const { return m_x_offset; }
	[[nodiscard]] float GetYOffset() const { return m_y_offset; }

	[[nodiscard]] std::string GetName() const override { return "MouseScrolledEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": x offset=" << m_x_offset << ",y offset=" << m_y_offset;
		return ssm.str();
	}

private:
	float m_x_offset, m_y_offset;
};

class KeyEvent : public Event
{
public:
	enum KeyEventType
	{
		KeyPressed,
		KeyReleased,
	};

	~KeyEvent() override = default;

	[[nodiscard]] virtual KeyEventType GetKeyEventType() const = 0;

	[[nodiscard]] int GetType() const override { return EventType::KeyEvent; }

	static EventType GetStaticType() { return EventType::KeyEvent; }

	[[nodiscard]] std::string GetName() const override { return "KeyEvent"; }

	[[nodiscard]] std::string ToString() const override { return GetName(); }
};

class KeyPressedEvent final : public KeyEvent
{
public:
	explicit KeyPressedEvent(int key_code, int mods = 0)
		: m_key_code(key_code), m_mods(mods)
	{
	}

	[[nodiscard]] KeyEventType GetKeyEventType() const override { return KeyPressed; }

	[[nodiscard]] int GetKeyCode() const { return m_key_code; }
	[[nodiscard]] int GetMods() const { return m_mods; }

	[[nodiscard]] std::string GetName() const override { return "KeyPressedEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": key code=" << m_key_code << ",mods=" << m_mods;
		return ssm.str();
	}

private:
	int m_key_code{};
	int m_mods{};
};

class KeyReleasedEvent final : public KeyEvent
{
public:
	explicit KeyReleasedEvent(int key_code, int mods = 0)
		: m_key_code(key_code), m_mods(mods)
	{
	}

	[[nodiscard]] KeyEventType GetKeyEventType() const override { return KeyReleased; }

	[[nodiscard]] int GetKeyCode() const { return m_key_code; }
	[[nodiscard]] int GetMods() const { return m_mods; }

	[[nodiscard]] std::string GetName() const override { return "KeyReleasedEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": key code=" << m_key_code << ",mods=" << m_mods;
		return ssm.str();
	}

private:
	int m_key_code;
	int m_mods;
};

class WindowEvent : public Event
{
public:
	enum WindowEventType
	{
		WindowResized,
		WindowClosed,
		WindowScaled
	};

	~WindowEvent() override = default;

	[[nodiscard]] virtual WindowEventType GetWindowEventType() const = 0;

	[[nodiscard]] int GetType() const override { return EventType::WindowEvent; }

	static EventType GetStaticType() { return EventType::WindowEvent; }

	[[nodiscard]] std::string GetName() const override { return "WindowEvent"; }

	[[nodiscard]] std::string ToString() const override { return GetName(); }
};

class WindowResizedEvent final : public WindowEvent
{
public:
	explicit WindowResizedEvent(const int width, const int height)
		: m_width(width), m_height(height)
	{
	}

	[[nodiscard]] WindowEventType GetWindowEventType() const override { return WindowResized; }

	[[nodiscard]] int GetWidth() const { return m_width; }
	[[nodiscard]] int GetHeight() const { return m_height; }

	[[nodiscard]] std::string GetName() const override { return "WindowResizedEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": width=" << m_width << ",height=" << m_height;
		return ssm.str();
	}

private:
	int m_width, m_height;
};

class WindowScaledEvent final : public WindowEvent
{
public:
	explicit WindowScaledEvent(const float x_scale, const float y_scale)
		: m_x_scale(x_scale), m_y_scale(y_scale)
	{
	}

	[[nodiscard]] WindowEventType GetWindowEventType() const override { return WindowScaled; }

	[[nodiscard]] float GetXScale() const { return m_x_scale; }
	[[nodiscard]] float GetYScale() const { return m_y_scale; }

	[[nodiscard]] std::string GetName() const override { return "WindowScaledEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": x scale=" << m_x_scale << ",y scale=" << m_y_scale;
		return ssm.str();
	}

private:
	float m_x_scale, m_y_scale;
};

class WindowFocusedEvent final : public WindowEvent
{
public:
	explicit WindowFocusedEvent(bool focused)
		: m_focused(focused)
	{
	}

	[[nodiscard]] WindowEventType GetWindowEventType() const override { return WindowScaled; }

	[[nodiscard]] float GetFocused() const { return m_focused; }

	[[nodiscard]] std::string GetName() const override { return "WindowScaledEvent"; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ssm;
		ssm << GetName() << ": focused=" << m_focused;
		return ssm.str();
	}

private:
	bool m_focused{};
};

class WindowClosedEvent final : public WindowEvent
{
public:
	WindowClosedEvent() = default;

	[[nodiscard]] WindowEventType GetWindowEventType() const override { return WindowClosed; }

	[[nodiscard]] std::string GetName() const override { return "WindowClosedEvent"; }

	[[nodiscard]] std::string ToString() const override { return GetName(); }
};

class ApplicationEvent : public Event
{
public:
	enum ApplicationEventType
	{
		AppLaunched,
		AppClosed,
	};

	~ApplicationEvent() override = default;

	[[nodiscard]] virtual ApplicationEventType GetApplicationEventType() const = 0;

	[[nodiscard]] int GetType() const override { return EventType::ApplicationEvent; }

	static EventType GetStaticType() { return EventType::ApplicationEvent; }

	[[nodiscard]] std::string GetName() const override { return "ApplicationEvent"; }

	[[nodiscard]] std::string ToString() const override { return GetName(); }
};

class AppLaunchedEvent final : public ApplicationEvent
{
public:
	AppLaunchedEvent() = default;

	[[nodiscard]] ApplicationEventType GetApplicationEventType() const override { return AppLaunched; }

	[[nodiscard]] std::string GetName() const override { return "AppLaunchedEvent"; }

	[[nodiscard]] std::string ToString() const override { return GetName(); }
};

class AppClosedEvent final : public ApplicationEvent
{
public:
	AppClosedEvent() = default;

	[[nodiscard]] ApplicationEventType GetApplicationEventType() const override { return AppClosed; }

	[[nodiscard]] std::string GetName() const override { return "AppClosedEvent"; }

	[[nodiscard]] std::string ToString() const override { return GetName(); }
};
