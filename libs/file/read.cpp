#include "read.h"

#include <fstream>
#include <stdexcept>

namespace file {

std::vector<char> to_binary(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::ate | std::ios::binary);

    if (not file.is_open()) {
        throw std::runtime_error("Failed to topen file: " + file_path);
    }

    size_t file_size = static_cast<size_t>(file.tellg());
    std::vector<char> binary_buffer(file_size);

    file.seekg(0);
    file.read(binary_buffer.data(), file_size);

    file.close();
    return binary_buffer;
}
}  // file