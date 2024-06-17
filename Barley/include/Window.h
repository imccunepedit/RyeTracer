#ifndef APP_H
#define APP_H

#include <optional>
#include <vector>

#include <vulkan/vulkan.h>
// include "imgui.h"

class GLFWwindow;

namespace Barley {
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };
    class Window {
        public:
            void Run();


        protected:
            Window();
            virtual ~Window();

            virtual void Update() {};
            virtual void AppMenu() {};

        private:
            void CreateGLFWWindow();
            void CreateSurface();
            void CreateVulkanInstance();
            void PickPhysicalDevice();
            void CreateLogicalDevice();
            void CreateSwapChain();

            QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
            bool CheckValidationLayerSupport();
            bool IsDeviceSuitable(VkPhysicalDevice device);
            bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
            SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
            VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        private:
            GLFWwindow* m_windowHandle;
            VkInstance m_vulkanInstance;
            VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
            VkDevice m_logicalDevice;
            VkSurfaceKHR m_surface;
            VkQueue m_graphicsQueue;
            VkQueue m_presentQueue;
            VkSwapchainKHR m_swapChain;
            std::vector<VkImage> m_swapChainImages;
            VkFormat m_swapChainImageFormat;
            VkExtent2D m_swapChainExtent;
            std::vector<VkImageView> swapChainImageViews;



        //     bool showDemoWindow = false;
            bool shouldQuit = false;
            // ImVec4 clearColor = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);

    };
}


#endif // APP_H
