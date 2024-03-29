#pragma once
#include "vulkanbase/VulkanUtil.h"
#include "GP2Shader.h"

namespace amu
{

	class GraphicsPipeline
	{
	public:
		void CreateGraphicsPipeline(VkDevice device, Shader& shader, VkRenderPass renderPass);
		void DrawFrame(const VkCommandBuffer& commandBuffer, VkExtent2D swapchainExtent);
		void Destroy();
		//Main thin that should be configurable is the shaders u use in the pipeline
		//You could make one massive struct render context to pass to here
	private:
		VkPipeline m_GraphicsPipeline;
		VkPipelineLayout m_PipelineLayout;

		VkDevice m_Device;
	};

}