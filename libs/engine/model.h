#pragma once

#include "dev/rei.h"

#include "device.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace engine {

class Model {
public:
    struct Vertex {
        glm::vec2 position;

        static std::vector<VkVertexInputBindingDescription> get_binding_descriptions();
        static std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions();
    };

public:
    Model(Device& device, const std::vector<Vertex>& vertices);
    ~Model();
    IMPLEMENT_REI(Model);

    void bind(VkCommandBuffer command_buffer);
    void draw(VkCommandBuffer command_buffer);

private:
    Device& device;
    VkBuffer vertex_buffer;
    VkDeviceMemory buffer_memory;
    uint32_t vertex_count;

    void create_vertext_buffers(const std::vector<Vertex>& vertices);
};
}  // engine
