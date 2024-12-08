#include "window.h"

#include <stdexcept>

namespace gui {

Window::Window(int width, int height, const std::string &name)
: WIDTH(width)
, HEIGHT(height)
, name(name)
{
    init_window();
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

void Window::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), nullptr, nullptr);
}

bool Window::closed() {
    return glfwWindowShouldClose(window);
}

void Window::create_surface(VkInstance instance, OUT VkSurfaceKHR& surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface!");
    }
}
} // gui
