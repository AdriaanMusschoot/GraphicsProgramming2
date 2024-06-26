#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H
#include "Engine/Configuration.h"

namespace vkInit
{

	bool CheckSupportExtensionsAndLayers(const std::vector<const char*>& requiredLayerVec, const std::vector<const char*>& requiredExtensionVec)
	{
		std::vector<vk::LayerProperties> supportedLayerVec{ vk::enumerateInstanceLayerProperties() };

		std::cout << "\nLayers supported:\n";
		for (const auto& supportedLayer : supportedLayerVec)
		{
			std::cout << "\t\"" << supportedLayer.layerName << "\"\n";
		}

		for (const auto& requiredLayers : requiredLayerVec)
		{
			bool wasFound = std::any_of(supportedLayerVec.begin(), supportedLayerVec.end(),
				[&](const vk::LayerProperties& supportedLayer)
				{
					return strcmp(requiredLayers, supportedLayer.layerName) == 0;
				});
			if (wasFound)
			{
				std::cout << "Layer: " << requiredLayers << " is supported\n";
			}
			else
			{
				std::cout << "Layer: " << requiredLayers << "is not supported\n";

				return false;
			}
		}

		std::vector<vk::ExtensionProperties> supportedExtensionVec{ vk::enumerateInstanceExtensionProperties() };

		std::cout << "\nExtensions supported:\n";
		for (const auto& supportedExtension : supportedExtensionVec)
		{
			std::cout << "\t\"" << supportedExtension.extensionName << "\"\n";
		}

		for (const auto& requiredExtension : requiredExtensionVec)
		{
			bool wasFound = std::any_of(supportedExtensionVec.begin(), supportedExtensionVec.end(),
				[&](const vk::ExtensionProperties& supportedExtension)
				{
					return strcmp(requiredExtension, supportedExtension.extensionName) == 0;
				});
			if (wasFound)
			{
				std::cout << "Extension: " << requiredExtension << " is supported\n";
			}
			else
			{
				std::cout << "Extension: " << requiredExtension << " is not supported\n";
				return false;
			}
		}

		return true;
	}

	vk::Instance CreateInstance(const std::string& name)
	{
		std::cout << "Creating instance\n";

		uint32_t versionNumber{ 0 };
		vkEnumerateInstanceVersion(&versionNumber);

		std::cout << "Supports vulkan variant: " << VK_API_VERSION_VARIANT(versionNumber) << ", version number: "
					  << VK_API_VERSION_MAJOR(versionNumber) << "."
					  << VK_API_VERSION_MINOR(versionNumber) << "."
					  << VK_API_VERSION_PATCH(versionNumber) << "\n";

		versionNumber &= ~(0xFFFU);

		versionNumber = VK_MAKE_API_VERSION(0, 1, 0, 0);

		vk::ApplicationInfo applicationInfo
		{
			name.c_str(),
			versionNumber,
			"VulkanEngine",
			versionNumber,
			versionNumber
		};

		std::vector<const char*> layerVec;

		layerVec.emplace_back("VK_LAYER_KHRONOS_validation");

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions{ glfwGetRequiredInstanceExtensions(&glfwExtensionCount) };
		
		std::vector<const char*> requiredExtensionVec(glfwExtensions, glfwExtensions + glfwExtensionCount);

		requiredExtensionVec.emplace_back("VK_EXT_debug_utils");
		

		if (not CheckSupportExtensionsAndLayers(layerVec, requiredExtensionVec))
		{
			return nullptr;
		}

		vk::InstanceCreateInfo createInfo
		{
			vk::InstanceCreateFlags{},
			&applicationInfo,
			static_cast<uint32_t>(layerVec.size()),				 //layer count
			layerVec.data(),									 //layers
			static_cast<uint32_t>(requiredExtensionVec.size()),	 //extension count
			requiredExtensionVec.data()							 //extensions
		};
		
		try
		{
			return vk::createInstance(createInfo);
		}
		catch (const vk::SystemError & systemError)
		{
			std::cout << systemError.what() << "\n";

			return nullptr;
		}
	}

}

#endif