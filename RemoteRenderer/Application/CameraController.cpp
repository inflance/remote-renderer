#include "CameraController.h"

CameraController::CameraController(std::shared_ptr<Camera> camera)
	: m_camera(std::move(camera))
{
}

void CameraController::Update(float delta_time)
{

}

void CameraController::SetCameraPosition(const glm::vec3& position)
{
	m_camera->SetPosition(position);
}

void CameraController::SetCameraRotation(const glm::quat& rotation)
{
	m_camera->SetRotation(rotation);
}
