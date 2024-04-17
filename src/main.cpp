#include <iostream>
#include <ostream>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>

//#ifdef NDEBUG
//    const bool enableValidationLayers = true;
//#else
//    const bool enableValidationLayers = false;
//#endif
const bool enableValidationLayers = true;
const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;

void closeApp(GLFWwindow *window, VkInstance instance) {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

VkInstanceCreateInfo createVkInfo(struct VkInstanceCreateInfo createInfo, std::vector<const char*> validationLayers) {
    VkApplicationInfo appInfo{};
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = nullptr;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    return createInfo;
}

bool checkValidationSupport(std::vector<const char*> validationLayers) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for (const char* layerName : validationLayers){
        bool layerFound = false;
        for (const VkLayerProperties& layerProperties : availableLayers){
            if (strcmp(layerName, layerProperties.layerName) == 0){
                layerFound = true;
                break;
            }
        }
        if (!layerFound){
            return false;
        }
    }
    return true;
}

int main() {
    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };
    if (enableValidationLayers && !checkValidationSupport(validationLayers)) {
        std::cout << "Error in validation layers initialization" << std::endl;
    } else {
        std::cout << "Validation Layers enabled" << std::endl;
    }
    GLFWwindow* window;
    VkInstance instance;
    VkInstanceCreateInfo createInfo {};

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Game", nullptr, nullptr);

    createInfo = createVkInfo(createInfo, validationLayers);
    
    vkCreateInstance(&createInfo, nullptr, &instance);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    closeApp(window, instance);
    return 0;
}
