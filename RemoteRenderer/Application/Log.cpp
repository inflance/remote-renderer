#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

void Log::Init()
{
	m_logger = spdlog::stdout_color_mt("RemoteApp");
	m_logger->set_level(spdlog::level::debug);
}

void Log::Shutdown() const
{
	m_logger->flush();
}
