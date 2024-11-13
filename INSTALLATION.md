# Genesis Installation Guide
Installing Genesis into your project is pretty easy and straightforward. The release includes builds for Linux and Windows, both have a static library build and a dynamic one, as well as bundled SDL2 that comes with Genesis. Note that dynamic Genesis has SDL fully built in and you don't need to include it separately, while static version requires adding static SDL, which is provided out of the box and is done during `find_package`. You can see an example of connecting Genesis to a real project in my game called [**ArkanoidWithoutAnEngine**](https://github.com/Atennop1/ArkanoidWithoutAnEngine).

You need to put the folders from the release somewhere in your project (for example, in the libs folder), set the `Genesis_DIR`, `GENESIS_LIB_DIR` and `GENESIS_SHARED_LIBS` variables to the values you need, call `find_package` and connect everything it found for you. In `Genesis_DIR`, you need to specify the path to cmake with `genesis-config.cmake`, in `GENESIS_LIB_DIR` the path to the root folder (the one with cmake, include, etc.), and set the `GENESIS_SHARED_LIBS` flag to ON or OFF, depending on whether you are using static or dynamic builds. Also don't forget to add the path to libGenesis.so to your `LD_LIBRARY_PATH` if you want to use the dynamic library variant and are using Linux.

Here is the code for connecting Genesis to the CMake test project. Note that on Windows you need to add additional libraries and for a dynamic library do not forget to copy `Genesis.dll` to the build folder:

```cmake
# basic setup
cmake_minimum_required(VERSION 3.21.1)
set(CMAKE_CXX_STANDARD 20)

project(Example)
add_executable(Example)

# setting data for find_package
if(WIN32)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows/cmake)
    set(GENESIS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/windows)
    set(ADDITIONAL_APIS setupapi user32 gdi32 winmm imm32 version)
elseif(UNIX)
    set(Genesis_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux/cmake)
    set(GENESIS_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/Genesis/linux)
endif()

# finding
set(GENESIS_SHARED_LIBS OFF)
find_package(Genesis REQUIRED)

# linking
include_directories(${GENESIS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE Genesis::Genesis ${ADDITIONAL_APIS})

# copying .dll after building if using shared Genesis
if(WIN32 AND GENESIS_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GENESIS_LIB_DIR}/lib/Genesis.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
```
