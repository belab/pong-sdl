# Pong with SDL

Minimalistic implementation of pong with SDL. This project is using cmake and vcpkg.

## Setup

### vcpkg

```dos
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg\vcpkg.exe install sdl2:x64-windows
.\vcpkg\vcpkg.exe install sdl2-image:x64-windows
.\vcpkg\vcpkg.exe install sdl2-mixer:x64-windows
.\vcpkg\vcpkg.exe install sdl2-ttf:x64-windows
```

### VSCode

Install Microsoft CMake Tools extension in VSCode.
Add following lines to settings.json:

```text
"cmake.configureSettings": {
    "CMAKE_TOOLCHAIN_FILE": "<PATH_TO_VCPKG>/vcpkg/scripts/buildsystems/vcpkg.cmake"
}
```
