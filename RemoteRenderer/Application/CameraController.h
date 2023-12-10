#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

class CameraController
{
public:
	explicit CameraController(std::shared_ptr<Camera> camera);
	virtual ~CameraController() = default;

	void SetCamera(const std::shared_ptr<Camera>& camera) { m_camera = camera; }

	virtual void Update(float delta_time);

	void SetCameraPosition(const glm::vec3& position);

	void SetCameraRotation(const glm::quat& rotation);

	[[nodiscard]] Camera* GetCamera() const;

protected:
	std::shared_ptr<Camera> m_camera;
};
