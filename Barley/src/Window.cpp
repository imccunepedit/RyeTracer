#include "Window.h"

#include <iostream>
#include <cstring>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

// #include "imgui.h"
// #include "backends/imgui_impl_glfw.h"
// #include "backends/imgui_impl_vulkan.h"

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

#ifndef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = false;
#endif


using namespace Barley;

void Window::Run()
{
    while (!glfwWindowShouldClose(m_windowHandle) && !shouldQuit)
    {
        // tell glfw to look for events
        glfwPollEvents();

        // // tell opengl what color to make the rendered buffer
        // glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        // glClear(GL_COLOR_BUFFER_BIT);

        // ImGui_ImplVulkan_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();

        // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode); // do the docking things, make sure whats rendered in the background can still be seen


        Update();


        // // show a menu bar, useful for demo window and quitting the application
        // if (ImGui::BeginMainMenuBar())
        // {
        //     if (ImGui::BeginMenu("Menu"))
        //     {
        //         ImGui::MenuItem("Demo Window", NULL, &showDemoWindow);
        //         ImGui::ColorEdit4("Background (Clear) color", (float*) &clearColor, ImGuiColorEditFlags_NoInputs);
        //         ImGui::MenuItem("Quit", NULL, &shouldQuit);
        //         ImGui::EndMenu();
        //     }

        //     AppMenu();
        //     ImGui::EndMainMenuBar();
        // }

        // // show the demo window, very useful
        // if (showDemoWindow)
        //     ImGui::ShowDemoWindow();


        // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // swap the currently displayed buffer with the one that was just rendered
        glfwSwapBuffers(m_windowHandle);
    }

}


Window::Window()
{
    CreateGLFWWindow();
    CreateVulkanInstance();
    PickPhysicalDevice();
    CreateLogicalDevice();
}

Window::~Window() {
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();
    // destrou vulkan stuff
    vkDestroyDevice(m_logicalDevice, nullptr);
    vkDestroySurfaceKHR(m_vulkanInstance, m_surface, nullptr);
    vkDestroyInstance(m_vulkanInstance, nullptr);

    // tell glfw to kill our window and kill its self
    glfwDestroyWindow(m_windowHandle);
    glfwTerminate();
}

void Window::CreateGLFWWindow()
{

    // initiallize glfw and check
    if (!glfwInit())
        std::exit(1);

    // tell glfw what opengl we are using
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // create a window size x,y,title,not full screen
    m_windowHandle = glfwCreateWindow(WIDTH, HEIGHT, "m_floating Renderer", nullptr, nullptr);


    // make sure window exists
    if (m_windowHandle == nullptr)
        std::exit(2);

    // tell glfw that we want to use our window
    glfwMakeContextCurrent(m_windowHandle);
}

void Window::CreateSurface()
{
    if (glfwCreateWindowSurface(m_vulkanInstance, m_windowHandle, nullptr, &m_surface) != VK_SUCCESS)
        throw std::runtime_error("ERROR: failed to create window surface");
}

void Window::CreateVulkanInstance()
{
    if (enableValidationLayers && !CheckValidationLayerSupport())
    {
        throw std::runtime_error("ERROR: requested validation layers not available");
    }

    VkApplicationInfo appInfo{}; // create a struct with information about our
                                 // app, not strictly nesecary but could be used
                                 // to optimize our app.
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hellos";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{}; // a struct containing info that is
                                       // needed to create a vulkan instance
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtentionCount = 0;
    const char** glfwExtensions;
    std::vector<const char*> requiredExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);

    // need to add portabilit enum ext so unwrap the extensions
    for(uint32_t i = 0; i < glfwExtentionCount; i++) {
        requiredExtensions.emplace_back(glfwExtensions[i]);
    }
    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR; // on macos might be needed

    if (enableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

#ifndef NDEBUG
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions" << std::endl;

    for (const auto& extension : extensions)
    {
        std::cout << "\t" << extension.extensionName << std::endl;
    }
#endif

    if (vkCreateInstance(&createInfo, nullptr, &m_vulkanInstance) != VK_SUCCESS)
        throw std::runtime_error("ERROR: failed to create vulkan instance");
}

void Window::PickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_vulkanInstance, &deviceCount, nullptr);
    if (deviceCount == 0)
        throw std::runtime_error("ERROR: failed to find gpus with vulkan support");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_vulkanInstance, &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        if (IsDeviceSuitable(device))
        {
            m_physicalDevice = device;
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("ERROR: failed to find a suitable GPU!");
    }

}

void Window::CreateLogicalDevice()
{
    QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS) {
        throw std::runtime_error("ERROR: failed to create logical device");
    }

    vkGetDeviceQueue(m_logicalDevice, indices.graphicsFamily.value(), 0, &m_graphicsQueue);


}

bool Window::IsDeviceSuitable(VkPhysicalDevice device)
{
    // VkPhysicalDeviceProperties deviceProperties;
    // VkPhysicalDeviceFeatures deviceFeatures;

    // vkGetPhysicalDeviceProperties(device, &deviceProperties);
    // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    QueueFamilyIndices indices = FindQueueFamilies(device);

    return indices.IsComplete();
}

QueueFamilyIndices Window::FindQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queuFamily : queueFamilies)
    {
        if (queuFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;
        if (indices.IsComplete())
            break;

        ++i;
    }


    return indices;
}

bool Window::CheckValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers)
    {
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }
    return false;
}



    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //     std::exit(3);

    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // ImGui::StyleColorsDark();

    // ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
    // ImGui_ImplOpenGL3_Init("#version 330");
