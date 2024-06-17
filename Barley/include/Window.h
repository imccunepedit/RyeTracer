#ifndef APP_H
#define APP_H

#include <optional>

#include <vulkan/vulkan.h>
// include "imgui.h"

class GLFWwindow;

namespace Barley {
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;

        bool IsComplete()
        {
            return graphicsFamily.has_value();
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

            QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
            bool CheckValidationLayerSupport();
            bool IsDeviceSuitable(VkPhysicalDevice);

        private:
            GLFWwindow* m_windowHandle;
            VkInstance m_vulkanInstance;
            VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
            VkDevice m_logicalDevice;
            VkQueue m_graphicsQueue;
            VkSurfaceKHR m_surface;


        //     bool showDemoWindow = false;
            bool shouldQuit = false;
            // ImVec4 clearColor = ImVec4(0.07f, 0.13f, 0.17f, 1.0f);

    };
}


#endif // APP_H
