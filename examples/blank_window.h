#pragma once

#include "gui/app.h"

class BlankWindow: public gui::App {
    using gui::App::App;

protected:
    void update() override;
};
