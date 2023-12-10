#include "MousePanCameraController.h"

#include <utility>

#include "InputSystem.h"

MousePanCameraController::MousePanCameraController(std::shared_ptr<Camera> camera)
	: CameraController(std::move(camera)), m_last_mouse_x(0), m_last_mouse_y(0)
{
}

void MousePanCameraController::PanCamera(double delta_x, double delta_y) const
{
	const glm::vec3 camera_forward = m_camera->GetForward();
	const glm::vec3 camera_right = normalize(cross(camera_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	const glm::vec3 camera_up = cross(camera_right, camera_forward);

	// 假设 delta_x 用于水平平移，delta_y 用于垂直平移
	constexpr float pan_speed = 0.1f; // 调整平移速度
	const glm::vec3 pan = pan_speed * (glm::vec3(delta_x) * camera_right + glm::vec3(delta_y) * camera_up);
	const auto inf = glm::isinf(pan);
	if (inf.x || inf.y || inf.z)
		return;
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
