#pragma once

#include "gui/app.h"

class BlankWindow: public gui::App {
public:
    BlankWindow();

protected:
    void draw() override;
};
