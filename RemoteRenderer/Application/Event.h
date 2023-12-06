#pragma once

#include <cstdint>

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
};

class MouseButtonPressedEvent final : public MouseEvent
{
public:
	explicit MouseButtonPressedEvent(const int button)
		: button(button)
	{
	}

	[[nodiscard]] MouseEventType GetMouseEventType() const override { return MouseButtonPressed; }

	[[nodiscard]] int GetButton() const { return button; }

private:
	int button;
};

class MouseButtonReleasedEvent final : public MouseEvent
{
public:
	explicit MouseButtonReleasedEvent(const int button)
		: m_button(button)
	{
	}

	[[nodiscard]] MouseEventType GetMouseEventType() const override { return MouseButtonReleased; }

	[[nodiscard]] int GetButton() const { return m_button; }

private:
	int m_button;
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
};

class KeyPressedEvent final : public KeyEvent
{
public:
	explicit KeyPressedEvent(int key_code)
		: m_key_code(key_code)
	{
	}

	[[nodiscard]] KeyEventType GetKeyEventType() const override { return KeyPressed; }

	[[nodiscard]] int GetKeyCode() const { return m_key_code; }

private:
	int m_key_code;
};

class KeyReleasedEvent final : public KeyEvent
{
public:
	explicit KeyReleasedEvent(int key_code)
		: m_key_code(key_code)
	{
	}

	[[nodiscard]] KeyEventType GetKeyEventType() const override { return KeyReleased; }

	[[nodiscard]] int GetKeyCode() const { return m_key_code; }

private:
	int m_key_code;
};

class WindowEvent : public Event
{
public:
	enum WindowEventType
	{
		WindowResized,
		WindowClosed,
		// Add other window event types as needed
	};

	~WindowEvent() override = default;

	[[nodiscard]] virtual WindowEventType GetWindowEventType() const = 0;

	[[nodiscard]] int GetType() const override { return EventType::WindowEvent; }
	static EventType GetStaticType() { return EventType::WindowEvent; }
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

private:
	int m_width, m_height;
};

class WindowClosedEvent final : public WindowEvent
{
public:
	WindowClosedEvent() = default;

	[[nodiscard]] WindowEventType GetWindowEventType() const override { return WindowClosed; }
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
};

class AppLaunchedEvent final : public ApplicationEvent
{
public:
	AppLaunchedEvent() = default;

	[[nodiscard]] ApplicationEventType GetApplicationEventType() const override { return AppLaunched; }
};

class AppClosedEvent final : public ApplicationEvent
{
public:
	AppClosedEvent() = default;

	[[nodiscard]] ApplicationEventType GetApplicationEventType() const override { return AppClosed; }
};
