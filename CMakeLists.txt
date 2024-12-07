# Project name and version
cmake_minimum_required(VERSION 3.15)
project(VulkanTest VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(VulkanTest main.cpp)

# Packages
find_package(Vulkan REQUIRED)
target_link_libraries(VulkanTest PRIVATE Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(VulkanTest PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(VulkanTest PRIVATE glm::glm)
