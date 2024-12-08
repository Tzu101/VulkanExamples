#pragma once

#include "gui/app.h"

#include "engine/pipeline.h"
#include "engine/swap_chain.h"

#include <vector>
#include <memory>

class StaticTriangle: public gui::App {
    //using gui::App::App;
public:
    StaticTriangle();
    ~StaticTriangle();

protected:
    void update() override;

private:
    engine::SwapChain swap_chain{device, window.get_extent()};
    std::unique_ptr<engine::Pipeline> pipeline;
    VkPipelineLayout pipeline_layout;
    std::vector<VkCommandBuffer> command_buffers;

   void create_pipeline_layout();
   void create_pipeline();
   void create_command_buffers();
};
