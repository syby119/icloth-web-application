cmake_minimum_required(VERSION 3.15)

project(client VERSION 1.0)

set(THIRD_PARTY_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/external)

include_directories(${THIRD_PARTY_LIBRARY_PATH}/glm)

include_directories(${THIRD_PARTY_LIBRARY_PATH}/glad/include)

include_directories(${THIRD_PARTY_LIBRARY_PATH}/glfw/include)

aux_source_directory(. PROJECT_SOURCE)

add_executable(client ${PROJECT_SOURCE})

target_link_libraries(client glfw glad glm)