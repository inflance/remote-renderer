#include "MousePanCameraController.h"

#include <utility>
#include <GLFW/glfw3.h>

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
	if (const auto inf = isinf(pan); inf.x || inf.y || inf.z)
		return;
	m_camera->SetPosition(m_camera->GetPosition() + pan);
}

void MousePanCameraController::ZoomCamera(double delta_x, double delta_y) const
{
	constexpr float zoom_speed = 0.1f; // 调整缩放速度
	const float zoom = zoom_speed * static_cast<float>(delta_x + delta_y);
	if (const auto inf = isinf(zoom))
		return;
	m_camera->SetPosition(m_camera->GetPosition() + zoom * m_camera->GetForward());
}

void MousePanCameraController::RotateCamera(double delta_x, double delta_y) const
{
	constexpr float rotate_speed = 0.1f; // 调整旋转速度
	const glm::quat rotation = angleAxis(rotate_speed * static_cast<float>(delta_x), glm::vec3(0.0f, 1.0f, 0.0f))
		* angleAxis(rotate_speed * static_cast<float>(delta_y), glm::vec3(1.0f, 0.0f, 0.0f));
	m_camera->SetRotation(rotation + m_camera->GetRotation());
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
	if (InputSystem::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		RotateCamera(delta_x, delta_y);
	}
	if (InputSystem::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		PanCamera(delta_x, delta_y);
	}
	if (InputSystem::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		ZoomCamera(delta_x, delta_y);
	}
	m_last_mouse_x = x_pos;
	m_last_mouse_y = y_pos;
}
