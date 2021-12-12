include(ExternalProject)

set(ASSIMP_ROOT         ${CMAKE_SOURCE_DIR}/external/assimp)
set(ASSIMP_GIT_TAG      v5.1.3)
set(ASSIMP_GIT_URL      https://github.com/assimp/assimp.git)
set(ASSIMP_CONFIGURE    cd ${ASSIMP_ROOT}/src/assimp && cmake -D CMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/assimp .)
set(ASSIMP_MAKE         cd ${ASSIMP_ROOT}/src/assimp && cmake --build . --config Release)
set(ASSIMP_INSTALL      cd ${ASSIMP_ROOT}/src/assimp && cmake --install . --config Release)

ExternalProject_Add(
    assimp
    PREFIX            ${ASSIMP_ROOT}
    GIT_REPOSITORY    ${ASSIMP_GIT_URL}
    GIT_TAG           ${ASSIMP_GIT_TAG}
    CONFIGURE_COMMAND ${ASSIMP_CONFIGURE}
    BUILD_COMMAND     ${ASSIMP_MAKE}
    INSTALL_COMMAND   ${ASSIMP_INSTALL}
)

# set(ASSIMP_LIB       ${ASSIMP_ROOT}/lib/assimp/libassimp.a)
# set(ASSIMP_INCLUDE_DIR   ${ASSIMP_ROOT}/include)