#include "RenderStructs.h"

vk::VertexInputBindingDescription vkUtil::GetPosColBindingDescription()
{
	vk::VertexInputBindingDescription bindingDescription;
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex2D);
	bindingDescription.inputRate = vk::VertexInputRate::eVertex;

	return bindingDescription;
}

std::array<vk::VertexInputAttributeDescription, 2> vkUtil::GetPosColAttributeDescription()
{
	std::array<vk::VertexInputAttributeDescription, 2> attributeDescriptionArr{};
	attributeDescriptionArr[0].binding = 0;
	attributeDescriptionArr[0].location = 0;
	attributeDescriptionArr[0].format = vk::Format::eR32G32Sfloat;
	attributeDescriptionArr[0].offset = 0;

	attributeDescriptionArr[1].binding = 0;
	attributeDescriptionArr[1].location = 1;
	attributeDescriptionArr[1].format = vk::Format::eR32G32B32Sfloat;
	attributeDescriptionArr[1].offset = sizeof(Vertex2D::Position);

	return attributeDescriptionArr;
}