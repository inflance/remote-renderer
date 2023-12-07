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

	virtual void OnEvent(const ::Event* event){};

private:
	std::string m_name{};
};
