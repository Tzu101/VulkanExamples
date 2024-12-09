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

    int get_width() const {
        return width;
    }
    int get_height() const {
        return height;
    }
    VkExtent2D get_extent() const {
        return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
    }

    bool has_size() const {
        return width > 0 and height > 0;
    }
    bool was_resized() const {
        return resized;
    }
    void resize_registered() {
        resized = false;
    }

private:
    int width;
    int height;
    bool resized;

    const std::string name;
    GLFWwindow* window = nullptr;

    void init_window();

    static void resize_ballback(GLFWwindow* window, int width, int height);
};
}  // gui
