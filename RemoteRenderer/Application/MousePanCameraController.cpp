#include "MousePanCameraController.h"

#include <utility>

#include "InputSystem.h"

MousePanCameraController::MousePanCameraController(std::shared_ptr<Camera> camera)
	: CameraController(std::move(camera)), m_last_mouse_x(0), m_last_mouse_y(0)
{
}

glm::vec3 operator*(double lhs, const glm::vec3& vec)
{
	return glm::vec3(lhs) * vec;
}

void MousePanCameraController::PanCamera(double delta_x, double delta_y) const
{
	const glm::vec3 camera_right = normalize(cross(m_camera->GetForward(), glm::vec3(0.0f, 1.0f, 0.0f)));
	const glm::vec3 camera_up = cross(camera_right, m_camera->GetForward());
	const glm::vec3 pan = -delta_x * camera_right + delta_y * camera_up;
	m_camera->SetPosition(m_camera->GetPosition() + pan);
}

void MousePanCameraController::Update(float deltaTime)
{
	double x_pos, y_pos;
	InputSystem::GetMousePos(x_pos, y_pos);

	double delta_x = x_pos - m_last_mouse_x;
	double delta_y = y_pos - m_last_mouse_y;

	constexpr float sensitivity = 0.1f;
	delta_x *= sensitivity;
	delta_y *= sensitivity;

	PanCamera(delta_x, delta_y);

	m_last_mouse_x = x_pos;
	m_last_mouse_y = y_pos;
}
