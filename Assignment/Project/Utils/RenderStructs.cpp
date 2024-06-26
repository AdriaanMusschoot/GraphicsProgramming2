#include "RenderStructs.h"

std::vector<vk::VertexInputBindingDescription> vkUtil::Vertex2D::GetBindingDescription()
{
	std::vector<vk::VertexInputBindingDescription> bindingDescriptionVec;
	bindingDescriptionVec.emplace_back(vk::VertexInputBindingDescription{ 0, sizeof(Vertex2D), vk::VertexInputRate::eVertex });

	return bindingDescriptionVec;
}

std::vector<vk::VertexInputAttributeDescription> vkUtil::Vertex2D::GetAttributeDescription()
{
	std::vector<vk::VertexInputAttributeDescription> attributeDescriptionVec{};

	attributeDescriptionVec.emplace_back(vk::VertexInputAttributeDescription{ 0, 0, vk::Format::eR32G32Sfloat, 0 });
	attributeDescriptionVec.emplace_back(vk::VertexInputAttributeDescription{ 1, 0, vk::Format::eR32G32Sfloat, sizeof(Vertex2D::Position) });

	return attributeDescriptionVec;
}

std::vector<vk::VertexInputBindingDescription> vkUtil::Vertex3D::GetBindingDescription()
{
	std::vector<vk::VertexInputBindingDescription> bindingDescriptionVec;
	bindingDescriptionVec.emplace_back(vk::VertexInputBindingDescription{ 0, sizeof(Vertex3D), vk::VertexInputRate::eVertex });

	return bindingDescriptionVec;
}

std::vector<vk::VertexInputAttributeDescription> vkUtil::Vertex3D::GetAttributeDescription()
{
	std::vector<vk::VertexInputAttributeDescription> attributeDescriptionVec{};

	attributeDescriptionVec.emplace_back(vk::VertexInputAttributeDescription{ 0, 0, vk::Format::eR32G32B32Sfloat, 0 });
	attributeDescriptionVec.emplace_back(vk::VertexInputAttributeDescription{ 1, 0, vk::Format::eR32G32B32Sfloat, sizeof(Vertex3D::Position) });
	attributeDescriptionVec.emplace_back(vk::VertexInputAttributeDescription{ 2, 0, vk::Format::eR32G32Sfloat, sizeof(Vertex3D::Position) + sizeof(Vertex3D::Normal) });

	return attributeDescriptionVec;
}
