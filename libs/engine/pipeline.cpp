#include "pipeline.h"

#include "file/read.h"

#include <iostream>
#include <cassert>

namespace engine {

Pipeline::Pipeline(Device& device, const Config& config, const std::string& vert_source, const std::string& frag_source)
: device(device)
{
    assert(config.pipeline_layout != VK_NULL_HANDLE && "Cannot create graphics pipeline: pipeline_layout not provided");
    assert(config.render_pass != VK_NULL_HANDLE && "Cannot create graphics pipeline: render_pass not provided");

    auto vert_binary = file::to_binary(vert_source);
    auto frag_binary = file::to_binary(frag_source);

    create_shader(vert_binary, vert_shader);
    create_shader(frag_binary, frag_shader);

    VkPipelineShaderStageCreateInfo shader_stages[2];
    shader_stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shader_stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shader_stages[0].module = vert_shader;
    shader_stages[0].pName = "main";
    shader_stages[0].flags = 0;
    shader_stages[0].pNext = nullptr;
    shader_stages[0].pSpecializationInfo = nullptr;

    shader_stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shader_stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shader_stages[1].module = frag_shader;
    shader_stages[1].pName = "main";
    shader_stages[1].flags = 0;
    shader_stages[1].pNext = nullptr;
    shader_stages[1].pSpecializationInfo = nullptr;

    VkPipelineVertexInputStateCreateInfo vertex_input{};
    vertex_input.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input.vertexAttributeDescriptionCount = 0;
    vertex_input.vertexBindingDescriptionCount = 0;
    vertex_input.pVertexAttributeDescriptions = nullptr;
    vertex_input.pVertexBindingDescriptions = nullptr;

    VkPipelineViewportStateCreateInfo viewport_info{};
    viewport_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_info.viewportCount = 1;
    viewport_info.pViewports = &config.viewport;
    viewport_info.scissorCount = 1;
    viewport_info.pScissors = &config.scissor;

    VkGraphicsPipelineCreateInfo pipeline_info{};
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.stageCount = 2;
    pipeline_info.pStages = shader_stages;
    pipeline_info.pVertexInputState = &vertex_input;
    pipeline_info.pInputAssemblyState = &config.assembly_info;
    pipeline_info.pViewportState = &viewport_info;
    pipeline_info.pRasterizationState = &config.rasterization_info;
    pipeline_info.pMultisampleState = &config.multisample_info;
    pipeline_info.pColorBlendState = &config.color_blend_info;
    pipeline_info.pDepthStencilState = &config.depth_stencil_info;
    pipeline_info.pDynamicState = nullptr;

    pipeline_info.layout = config.pipeline_layout;
    pipeline_info.renderPass = config.render_pass;
    pipeline_info.subpass = config.subpass;

    pipeline_info.basePipelineIndex = -1;
    pipeline_info.basePipelineHandle = VK_NULL_HANDLE;

    if (vkCreateGraphicsPipelines(device.device(), VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create graphics pipeline!");
    }
}

Pipeline::~Pipeline() {
    vkDestroyShaderModule(device.device(), vert_shader, nullptr);
    vkDestroyShaderModule(device.device(), frag_shader, nullptr);
    vkDestroyPipeline(device.device(), pipeline, nullptr);
}

void Pipeline::create_shader(const std::vector<char>& shader_binary, OUT VkShaderModule &shader) {
    VkShaderModuleCreateInfo shader_info{};
    shader_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shader_info.codeSize = shader_binary.size();
    shader_info.pCode = reinterpret_cast<const uint32_t*>(shader_binary.data());

    if (vkCreateShaderModule(device.device(), &shader_info, nullptr, &shader) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader modeule");
    }
}

Pipeline::Config Pipeline::Config::get_default(uint32_t width, uint32_t height) {
    Config default_config{};

    default_config.assembly_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    default_config.assembly_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    default_config.assembly_info.primitiveRestartEnable = VK_FALSE;

    default_config.viewport.x = 0.0f;
    default_config.viewport.y = 0.0f;
    default_config.viewport.width = static_cast<float>(width);
    default_config.viewport.height = static_cast<float>(height);
    default_config.viewport.minDepth = 0.0f;
    default_config.viewport.maxDepth = 1.0f;
    
    default_config.scissor.offset = {0, 0};
    default_config.scissor.extent = {width, height};

    default_config.rasterization_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    default_config.rasterization_info.depthClampEnable = VK_FALSE;
    default_config.rasterization_info.rasterizerDiscardEnable = VK_FALSE;
    default_config.rasterization_info.polygonMode = VK_POLYGON_MODE_FILL;
    default_config.rasterization_info.lineWidth = 1.0f;
    default_config.rasterization_info.cullMode = VK_CULL_MODE_NONE;
    default_config.rasterization_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
    default_config.rasterization_info.depthBiasEnable = VK_FALSE;
    default_config.rasterization_info.depthBiasConstantFactor = 0.0f;  // Optional
    default_config.rasterization_info.depthBiasClamp = 0.0f;           // Optional
    default_config.rasterization_info.depthBiasSlopeFactor = 0.0f;     // Optional

    default_config.multisample_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    default_config.multisample_info.sampleShadingEnable = VK_FALSE;
    default_config.multisample_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    default_config.multisample_info.minSampleShading = 1.0f;           // Optional
    default_config.multisample_info.pSampleMask = nullptr;             // Optional
    default_config.multisample_info.alphaToCoverageEnable = VK_FALSE;  // Optional
    default_config.multisample_info.alphaToOneEnable = VK_FALSE;       // Optional

    default_config.color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    default_config.color_blend_attachment.blendEnable = VK_FALSE;
    default_config.color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    default_config.color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    default_config.color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
    default_config.color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
    default_config.color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
    default_config.color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional

    default_config.color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    default_config.color_blend_info.logicOpEnable = VK_FALSE;
    default_config.color_blend_info.logicOp = VK_LOGIC_OP_COPY;  // Optional
    default_config.color_blend_info.attachmentCount = 1;
    default_config.color_blend_info.pAttachments = &default_config.color_blend_attachment;
    default_config.color_blend_info.blendConstants[0] = 0.0f;  // Optional
    default_config.color_blend_info.blendConstants[1] = 0.0f;  // Optional
    default_config.color_blend_info.blendConstants[2] = 0.0f;  // Optional
    default_config.color_blend_info.blendConstants[3] = 0.0f;  // Optional

    default_config.depth_stencil_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    default_config.depth_stencil_info.depthTestEnable = VK_TRUE;
    default_config.depth_stencil_info.depthWriteEnable = VK_TRUE;
    default_config.depth_stencil_info.depthCompareOp = VK_COMPARE_OP_LESS;
    default_config.depth_stencil_info.depthBoundsTestEnable = VK_FALSE;
    default_config.depth_stencil_info.minDepthBounds = 0.0f;  // Optional
    default_config.depth_stencil_info.maxDepthBounds = 1.0f;  // Optional
    default_config.depth_stencil_info.stencilTestEnable = VK_FALSE;
    default_config.depth_stencil_info.front = {};  // Optional
    default_config.depth_stencil_info.back = {};   // Optional

    return default_config;
}
} // engine