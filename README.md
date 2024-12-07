# Vulkan Examples
A collection a Vulkan examples for future reference.

## Build
This project is build with CMake and includes Vulkan via Vcpkg.

To setup this project for VS Code, install the  [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension, then add vcpkg to `settings.json`:
```json
"cmake.configureArgs": [
    "-DCMAKE_TOOLCHAIN_FILE={Vcpkg Path}\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"
]
```
<br/>

For intelisense install the  [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) extansion, then modify `settings.json` for Vcpkg intelisense:
```json
"C_Cpp.default.includePath": [
    "{Vcpkg Path}\\installed\\x64-windows\\include"
]
```
As well as `.vscode/c_cpp_properties.json` for local file intelisense:
```json
"configurations": [
    {
        "name": "Win32",
        "includePath": [
            "${workspaceFolder}/examples"
        ]
    }
],
"version": 4
```


## Resources
Some resources that were helpfull:
- [https://vulkan-tutorial.com/Introduction](https://vulkan-tutorial.com/Introduction)
- [https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR](https://www.youtube.com/playlist?list=PL8327DO66nu9qYVKLDmdLW_84-yE4auCR)
