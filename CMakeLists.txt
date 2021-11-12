cmake_minimum_required(VERSION 3.15)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(icloth_web_application VERSION 0.3)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

########## include third party library with cmake ##########
add_subdirectory(external/grpc)
add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/tinyobjloader)

############## include projects #################
add_subdirectory(client)
# add_subdirectory(server)