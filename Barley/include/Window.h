#ifndef APP_H
#define APP_H

#include <optional>
#include <vector>
#include <string>

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
            void CreateImageViews();
            void CreateGraphicsPipeline();
            void CreateRenderPass();
            void CreateFramebuffers();
            void CreateCommandPool();
            void CreateCommandBuffer();
            void CreateSyncObjects();

            QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
            bool IsDeviceSuitable(VkPhysicalDevice device);
            bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
            SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
            VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
            VkShaderModule CreateShaderModule(const std::vector<char>& code);
            static std::vector<char> ReadFile(const std::string& filename);
            void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);


            void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
            void SetupDebugMessenger();
            std::vector<const char*> GetRequiredExtensions();
            bool CheckValidationLayerSupport();
            static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);


        private:
            GLFWwindow* m_windowHandle;
            VkInstance m_vulkanInstance;
            VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
            VkDevice m_logicalDevice;
            VkSurfaceKHR m_surface;
            VkQueue m_graphicsQueue;
            VkQueue m_presentQueue;
            VkRenderPass m_renderPass;
            VkPipelineLayout m_pipelineLayout;
            VkPipeline m_graphicsPipeline;

            VkCommandPool m_commandPool;
            VkCommandBuffer m_commandBuffer;

            VkSwapchainKHR m_swapChain;
            VkFormat m_swapChainImageFormat;
            VkExtent2D m_swapChainExtent;
            std::vector<VkImage> m_swapChainImages;
            std::vector<VkImageView> m_swapChainImageViews;
            std::vector<VkFramebuffer> m_swapChainFramebuffers;

            VkSemaphore m_imageAvailableSemaphore;
            VkSemaphore m_renderFinishedSemaphore;
            VkFence m_inFlightFence;

            VkDebugUtilsMessengerEXT m_debugMessenger;
            // bool showDemoWindow = false;
            bool shouldQuit = false;

    };
}


#endif // APP_H
