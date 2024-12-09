#include "window.h"

#include <stdexcept>

namespace gui {

Window::Window(int width, int height, const std::string &name)
: width(width)
, height(height)
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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, resize_ballback);
}

bool Window::closed() {
    return glfwWindowShouldClose(window);
}

void Window::create_surface(VkInstance instance, OUT VkSurfaceKHR& surface) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface!");
    }
}

void Window::resize_ballback(GLFWwindow* resized_window, int width, int height) {
    auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(resized_window));
    window->resized = true;
    window->width = width;
    window->height = height;
}
} // gui
