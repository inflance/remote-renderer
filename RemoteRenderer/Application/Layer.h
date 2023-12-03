#pragma once

#include <string>

class Layer
{
public:
	explicit Layer(std::string name = {});
	virtual ~Layer();

	virtual void Init(){}
	virtual void Shutdown(){}
	virtual void Update(float delta_time) {}

	virtual bool Event() { return true; }

private:
	std::string m_name{};
};
