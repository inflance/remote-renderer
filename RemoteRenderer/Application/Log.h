#pragma once

#include <memory>
#include <spdlog/spdlog.h>

#include "Singleton.h"

class Log : public Singleton<Log>
{
public:
	void Init();
	void Shutdown() const;

	spdlog::logger* GetLogger() const { return m_logger.get(); }

	template <typename... Args>
	void Error(Args&&... args)
	{
		if (m_logger)
		{
			m_logger->error(std::forward<Args>(args)...);
		}
	}

	template <typename... Args>
	void Info(Args&&... args)
	{
		if (m_logger)
		{
			m_logger->info(std::forward<Args>(args)...);
		}
	}

	template <typename... Args>
	void Warn(Args&&... args)
	{
		if (m_logger)
		{
			m_logger->warn(std::forward<Args>(args)...);
		}
	}

	template <typename... Args>
	void Debug(Args&&... args)
	{
		if (m_logger)
		{
			m_logger->debug(std::forward<Args>(args)...);
		}
	}

	template <typename... Args>
	void Critical(Args&&... args)
	{
		if (m_logger)
		{
			m_logger->critical(std::forward<Args>(args)...);
		}
	}

private:
	std::shared_ptr<spdlog::logger> m_logger = nullptr;
};
