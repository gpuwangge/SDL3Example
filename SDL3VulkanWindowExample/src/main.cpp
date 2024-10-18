/*
 * Vulkan Windowed Program
 *
 * Copyright (C) 2016, 2018 Valve Corporation
 * Copyright (C) 2016, 2018 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
Vulkan Windowed Project Template
Create and destroy a Vulkan surface on an SDL window.
*/

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


//#include <SDL2/SDL.h>
//#include <SDL2/SDL_syswm.h>
//#include <SDL2/SDL_vulkan.h>
//#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
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
    //SDL_SetAppMetadata("Example Renderer Geometry", "1.0", "com.example.renderer-geometry");

    // Create an SDL window that supports Vulkan rendering.
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Could not initialize SDL." << std::endl;
        return 1;
    }
    //SDL_Window* window = SDL_CreateWindow("Vulkan Window", SDL_WINDOWPOS_CENTERED,
    //    SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_VULKAN);
    SDL_Window* window = SDL_CreateWindow("Vulkan Window", 1280, 720, SDL_WINDOW_VULKAN);
    if(window == NULL) {
        std::cout << "Could not create SDL window." << std::endl;
        return 1;
    }

    std::cout << "Debug: after create window" << std::endl;

    // Get WSI extensions from SDL (we can add more if we like - we just can't remove these)
    //unsigned extension_count;
    //if(!SDL_Vulkan_GetInstanceExtensions(window, &extension_count, NULL)) {
    //if(!SDL_Vulkan_GetInstanceExtensions(&extension_count)) {
    //    std::cout << "Could not get the number of required instance extensions from SDL." << std::endl;
    //    return 1;
    //}
    //std::vector<const char*> extensions(extension_count);
    //if(!SDL_Vulkan_GetInstanceExtensions(window, &extension_count, extensions.data())) {
    //if(!(extensions = SDL_Vulkan_GetInstanceExtensions(&extension_count))) {
    //    std::cout << "Could not get the names of required instance extensions from SDL." << std::endl;
    //    return 1;
    //}

    std::cout << "Debug: after SDL_Vulkan_GetInstanceExtensions" << std::endl;

    Uint32 count_instance_extensions;
    const char * const *instance_extensions = SDL_Vulkan_GetInstanceExtensions(&count_instance_extensions);

    std::cout << "Debug: count_instance_extensions = " << count_instance_extensions << std::endl;
    std::cout << "Debug: instance_extensions = " << std::endl;;
    for(int i = 0; i < count_instance_extensions; i++)
        std::cout << instance_extensions[i] << std::endl;

    // int count_extensions = count_instance_extensions + 1;
    // const char **extensions = SDL_malloc(count_extensions * sizeof(const char *));
    // extensions[0] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
    // SDL_memcpy(&extensions[1], instance_extensions, count_instance_extensions * sizeof(const char*)); 

    // Use validation layers if this is a debug build
    std::vector<const char*> layers;
#if defined(_DEBUG)
    layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

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

    // VkInstanceCreateInfo is where the programmer specifies the layers and/or extensions that
    // are needed.
    VkInstanceCreateInfo instInfo = {};
    instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instInfo.pNext = NULL;
    instInfo.flags = 0;
    instInfo.pApplicationInfo = &appInfo;
    //instInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    instInfo.enabledExtensionCount = static_cast<uint32_t>(count_instance_extensions);
    //instInfo.ppEnabledExtensionNames = extensions.data();
    instInfo.ppEnabledExtensionNames = instance_extensions;
    instInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
    instInfo.ppEnabledLayerNames = layers.data();

    std::cout << "Debug: before create instance" << std::endl;

    // Create the Vulkan instance.
    VkInstance instance;
    VkResult result = vkCreateInstance(&instInfo, NULL, &instance);
    
    std::cout << "Debug: after create instance" << std::endl;

    if(result == VK_ERROR_INCOMPATIBLE_DRIVER) {
        std::cout << "Unable to find a compatible Vulkan Driver." << std::endl;
        return 1;
    } else if(result) {
        std::cout << "Could not create a Vulkan instance (for unknown reasons)." << std::endl;
        return 1;
    }

    

    // Create a Vulkan surface for rendering
    VkSurfaceKHR surface;
    // if(!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
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
