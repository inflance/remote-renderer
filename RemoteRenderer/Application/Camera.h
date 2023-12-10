#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
	enum class Type
	{
		None,
		Perspective,
		Orthographic
	};

	Camera(float fov, float aspect_ratio, float near_clip, float far_clip);
	Camera(float left, float right, float bottom, float top, float near_clip, float far_clip);

	void SetPosition(const glm::vec3& position);

	void SetRotation(const glm::quat& rotation);

	[[nodiscard]] Type GetCameraType() const { return m_type; }

	[[nodiscard]] const glm::mat4& getProjectionMatrix() const { return m_proj_mat; }

	[[nodiscard]] const glm::mat4& getViewMatrix() const { return m_view_mat; }

	[[nodiscard]] glm::mat4 GetViewProjectionMatrix() const { return m_view_mat * m_proj_mat; }

	void SetProjectMatrixByPerspective(float fov, float aspect_ratio, float near_clip, float far_clip);
	void SetProjectMatrixByOrthographic(float left, float right, float bottom, float top, float near_clip,
	                                    float far_clip);
	[[nodiscard]] const glm::vec3& GetPosition() const { return m_position; }
	[[nodiscard]] glm::vec3 GetForward() const;

	static std::shared_ptr<Camera> CreateByPerspective(float fov, float aspect_ratio, float near_clip, float far_clip);
	static std::shared_ptr<Camera> CreateByOrthographic(float left, float right, float bottom, float top,
	                                                    float near_clip,
	                                                    float far_clip);

protected:
	void UpdateViewMatrix();

protected:
	glm::mat4 m_view_mat{};
	glm::mat4 m_proj_mat{};

	glm::vec3 m_position{};
	glm::quat m_rotation{};

	Type m_type = Type::None;
};
