#include "app.h"

#include <iostream>

namespace gui {

App::App(const std::string &name)
: window(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, name)
{}

void App::run() {
    while (not window.closed()) {
        glfwPollEvents();
        draw();
    }

    vkDeviceWaitIdle(device.device());
}

void App::draw() {
    std::cout << "App update" << std::endl;
}
} // gui