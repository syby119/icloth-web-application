cmake_minimum_required(VERSION 3.15)

project(client VERSION 1.0)

set(THIRD_PARTY_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/external)

# include 
include_directories(${THIRD_PARTY_LIBRARY_PATH}/glm
                    ${THIRD_PARTY_LIBRARY_PATH}/glad/include
                    ${THIRD_PARTY_LIBRARY_PATH}/glfw/include
                    ${THIRD_PARTY_LIBRARY_PATH}/tinyobjloader
                    ${THIRD_PARTY_LIBRARY_PATH}/imgui
                    ${THIRD_PARTY_LIBRARY_PATH}/imgui/backends
                    ${THIRD_PARTY_LIBRARY_PATH}/stb
                    ${THIRD_PARTY_LIBRARY_PATH}/grpc/include)

aux_source_directory(${THIRD_PARTY_LIBRARY_PATH}/glad/src GLAD_SRC)

aux_source_directory(${THIRD_PARTY_LIBRARY_PATH}/imgui IMGUI_SRC)
set(IMGUI_BACKEND_SRC ${THIRD_PARTY_LIBRARY_PATH}/imgui/backends/imgui_impl_glfw.cpp
                      ${THIRD_PARTY_LIBRARY_PATH}/imgui/backends/imgui_impl_opengl3.cpp)

aux_source_directory(${THIRD_PARTY_LIBRARY_PATH}/stb STB_SRC)

aux_source_directory(. PROJECT_SOURCE)

add_executable(client ${PROJECT_SOURCE} ${GLAD_SRC} ${IMGUI_SRC} ${IMGUI_BACKEND_SRC} ${STB_SRC})

target_link_libraries(client glm glfw tinyobjloader grpc++)