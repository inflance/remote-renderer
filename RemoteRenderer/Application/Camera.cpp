#include "Camera.h"

Camera::Camera(float fov, float aspect_ratio, float near_clip, float far_clip)
{
	SetProjectMatrixByPerspective(fov, aspect_ratio, near_clip, far_clip);
	m_view_mat = glm::mat4(1.0f);
}

Camera::Camera(float left, float right, float bottom, float top, float near_clip, float far_clip)
{
	SetProjectMatrixByOrthographic(left, right, bottom, top, near_clip, far_clip);
	m_view_mat = glm::mat4(1.0f);
}

void Camera::SetPosition(const glm::vec3& position)
{
	m_position = position;
	UpdateViewMatrix();
}

void Camera::SetRotation(const glm::quat& rotation)
{
	m_rotation = rotation;
	UpdateViewMatrix();
}

void Camera::SetProjectMatrixByPerspective(float fov, float aspect_ratio, float near_clip, float far_clip)
{
	m_proj_mat = glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
	m_type = Type::Perspective;
}

void Camera::SetProjectMatrixByOrthographic(float left, float right, float bottom, float top, float near_clip,
                                            float far_clip)
{
	m_proj_mat = glm::ortho(left, right, bottom, top, near_clip, far_clip);
	m_type = Type::Orthographic;
}

glm::vec3 Camera::GetForward() const
{
	return normalize(rotate(m_rotation, glm::vec3(0.0f, 0.0f, -1.0f)));
}

std::shared_ptr<Camera> Camera::CreateByPerspective(float fov, float aspect_ratio, float near_clip, float far_clip)
{
	return std::make_shared<Camera>(fov, aspect_ratio, near_clip, far_clip);
}

std::shared_ptr<Camera> Camera::CreateByOrthographic(float left, float right, float bottom, float top, float near_clip,
                                                     float far_clip)
{
	return std::make_shared<Camera>(left, right, bottom, top, near_clip, far_clip);
}

void Camera::UpdateViewMatrix()
{
	const glm::mat4 translation_matrix = translate(glm::mat4(1.0f), -m_position);
	const glm::mat4 rotation_matrix = toMat4(m_rotation);
	m_view_mat = rotation_matrix * translation_matrix;
}
