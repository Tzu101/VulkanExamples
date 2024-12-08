#pragma once

#include "gui/app.h"

#include "engine/device.h"
#include "engine/pipeline.h"

class StaticTriangle: public gui::App {
    using gui::App::App;

protected:
    void update() override;

private:
    engine::Device device{window};
    engine::Pipeline pipeline{
        device, 
        engine::Pipeline::Config::get_default(window.width(), window.height()), 
        "shaders/static_triangle.vert.spv", 
        "shaders/static_triangle.frag.spv"
    };
};
