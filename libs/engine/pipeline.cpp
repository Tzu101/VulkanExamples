#include "pipeline.h"

#include "file/read.h"

#include <iostream>

namespace engine {

Pipeline::Pipeline(Device& device, const Config& config, const std::string& vert_source, const std::string& frag_source)
: device(device)
{
    auto vert_binary = file::to_binary(vert_source);
    auto frag_binary = file::to_binary(frag_source);

    std::cout << "Vert: " << vert_binary.size() << " Frag: " << frag_source.size() << std::endl;
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
    return default_config;
}
} // engine