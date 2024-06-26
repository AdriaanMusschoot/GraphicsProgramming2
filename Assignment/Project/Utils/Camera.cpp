#include "Camera.h"
#include "Engine/Clock.h"

ave::Camera::Camera(GLFWwindow* windowPtr, const glm::vec3& origin, float fovAngle, int width, int height)
	: m_Origin{ origin }
	, m_FovAngle{ fovAngle }
	, m_AspectRatio{ static_cast<float>(width) / static_cast<float>(height) }
	, m_WindowPtr{ windowPtr }
{
	m_Fov = tanf(glm::radians(m_FovAngle)/ 2.f);
	CalculateProjectionMatrix(width, height);
	CalculateViewMatrix();
}

void ave::Camera::CalculateViewMatrix()
{
	m_Right = glm::cross(glm::vec3{ 0, 1, 0 }, m_Forward);
	m_Right = glm::normalize(m_Right);

	m_Up = glm::cross(m_Right, m_Forward);
	m_Up = glm::normalize(m_Up);

	m_ViewMatrix = glm::lookAt(m_Origin, m_Origin + m_Forward, m_Up);
}

void ave::Camera::CalculateProjectionMatrix(int width, int height)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FovAngle), m_AspectRatio, m_NearPlane, m_FarPlane);
}

void ave::Camera::Update()
{
	const float deltaTime{ static_cast<float>(ave::Clock::GetInstance().GetDeltaTime()) };

	bool calculateCameraMatrix{ false };

	float speedTranslation
	{
		[&]() -> float
		{
			if (glfwGetKey(m_WindowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			{
				return m_SpeedTranslation * 5;
			}
			else
			{
				return m_SpeedTranslation;
			}
		}()
	};

	if (glfwGetKey(m_WindowPtr, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(m_WindowPtr, GLFW_KEY_UP) == GLFW_PRESS)
	{
		m_Origin += m_Forward * speedTranslation * deltaTime;
		calculateCameraMatrix = true;
	}
	if (glfwGetKey(m_WindowPtr, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(m_WindowPtr, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		m_Origin -= m_Forward * speedTranslation * deltaTime;
		calculateCameraMatrix = true;
	}
	if (glfwGetKey(m_WindowPtr, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(m_WindowPtr, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		m_Origin += m_Right * speedTranslation * deltaTime;
		calculateCameraMatrix = true;
	}
	if (glfwGetKey(m_WindowPtr, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(m_WindowPtr, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		m_Origin -= m_Right * speedTranslation * deltaTime;
		calculateCameraMatrix = true;
	}

	double mousePositionX;
	double mousePositionY;
	glfwGetCursorPos(m_WindowPtr, &mousePositionX, &mousePositionY);

	double deltaMouseX{ mousePositionX - m_LastMousePositionX };
	double deltaMouseY{ mousePositionY - m_LastMousePositionY };

	m_LastMousePositionX = mousePositionX;
	m_LastMousePositionY = mousePositionY;

	if (glfwGetMouseButton(m_WindowPtr, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS and glfwGetMouseButton(m_WindowPtr, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		m_Origin.y += m_Up.y * deltaMouseY * speedTranslation * deltaTime * 10;
		calculateCameraMatrix = true;
	}
	else if (glfwGetMouseButton(m_WindowPtr, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		m_TotalYaw += deltaMouseX * m_SpeedRotation * deltaTime;
		m_TotalPitch += deltaMouseY * m_SpeedRotation * deltaTime;

		//takes in current matrix and assigns the new value to it
		glm::mat4 rotationMatrix{ 1.0f };
		rotationMatrix = glm::rotate(rotationMatrix, static_cast<float>(m_TotalYaw), glm::vec3{ 0, 1, 0 });
		rotationMatrix = glm::rotate(rotationMatrix, static_cast<float>(m_TotalPitch), glm::vec3{ 1, 0, 0 });
		m_Forward = rotationMatrix * glm::vec4{ 0, 0, 1, 0 };
		m_Forward = glm::normalize(m_Forward);
		calculateCameraMatrix = true;
	}
	if (calculateCameraMatrix)
	{
		CalculateViewMatrix();
	}
}

const glm::mat4& ave::Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

const glm::mat4& ave::Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

const glm::vec3& ave::Camera::GetCameraPosition() const
{
	return m_Origin;
}
