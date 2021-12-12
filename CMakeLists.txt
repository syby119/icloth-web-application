cmake_minimum_required(VERSION 3.15)

project(icloth_web_application VERSION 0.3)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

########## include third party library with cmake ##########
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake; ${CMAKE_MODULE_PATH}")

include(assimp)
include(grpc)
include(glfw)

set_target_properties(assimp PROPERTIES FOLDER external)
set_target_properties(grpc PROPERTIES FOLDER external)
set_target_properties(glfw PROPERTIES FOLDER external)

############## include projects #################
add_subdirectory(client)
# add_subdirectory(server)
