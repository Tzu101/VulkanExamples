#include "window.h"

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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
}

bool Window::closed() {
    return glfwWindowShouldClose(window);
}
}  // gui
