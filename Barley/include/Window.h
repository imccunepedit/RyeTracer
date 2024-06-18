#ifndef APP_H
#define APP_H

#include <optional>
#include <array>
#include <vector>
#include <string>

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
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

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;
        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            return attributeDescriptions;
        }

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
            void CreateImGUI();
            void CleanImGUI();

            void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

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
            VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
            VkDevice m_logicalDevice;
            VkSurfaceKHR m_surface;
            VkQueue m_graphicsQueue;
            VkQueue m_presentQueue;
            VkRenderPass m_renderPass;
            VkPipelineLayout m_pipelineLayout;
            VkPipeline m_graphicsPipeline;
            VkCommandPool m_commandPool;
            std::vector<VkCommandBuffer> m_commandBuffers;

            VkBuffer m_vertexBuffer;
            VkDeviceMemory m_vertexBufferMemory;

            VkBuffer m_indexBuffer;
            VkDeviceMemory m_indexBufferMemory;

            std::vector<VkBuffer> m_uniformBuffers;
            std::vector<VkDeviceMemory> m_uniformBuffersMemory;
            std::vector<void*> m_uniformBuffersMapped;

            VkSwapchainKHR m_swapChain;
            VkFormat m_swapChainImageFormat;
            VkExtent2D m_swapChainExtent;
            std::vector<VkImage> m_swapChainImages;
            std::vector<VkImageView> m_swapChainImageViews;
            std::vector<VkFramebuffer> m_swapChainFramebuffers;

            std::vector<VkSemaphore> m_imageAvailableSemaphores;
            std::vector<VkSemaphore> m_renderFinishedSemaphores;
            std::vector<VkFence> m_inFlightFences;

            VkDescriptorPool m_descriptorPool;
            VkDescriptorSetLayout m_descriptorSetLayout;
            std::vector<VkDescriptorSet> m_descriptorSets;

            VkDebugUtilsMessengerEXT m_debugMessenger;

            const std::vector<Vertex> vertices = {
                {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
                {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
            };
            const std::vector<uint16_t> indices = {
                0, 1, 2, 2, 3, 0
            };

            bool m_framebufferResized = false;
            uint32_t m_frameIndex = 0;
            // bool showDemoWindow = false;
            bool shouldQuit = false;

    };
}


#endif // APP_H
