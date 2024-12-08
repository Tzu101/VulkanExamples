#pragma once

#include "dev/rei.h"
#include "dev/out.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace gui {

class Window {
public:
    Window(int width, int height, const std::string& name);
    ~Window();
    IMPLEMENT_REI(Window);

    bool closed();
    void create_surface(VkInstance instance, OUT VkSurfaceKHR& surface);

    const int width() {
        return WIDTH;
    }
    const int height() {
        return HEIGHT;
    }
    VkExtent2D get_extent() const {
        return { static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT) };
    }

private:
    const int WIDTH;
    const int HEIGHT;
    const std::string name;

    GLFWwindow* window = nullptr;

    void init_window();
};
}  // gui
