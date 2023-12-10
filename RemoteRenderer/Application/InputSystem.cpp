#include "InputSystem.h"

#include "Application.h"

void InputSystem::GetMousePos(double& x_pos, double& y_pos)
{
	const auto window = Application::Instance().GetWindow();
	window->GetMousePos(x_pos, y_pos);
}
