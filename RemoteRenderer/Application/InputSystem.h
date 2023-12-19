#pragma once

class InputSystem
{
public:
	static void GetMousePos(double& x_pos, double& y_pos);
	static bool IsMouseButtonPressed(int button);
	static bool IsMouseButtonReleased(int button);
};
