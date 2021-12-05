include(ExternalProject)

set(GLM_ROOT         ${CMAKE_SOURCE_DIR}/external/glm)
set(GLM_GIT_TAG      v1.42.0)
set(GLM_GIT_URL      https://github.com/glm/glm.git)
set(GLM_CONFIGURE    cd ${GLM_ROOT}/src/glm && cmake -D CMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/glm .)
set(GLM_MAKE         cd ${GLM_ROOT}/src/glm && cmake --build . --config Release)
set(GLM_INSTALL      cd ${CMAKE_BINARY_DIR}/src/glm && cmake --install . --config Release)

ExternalProject_Add(
    glm
    PREFIX            ${GLM_ROOT}
    GIT_REPOSITORY    ${GLM_GIT_URL}
    GIT_TAG           ${GLM_GIT_TAG}
    CONFIGURE_COMMAND ${GLM_CONFIGURE}
    BUILD_COMMAND     ${GLM_MAKE}
    INSTALL_COMMAND   ${GLM_INSTALL}
)

# set(GLM_LIB       ${GLM_ROOT}/lib/glm/libglm.a)
# set(GLM_INCLUDE_DIR   ${GLM_ROOT}/include)