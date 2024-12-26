#ifndef WINDOW_H_
#define WINDOW_H_

#include <optional>
#include <vector>
#include <string>

#include <vulkan/vulkan.h>

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

            virtual void Update() = 0;
            virtual void ImGuiDraw() = 0;
            virtual void AppMenu() = 0;

        private:
            void Init();
            void InitGlfw();
            void InitVulkan();
            void InitImGui();

            void Close();
            void CleanImGui();
            void CleanVulkan();
            void CleanGlfw();


        private:
            // vulkan initialization functions
            void CreateSurface();
            void CreateVulkanInstance();
            void PickPhysicalDevice();
            void CreateLogicalDevice();
            void CreateSwapChain();
            void CleanSwapChain();
            void RecreateSwapChain();
            void CreateImageViews();
            void CreateGraphicsPipeline();
            void CreateRenderPass();
            void CreateFramebuffers();
            void CreateCommandPool();
            void CreateCommandBuffers();
            void CreateVertexBuffer();
            void CreateIndexBuffer();
            void CreateUniformBuffers();
            void CreateSyncObjects();
            void CreateDescriptorPool();
            void CreateDescriptorSets();
            void CreateDescriptorSetLayout();

            // vulkan functions during frame
            void StartRecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
            void EndRecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);


            QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
            bool IsDeviceSuitable(VkPhysicalDevice device);
            bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
            SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
            VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
            VkShaderModule CreateShaderModule(const std::vector<char>& code);
            static std::vector<char> ReadFile(const std::string& filename);


            void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
            VkCommandBuffer BeginSingleTimeCommands();

            static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

            void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
            void SetupDebugMessenger();
            std::vector<const char*> GetRequiredExtensions();
            bool CheckValidationLayerSupport();
            static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
            uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
            void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
            void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

            void UpdateUniformBuffer(uint32_t frameIndex);


        private:
            GLFWwindow* m_windowHandle;

            VkInstance m_vulkanInstance;
            VkDebugUtilsMessengerEXT m_debugMessenger;
            VkSurfaceKHR m_surface;

            VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
            VkDevice m_logicalDevice;

            VkQueue m_graphicsQueue;
            VkQueue m_presentQueue;

            VkSwapchainKHR m_swapChain;
            std::vector<VkImage> m_swapChainImages;
            VkFormat m_swapChainImageFormat;
            VkExtent2D m_swapChainExtent;
            std::vector<VkImageView> m_swapChainImageViews;
            std::vector<VkFramebuffer> m_swapChainFramebuffers;

            VkRenderPass m_renderPass;
            VkDescriptorSetLayout m_descriptorSetLayout;
            VkPipelineLayout m_pipelineLayout;
            VkPipeline m_graphicsPipeline;

            VkCommandPool m_commandPool;


            VkBuffer m_vertexBuffer;
            VkDeviceMemory m_vertexBufferMemory;
            VkBuffer m_indexBuffer;
            VkDeviceMemory m_indexBufferMemory;

            std::vector<VkBuffer> m_uniformBuffers;
            std::vector<VkDeviceMemory> m_uniformBuffersMemory;
            std::vector<void*> m_uniformBuffersMapped;

            VkDescriptorPool m_descriptorPool;
            std::vector<VkDescriptorSet> m_descriptorSets;

            std::vector<VkCommandBuffer> m_commandBuffers;

            std::vector<VkSemaphore> m_imageAvailableSemaphores;
            std::vector<VkSemaphore> m_renderFinishedSemaphores;
            std::vector<VkFence> m_inFlightFences;

            uint32_t m_frameIndex = 0;

            bool m_framebufferResized = false;

            bool m_shouldQuit = false;
            // bool m_showDemoWindow = false;

    };
}


#endif // WINDOW_H_
