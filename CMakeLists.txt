cmake_minimum_required(VERSION 3.19)
project(Genesis
    VERSION 1.0.0
    DESCRIPTION "Simple 2D game engine based on SDL2 and written in C++"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# General settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(GENESIS_BUILD_EXAMPLES "Build Genesis examples" OFF)
option(GENESIS_INSTALL "Generate target for installing Genesis" ${is_top_level})
set_if_undefined(GENESIS_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/Genesis" CACHE STRING "Install path for Genesis package-related CMake files")

if(DEFINED GENESIS_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${GENESIS_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET default)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)

add_library(Genesis)
add_library(Genesis::Genesis ALIAS Genesis)

#----------------------------------------------------------------------------------------------------------------------
# Genesis dependencies
#----------------------------------------------------------------------------------------------------------------------

if(WIN32)
    set(SDL2_LIB "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/windows/libSDL2.a")
    set(ADDITIONAL_APIS imagehlp dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid setupapi hid)
elseif(UNIX)
    set(SDL2_LIB "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib/linux/libSDL2.a")
endif()

include_directories(dependencies/SDL2/include include/)
target_link_libraries(Genesis PRIVATE ${SDL2_LIB} ${ADDITIONAL_APIS})

#----------------------------------------------------------------------------------------------------------------------
# Genesis sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

set(sources
    include/genesis/events/input.hpp
    include/genesis/events/application_events.hpp
    include/genesis/exiting/exit_event.hpp
    include/genesis/exiting/application_exiter.hpp
    include/genesis/loop/objects/game_loop_object.hpp
    include/genesis/loop/objects/game_object.hpp
    include/genesis/loop/game_time.hpp
    include/genesis/loop/game_loop.hpp
    include/genesis/math/vector2.hpp
    include/genesis/memory/shared_pointer.hpp
    include/genesis/physics/physical_properties.hpp
    include/genesis/physics/physics_object.hpp
    include/genesis/physics/physics_simulation.hpp
    include/genesis/rendering/screen_applier.hpp
    include/genesis/rendering/screen_cleaner.hpp
    include/genesis/rendering/window_references.hpp
    include/genesis/shortcuts/shortcuts.hpp
    src/events/application_events.cpp
    src/events/input.cpp
    src/exiting/application_exiter.cpp
    src/loop/game_loop.cpp
    src/loop/game_time.cpp
    src/math/vector2.cpp
    src/physics/physics_simulation.cpp
    src/rendering/screen_applier.cpp
    src/rendering/screen_cleaner.cpp
    src/rendering/window_references.cpp
    src/shortcuts/shortcuts.cpp)

generate_export_header(Genesis EXPORT_FILE_NAME include/genesis/${export_file_name})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# Genesis target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(Genesis PRIVATE ${sources})
target_compile_definitions(Genesis PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:GENESIS_STATIC_DEFINE>")

target_include_directories(Genesis
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(Genesis PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
    OUTPUT_NAME "Genesis")

if(WIN32 AND BUILD_SHARED_LIBS)
    set_target_properties(Genesis PROPERTIES
            INTERFACE_LINK_LIBRARIES "${ADDITIONAL_APIS}"
            ARCHIVE_OUTPUT_NAME ""
            PREFIX "")
endif()

if(GENESIS_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/genesis-config.cmake.in genesis-config.cmake
        INSTALL_DESTINATION "${GENESIS_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(genesis-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS Genesis EXPORT Genesis_export
        RUNTIME COMPONENT Genesis
        LIBRARY COMPONENT Genesis NAMELINK_COMPONENT genesis-dev
        ARCHIVE COMPONENT genesis-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT genesis-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/genesis/${export_file_name}"
        COMPONENT genesis-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/genesis")

    set(targets_file "genesis-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "genesis-static-targets.cmake")
    endif()

    install(EXPORT Genesis_export
        COMPONENT genesis-dev
        FILE "${targets_file}"
        DESTINATION "${GENESIS_INSTALL_CMAKEDIR}"
        NAMESPACE Genesis::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/genesis-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/genesis-config-version.cmake"
        COMPONENT genesis-dev
        DESTINATION "${GENESIS_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:Genesis>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            set(pdb_file "$<TARGET_FILE_DIR:Genesis>/$<TARGET_FILE_PREFIX:Genesis>$<TARGET_FILE_BASE_NAME:Genesis>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT genesis-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# Other targets
#----------------------------------------------------------------------------------------------------------------------

if(GENESIS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
