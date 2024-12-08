#pragma once

#include "device.h"

#include "dev/rei.h"

#include <string>

namespace engine {

class Pipeline {
public:
    struct Config {
        VkPipelineInputAssemblyStateCreateInfo assembly_info;
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineRasterizationStateCreateInfo rasterization_info;
        VkPipelineMultisampleStateCreateInfo multisample_info;
        VkPipelineColorBlendAttachmentState color_blend_attachment;
        VkPipelineColorBlendStateCreateInfo color_blend_info;
        VkPipelineDepthStencilStateCreateInfo depth_stencil_info;
        VkPipelineLayout pipeline_layout = nullptr;
        VkRenderPass render_pass = nullptr;
        uint32_t subpass = 0;

        static Config get_default(uint32_t width, uint32_t height);
    };

public:
    Pipeline(Device& device, const Config& config, const std::string& vert_source, const std::string& frag_source);
    ~Pipeline();
    IMPLEMENT_REI(Pipeline);

private:
    Device& device;
    VkPipeline pipeline;
    VkShaderModule vert_shader;
    VkShaderModule frag_shader;

    void create_shader(const std::vector<char>& shader_binary, OUT VkShaderModule& shader);
};
}  // engine
