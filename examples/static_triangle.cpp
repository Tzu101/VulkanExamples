#include "static_triangle.h"

#include <array>
#include <stdexcept>

StaticTriangle::StaticTriangle()
: gui::App("Static Triangle")
{
    load_models();
    create_pipeline_layout();
    recreate_swap_chain();
    create_command_buffers();
}

StaticTriangle::~StaticTriangle() {
    vkDestroyPipelineLayout(device.device(), pipeline_layout, nullptr);
}

void StaticTriangle::draw() {
    uint32_t image_index;
    auto result = swap_chain->acquireNextImage(&image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreate_swap_chain();
        return;
    }

    if (result != VK_SUCCESS and result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed to accuire swap chain image");
    }

    record_command_buffer(image_index);
    result = swap_chain->submitCommandBuffers(&command_buffers[image_index], &image_index);

    if (result == VK_ERROR_OUT_OF_DATE_KHR or result == VK_SUBOPTIMAL_KHR or window.was_resized()) {
        window.resize_registered();
        recreate_swap_chain();
        return;
    }

    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("Failed present swap chain image");
    }
}


void StaticTriangle::load_models() {
    std::vector<engine::Model::Vertex> vertices {
        {{0.0f, -0.5f}, {1, 1, 0}},
        {{0.5f, 0.5f}, {1, 0, 1}},
        {{-0.5f, 0.5f}, {0, 1, 1}},
    };
    triangle_model = std::make_unique<engine::Model>(device, vertices);
}

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
    engine::Pipeline::Config pipeline_config{};
    engine::Pipeline::Config::default_config(pipeline_config);
    pipeline_config.render_pass = swap_chain->getRenderPass();
    pipeline_config.pipeline_layout = pipeline_layout;

    pipeline = std::make_unique<engine::Pipeline>(
        device, 
        pipeline_config, 
        "shaders/static_triangle.vert.spv", 
        "shaders/static_triangle.frag.spv"
    );
}

void StaticTriangle::create_command_buffers() {
    command_buffers.resize(swap_chain->imageCount());

    VkCommandBufferAllocateInfo allocate_info{};
    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandPool = device.getCommandPool();
    allocate_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());

    if (vkAllocateCommandBuffers(device.device(), &allocate_info, command_buffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate comamnd buffers");
    }

    for (int i = 0; i < command_buffers.size(); i++) {
        record_command_buffer(i);
    }
}

void StaticTriangle::free_command_buffers() {
    vkFreeCommandBuffers(device.device(), device.getCommandPool(), command_buffers.size(), command_buffers.data());
    command_buffers.clear();
}

void StaticTriangle::recreate_swap_chain() {
    while (not window.has_size()) {
        glfwWaitEvents();
    }
    vkDeviceWaitIdle(device.device());

    if (swap_chain == nullptr) {
        swap_chain = std::make_unique<engine::SwapChain>(device, window.get_extent());
    }
    else {
        swap_chain = std::make_unique<engine::SwapChain>(device, window.get_extent(), std::move(swap_chain));
        if (swap_chain->imageCount() != command_buffers.size()) {
            free_command_buffers();
            create_command_buffers();
        }
    }

    // TODO check for compatible render passes
    create_pipeline();
}

void StaticTriangle::record_command_buffer(int image_index) {
    VkCommandBufferBeginInfo begin_info{};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(command_buffers[image_index], &begin_info) != VK_SUCCESS) {
        throw std::runtime_error("Failed to begin recoring command buffer");
    }

    VkRenderPassBeginInfo render_pass_info{};
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_info.renderPass = swap_chain->getRenderPass();
    render_pass_info.framebuffer = swap_chain->getFrameBuffer(image_index);

    render_pass_info.renderArea.offset = {0, 0};
    render_pass_info.renderArea.extent = swap_chain->getSwapChainExtent();

    std::array<VkClearValue, 2> clear_values{};
    clear_values[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clear_values[1].depthStencil = {1.0f, 0};
    render_pass_info.clearValueCount = clear_values.size();
    render_pass_info.pClearValues = clear_values.data();

    vkCmdBeginRenderPass(command_buffers[image_index], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swap_chain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(swap_chain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, swap_chain->getSwapChainExtent()};
    vkCmdSetViewport(command_buffers[image_index], 0, 1, &viewport);
    vkCmdSetScissor(command_buffers[image_index], 0, 1, &scissor);

    pipeline->bind(command_buffers[image_index]);
    triangle_model->bind(command_buffers[image_index]);
    triangle_model->draw(command_buffers[image_index]);

    vkCmdDraw(command_buffers[image_index], 3, 1, 0, 0);

    vkCmdEndRenderPass(command_buffers[image_index]);
    if (vkEndCommandBuffer(command_buffers[image_index]) != VK_SUCCESS) {
        throw std::runtime_error("Failed to record command buffer");
    }
}
