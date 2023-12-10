#pragma once

#include "CameraController.h"

class MousePanCameraController : public CameraController
{
public:
	explicit MousePanCameraController(std::shared_ptr<Camera> camera);
	void PanCamera(double delta_x, double delta_y) const;
    void Update(float deltaTime) override;

private:
	double m_last_mouse_x{};
	double m_last_mouse_y{};
};
