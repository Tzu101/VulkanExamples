# Project name and version
cmake_minimum_required(VERSION 3.15)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/log.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/shaders.cmake)

# Specify the C++ standard
project(VulkanTest VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
info("Build directory: ${CMAKE_BINARY_DIR}")
add_executable(VulkanTest main.cpp)

# Examples
target_include_directories(VulkanTest PRIVATE ${PROJECT_SOURCE_DIR}/examples)
target_sources(VulkanTest PRIVATE
    examples/blank_window.cpp
)

# Libs
target_include_directories(VulkanTest PRIVATE ${PROJECT_SOURCE_DIR}/libs)
target_sources(VulkanTest PRIVATE
    libs/gui/window.cpp
    libs/gui/app.cpp
)

# Packages
info("Vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")

find_package(Vulkan REQUIRED)
target_link_libraries(VulkanTest PRIVATE Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(VulkanTest PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(VulkanTest PRIVATE glm::glm)

find_package(glslang CONFIG REQUIRED)
target_link_libraries(VulkanTest PRIVATE glslang::glslang glslang::glslang-default-resource-limits glslang::SPIRV glslang::SPVRemapper)

# Shaders
info("Glsl compiler: ${GLSL_COMPILER}")
compile_shaders("shaders")