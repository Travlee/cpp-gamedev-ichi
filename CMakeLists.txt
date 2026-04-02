cmake_minimum_required(VERSION 4.0...4.3.0)

set(CAMKE_CXX_STANDARD 17)

# Set this to ON for production build
set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        add_compile_options(/arch:AVX2) # force SIMD optimizations
else()
        add_link_options(-static -static-libstdc++ -static-libgcc)

        add_compile_options(-mavx2 -mfma) # force SIMD optimizations, but different
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as static lib" FORCE)

project(mygame)

add_subdirectory("thirdparty/raylib-5.0")
add_subdirectory("thirdparty/imgui-docking")
add_subdirectory("thirdparty/rlimgui")

# MY_SOURCES is defined as a list of all source files in src dir
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

if(PRODUCTION_BUILD)
        # Assign ASSETS_PATH macro to relative path; inside exe dir
        target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")

        target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
        # Useful for dev to get ASSET_PATH in IDE for dev
        target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
        target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)

endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(MINGW AND PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -mwindows)

elseif(UNIX AND PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)

endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib_static imgui rlimgui)