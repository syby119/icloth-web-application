cmake_minimum_required(VERSION 3.15)

project(icloth_web_application VERSION 0.3)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 11)

########## include third party library with cmake ##########
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake; ${CMAKE_MODULE_PATH}")
include(assimp)
include(grpc)
include(glfw)
include(glm)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

############## include projects #################
add_subdirectory(client)
# add_subdirectory(server)

target_link_libraries(test_spdlog ${ASSIMP_LIB} ${GRPC_LIB})
target_include_directories(test_spdlog PRIVATE ${ASSIMP_INCLUDE_DIR} ${GRPC_INCLUDE_DIR})