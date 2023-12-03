#include "Layer.h"

#include "Log.h"

Layer::Layer(std::string name)
	:m_name(std::move(name))
{
	Log::Instance().Debug("Create {} layer.", m_name);
}

Layer::~Layer()
{
}
