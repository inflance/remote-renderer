#pragma once

#include <condition_variable>
#include <functional>
#include <memory>
#include <queue>
#include <vector>

#include "Event.h"

class EventDispatcher
{
public:
	using EventCallback = std::function<void(const Event&)>;

	EventDispatcher() = default;
	~EventDispatcher() = default;

	void AddEventListener(const EventCallback& callback)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_event_callbacks.emplace_back(callback);
	}

	void EnqueueEvent(const std::shared_ptr<Event>& event)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_event_queue.push(event);
		m_condition_variable.notify_one();
	}

	void ProcessEvents()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_condition_variable.wait(lock, [this] { return !m_event_queue.empty(); });

			auto event = m_event_queue.front();
			m_event_queue.pop();
			lock.unlock();

			DispatchEvent(*event);
		}
	}

private:
	std::mutex m_mutex;
	std::condition_variable m_condition_variable;
	std::vector<EventCallback> m_event_callbacks;
	std::queue<std::shared_ptr<Event>> m_event_queue;

	void DispatchEvent(const Event& event)
	{
		for (auto& callback : m_event_callbacks)
		{
			callback(event);
		}
	}
};
