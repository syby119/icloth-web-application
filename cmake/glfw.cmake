include(ExternalProject)

set(GLFW_ROOT       ${CMAKE_SOURCE_DIR}/external/glfw)
set(GLFW_GIT_TAG    3.3.5)
set(GLFW_GIT_URL    https://github.com/glfw/glfw.git)
set(GLFW_CONFIGURE  cd ${GLFW_ROOT}/src/glfw && cmake -D CMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/glfw .)
set(GLFW_MAKE       cd ${GLFW_ROOT}/src/glfw && cmake --build . --config Release)
set(GLFW_INSTALL    cd ${GLFW_ROOT}/src/glfw && cmake --install . --config Release)

ExternalProject_Add(
    glfw
    PREFIX            ${GLFW_ROOT}
    GIT_REPOSITORY    ${GLFW_GIT_URL}
    GIT_TAG           ${GLFW_GIT_TAG}
    CONFIGURE_COMMAND ${GLFW_CONFIGURE}
    BUILD_COMMAND     ${GLFW_MAKE}
    INSTALL_COMMAND   ${GLFW_INSTALL}
)

# set(GLFW_LIB       ${GLFW_ROOT}/lib/glfw/libglfw.a)
# set(GLFW_INCLUDE_DIR   ${GLFW_ROOT}/include)