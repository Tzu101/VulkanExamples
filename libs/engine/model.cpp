#include "model.h"

namespace engine {
Model::Model(Device &device, const std::vector<Vertex> &vertices)
: device(device)
{
    create_vertext_buffers(vertices);
}

Model::~Model() {
    vkDestroyBuffer(device.device(), vertex_buffer, nullptr);
    vkFreeMemory(device.device(), buffer_memory, nullptr);
}

void Model::create_vertext_buffers(const std::vector<Vertex> &vertices) {
    vertex_count = vertices.size();
    assert(vertex_count >= 3 && "Vertex count mut be at least 3");

    VkDeviceSize buffer_size = sizeof(vertices[0]) * vertex_count;
    device.createBuffer(
        buffer_size,
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        vertex_buffer,
        buffer_memory
    );

    void* data;
    vkMapMemory(device.device(), buffer_memory, 0, buffer_size, 0, &data);
    memcpy(data, vertices.data(), buffer_size);
    vkUnmapMemory(device.device(), buffer_memory);
}

void Model::bind(VkCommandBuffer command_buffer) {
    VkBuffer buffers[] = {vertex_buffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(command_buffer, 0, 1, buffers, offsets);
}

void Model::draw(VkCommandBuffer command_buffer) {
    vkCmdDraw(command_buffer, vertex_count, 2, 0, 0);
}

std::vector<VkVertexInputBindingDescription> Model::Vertex::get_binding_descriptions()
{
    std::vector<VkVertexInputBindingDescription> descriptions(1);
    descriptions[0].binding = 0;
    descriptions[0].stride = sizeof(Vertex);
    descriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return descriptions;
}

std::vector<VkVertexInputAttributeDescription> Model::Vertex::get_attribute_descriptions()
{
    std::vector<VkVertexInputAttributeDescription> descriptions(2);
    descriptions[0].binding = 0;
    descriptions[0].location = 0;
    descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    descriptions[0].offset = offsetof(Vertex, position);

    descriptions[1].binding = 0;
    descriptions[1].location = 1;
    descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    descriptions[1].offset = offsetof(Vertex, color);

    return descriptions;
}
} // engine