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
    std::unique_ptr<engine::SwapChain> swap_chain;
    std::unique_ptr<engine::Pipeline> pipeline;
    VkPipelineLayout pipeline_layout;
    std::vector<VkCommandBuffer> command_buffers;
    std::unique_ptr<engine::Model> triangle_model;

    void load_models();
    void create_pipeline_layout();
    void create_pipeline();
    void create_command_buffers();
    void free_command_buffers();

    void recreate_swap_chain();
    void record_command_buffer(int image_index);
};
