# Vulkan Examples
A collection a Vulkan examples for future reference

## Build
This project is build with CMake and includes Vulkan via Vcpkg.

To setup this project for VS Code, install the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) and [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extensions, then add vcpkg to their settings:
```json
"cmake.configureArgs": [
    "-DCMAKE_TOOLCHAIN_FILE={Vcpkg Path}\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
],
"C_Cpp.default.includePath": [
    "{Vcpkg Path}\\installed\\x64-windows\\include"
]
```

## Resources
Some resources that were helpfull:
- [https://vulkan-tutorial.com/Introduction](https://vulkan-tutorial.com/Introduction)
- [https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR](https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR)
