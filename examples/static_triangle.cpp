#include "static_triangle.h"

#include <stdexcept>

StaticTriangle::StaticTriangle()
: gui::App("Static Triangle")
{
    create_pipeline_layout();
    create_pipeline();
    create_command_buffers();
}

StaticTriangle::~StaticTriangle() {
    vkDestroyPipelineLayout(device.device(), pipeline_layout, nullptr);
}

void StaticTriangle::update() {}

void StaticTriangle::create_pipeline_layout() {
    VkPipelineLayoutCreateInfo pipeline_layout_info{};
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 0;
    pipeline_layout_info.pSetLayouts = nullptr;
    pipeline_layout_info.pushConstantRangeCount = 0;
    pipeline_layout_info.pPushConstantRanges = nullptr;

    if (vkCreatePipelineLayout(device.device(), &pipeline_layout_info, nullptr, &pipeline_layout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout!");
    }
}

void StaticTriangle::create_pipeline() {
    auto pipeline_config = engine::Pipeline::Config::get_default(swap_chain.width(), swap_chain.height());
    pipeline_config.render_pass = swap_chain.getRenderPass();
    pipeline_config.pipeline_layout = pipeline_layout;

    pipeline = std::make_unique<engine::Pipeline>(
        device, 
        pipeline_config, 
        "shaders/static_triangle.vert.spv", 
        "shaders/static_triangle.frag.spv"
    );
}

void StaticTriangle::create_command_buffers() {
}
