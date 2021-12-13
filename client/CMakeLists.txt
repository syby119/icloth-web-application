cmake_minimum_required(VERSION 3.18)

project(client VERSION 1.0)

function(DebugPrint results)
    message(STATUS "####################################")
    foreach(result IN LISTS ${results})
        message(STATUS ${result})
    endforeach(result)
    message(STATUS "####################################")
endfunction(DebugPrint)

set(THIRD_PARTY_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/external)

# glad
file(GLOB GLAD_SRC "${THIRD_PARTY_LIBRARY_PATH}/glad/src/*.c")
source_group(external/glad FILES ${GLAD_SRC})

# imgui
file(GLOB IMGUI_SRC "${THIRD_PARTY_LIBRARY_PATH}/imgui/*.h" "${THIRD_PARTY_LIBRARY_PATH}/imgui/*.cpp")
set(IMGUI_BACKEND_SRC ${THIRD_PARTY_LIBRARY_PATH}/imgui/backends/imgui_impl_glfw.cpp
                      ${THIRD_PARTY_LIBRARY_PATH}/imgui/backends/imgui_impl_opengl3.cpp)
source_group(external/imgui FILES ${IMGUI_SRC} ${IMGUI_BACKEND_SRC})

# stb
file(GLOB STB_SRC "${THIRD_PARTY_LIBRARY_PATH}/stb/*.h")
source_group(external/stb FILES ${STB_SRC})

# base
file(GLOB_RECURSE CAMERA_SRC "camera/*.cpp" "camera/*.h" "camera/*.hpp")
source_group(base/camera FILES ${CAMERA_SRC})

file(GLOB_RECURSE CORE_SRC "core/*.cpp" "core/*.h" "core/*.hpp")
source_group(base/core FILES ${CORE_SRC})

file(GLOB_RECURSE LIGHT_SRC RELATIVE light "light/*.cpp" "light/*.h" "ight/*.hpp")
source_group(base/light FILES ${LIGHT_SRC})

file(GLOB_RECURSE LOADER_SRC loader "loader/*.cpp" "loader/*.h" "loader/*.hpp")
source_group(base/loader FILES ${LOADER_SRC})

file(GLOB_RECURSE MATERIAL_SRC material "material/*.cpp" "material/*.h" "material/*.hpp")
source_group(base/material FILES ${MATERIAL_SRC})

file(GLOB_RECURSE MATH_SRC math "math/*.cpp" "math/*.h" "math/*.hpp")
source_group(base/math FILES ${MATH_SRC})

file(GLOB_RECURSE OBJECT_SRC object "object/*.cpp" "object/*.h" "object/*.hpp")
source_group(base/object FILES ${OBJECT_SRC})

file(GLOB_RECURSE RENDERER_SRC renderer "renderer/*.cpp" "renderer/*.h" "renderer/*.hpp")
source_group(base/renderer FILES ${RENDERER_SRC})

file(GLOB_RECURSE TEXTURE_SRC texture "texture/*.cpp" "texture/*.h" "texture/*.hpp")
source_group(base/texture FILES ${TEXTURE_SRC})

file(GLOB_RECURSE UTILITY_SRC utility "utility/*.cpp" "utility/*.h" "utility/*.hpp")
source_group(base/utility FILES ${UTILITY_SRC})

set(BASE_SRC ${CAMERA_SRC} 
             ${CORE_SRC} 
             ${LIGHT_SRC} 
             ${LOADER_SRC} 
             ${MATERIAL_SRC} 
             ${MATH_SRC} ${OBJECT_SRC} 
             ${RENDERER_SRC} 
             ${TEXTURE_SRC}
             ${UTILITY_SRC})

# project
file(GLOB PROJECT_SRC "*.cpp" "*.h")

add_executable(
    client 
    ${PROJECT_SRC}
    ${BASE_SRC}
    ${GLAD_SRC}
    ${IMGUI_SRC}
    ${IMGUI_BACKEND_SRC}
    ${STB_SRC})

# include path
target_include_directories(
    client PUBLIC
    ${THIRD_PARTY_LIBRARY_PATH}/assimp/include
    ${THIRD_PARTY_LIBRARY_PATH}/grpc/include
    ${THIRD_PARTY_LIBRARY_PATH}/glfw/include
    ${THIRD_PARTY_LIBRARY_PATH}/glad/include
    ${THIRD_PARTY_LIBRARY_PATH}/glm
    ${THIRD_PARTY_LIBRARY_PATH}/imgui
    ${THIRD_PARTY_LIBRARY_PATH}/imgui/backends
    ${THIRD_PARTY_LIBRARY_PATH}/stb)

# target_link_libraries(client glm glfw assimp /*grpc++*/)
# target_link_libraries(client assimp glad glfw glm)