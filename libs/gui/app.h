#pragma once

#include "window.h"

namespace gui {

class App {
public:
    App(const std::string& name);

    void run();

protected:
    Window window;

    virtual void update() = 0;

private:
    static constexpr int DEFAULT_WINDOW_WIDTH = 800;
    static constexpr int DEFAULT_WINDOW_HEIGHT = 600;
};
}  // gui