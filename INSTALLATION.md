# Genesis Installation Guide
Installing Genesis into your project is pretty easy and straightforward. The release includes builds for Linux and Windows, both have a static library build and a dynamic one, as well as bundled SDL2 that comes with Genesis. You can see an example of connecting to a real project in my game called [**ArkanoidWithoutAnEngine**](https://github.com/Atennop1/ArkanoidWithoutAnEngine).

You need to put the folders from the release somewhere in your project (for example, in the libs folder), set the `Genesis_DIR`, `GENESIS_LIB_DIR` and `GENESIS_SHARED_LIBS` variables to the values you need, call `find_package` and connect everything it found for you. In `Genesis_DIR`, you need to specify the path to cmake with `genesis-config.cmake`, in `GENESIS_LIB_DIR` the path to the root folder (the one with cmake, include, etc.), and set the `GENESIS_SHARED_LIBS` flag to ON or OFF, depending on whether you are using static or dynamic builds.

Here is the code for connecting Genesis to the CMake test project. Note that on Windows you need to add additional libraries and for a dynamic library do not forget to copy `Genesis.dll` to the build folder:

```cmake
cmake_minimum_required(VERSION 3.21.1)
set(CMAKE_CXX_STANDARD 20)

project(Example)
add_executable(Example)

if(WIN32)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows/cmake)
    set(GENESIS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows)
    set(ADDITIONAL_APIS setupapi user32 gdi32 winmm imm32 version)
elseif(UNIX)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux/cmake)
    set(GENESIS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux)
endif()

set(GENESIS_SHARED_LIBS OFF)
find_package(Genesis REQUIRED)

include_directories(${GENESIS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Genesis::Genesis ${ADDITIONAL_APIS})

if(WIN32 AND GENESIS_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GENESIS_LIB_DIR}/lib/Genesis.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
```