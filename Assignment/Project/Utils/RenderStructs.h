#ifndef VK_RENDERSTRUCTS_H
#define VK_RENDERSTRUCTS_H
#include "Engine/Configuration.h"

namespace vkUtil
{
	struct Vertex2D
	{
		glm::vec2 Position;
		glm::vec3 Color;
	};

	struct ObjectData
	{
		glm::mat4 Model;
	};

	vk::VertexInputBindingDescription GetPosColBindingDescription();

	std::array<vk::VertexInputAttributeDescription, 2> GetPosColAttributeDescription();
}

#endif