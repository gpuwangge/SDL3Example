// Enable the WSI extensions
#if defined(__ANDROID__)
#define VK_USE_PLATFORM_ANDROID_KHR
#elif defined(__linux__)
#define VK_USE_PLATFORM_XLIB_KHR
#elif defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

// Tell SDL not to mess with main()
#define SDL_MAIN_HANDLED

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_vulkan.h>

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

//int main()
int main(int argc, char* argv[])
{
    SDL_SetAppMetadata("Example Renderer Geometry", "1.0", "com.example.renderer-geometry");

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Could not initialize SDL." << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Vulkan Window", 1280, 720, SDL_WINDOW_VULKAN);
    if(window == NULL) {
        std::cout << "Could not create SDL window." << std::endl;
        return 1;
    }

    Uint32 count_instance_extensions;
    const char * const *instance_extensions = SDL_Vulkan_GetInstanceExtensions(&count_instance_extensions);
    std::vector<const char*> requiredInstanceExtensions;
    requiredInstanceExtensions.resize(count_instance_extensions);
    for(int i = 0; i < count_instance_extensions; i++) requiredInstanceExtensions[i] = instance_extensions[i];
    requiredInstanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    std::cout << "requiredInstanceExtensions.size() = " << requiredInstanceExtensions.size() << std::endl;
    std::cout << "requiredInstanceExtensions = " << std::endl;
    for(int i = 0; i < requiredInstanceExtensions.size(); i++)
        std::cout << "    " << requiredInstanceExtensions[i] << std::endl;

    // Use validation layers if this is a debug build
    std::vector<const char*> requiredInstanceLayers;
#if defined(_DEBUG)
    requiredInstanceLayers.push_back("VK_LAYER_KHRONOS_validation");
#endif
    std::cout << "requiredInstanceLayers = " << std::endl;
    for(int i = 0; i < requiredInstanceLayers.size(); i++)
        std::cout << "    " << requiredInstanceLayers[i] << std::endl;

    // VkApplicationInfo allows the programmer to specifiy some basic information about the
    // program, which can be useful for layers and tools to provide more debug information.
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = NULL;
    appInfo.pApplicationName = "Vulkan Program Template";
    appInfo.applicationVersion = 1;
    appInfo.pEngineName = "LunarG SDK";
    appInfo.engineVersion = 1;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // VkInstanceCreateInfo is where the programmer specifies the layers and/or extensions that are needed.
    VkInstanceCreateInfo instInfo = {};
    instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instInfo.pNext = NULL;
    instInfo.flags = 0;
    instInfo.pApplicationInfo = &appInfo;
    //instInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instInfo.enabledExtensionCount = static_cast<uint32_t>(count_instance_extensions);
    //instInfo.ppEnabledExtensionNames = extensions.data();
    instInfo.ppEnabledExtensionNames = requiredInstanceExtensions.data();
    instInfo.enabledLayerCount = static_cast<uint32_t>(requiredInstanceLayers.size());
    instInfo.ppEnabledLayerNames = requiredInstanceLayers.data();

    // Create the Vulkan instance.
    VkInstance instance;
    VkResult result = vkCreateInstance(&instInfo, NULL, &instance);

    if(result == VK_ERROR_INCOMPATIBLE_DRIVER) {
        std::cout << "Unable to find a compatible Vulkan Driver." << std::endl;
        return 1;
    } else if(result) {
        std::cout << "Could not create a Vulkan instance (for unknown reasons)." << std::endl;
        return 1;
    }

    VkSurfaceKHR surface;
    if(!SDL_Vulkan_CreateSurface(window, instance, NULL, &surface)) {
        std::cout << "Could not create a Vulkan surface." << std::endl;
        return 1;
    }

    // This is where most initializtion for a program should be performed

    // Poll for user input.
    unsigned debugCount = 0;
    bool stillRunning = true;
    while(stillRunning) {
        debugCount++;
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            std::cout << "Debug: while loop: " <<debugCount<< std::endl;
            switch(event.type) {
                case SDL_EVENT_QUIT:
                    stillRunning = false;
                    break;
                default:
                    // Do nothing.
                    break;
            }
        }

        SDL_Delay(10);
    }

    // Clean up.
    vkDestroySurfaceKHR(instance, surface, NULL);
    SDL_DestroyWindow(window);
    SDL_Quit();
    vkDestroyInstance(instance, NULL);

    return 0;
}
