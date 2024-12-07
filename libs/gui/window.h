#pragma once

#include "dev/rei.h"

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

private:
    const int width;
    const int height;
    const std::string name;

    GLFWwindow* window = nullptr;

    void init_window();
};
}  // gui
