#pragma once

#include "gui/app.h"

#include "engine/pipeline.h"
#include "engine/swap_chain.h"
#include "engine/model.h"

#include <vector>
#include <memory>

class StaticTriangle: public gui::App {
    //using gui::App::App;
public:
    StaticTriangle();
    ~StaticTriangle();

protected:
    void draw() override;

private:
    engine::SwapChain swap_chain{device, window.get_extent()};
    std::unique_ptr<engine::Pipeline> pipeline;
    VkPipelineLayout pipeline_layout;
    std::vector<VkCommandBuffer> command_buffers;
    std::unique_ptr<engine::Model> triangle_model;

   void load_models();
   void create_pipeline_layout();
   void create_pipeline();
   void create_command_buffers();
};
