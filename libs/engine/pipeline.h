#pragma once

#include "device.h"

#include "dev/rei.h"

#include <string>

namespace engine {

class Pipeline {
public:
    struct Config {
        VkPipelineViewportStateCreateInfo viewport_info;
        VkPipelineInputAssemblyStateCreateInfo assembly_info;
        VkPipelineRasterizationStateCreateInfo rasterization_info;
        VkPipelineMultisampleStateCreateInfo multisample_info;
        VkPipelineColorBlendAttachmentState color_blend_attachment;
        VkPipelineColorBlendStateCreateInfo color_blend_info;
        VkPipelineDepthStencilStateCreateInfo depth_stencil_info;
        std::vector<VkDynamicState> dynamic_state_enables;
        VkPipelineDynamicStateCreateInfo dynamic_state_info;
        VkPipelineLayout pipeline_layout = nullptr;
        VkRenderPass render_pass = nullptr;
        uint32_t subpass = 0;

        static void default_config(OUT Config& config_info);
        Config() = default;
        IMPLEMENT_REI(Config);
    };

public:
    Pipeline(Device& device, const Config& config, const std::string& vert_source, const std::string& frag_source);
    ~Pipeline();
    IMPLEMENT_REI(Pipeline);

    void bind(VkCommandBuffer command_buffer);

private:
    Device& device;
    VkPipeline pipeline;
    VkShaderModule vert_shader;
    VkShaderModule frag_shader;

    void create_shader(const std::vector<char>& shader_binary, OUT VkShaderModule& shader);
};
}  // engine
