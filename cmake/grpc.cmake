include(ExternalProject)

set(GRPC_ROOT         ${CMAKE_SOURCE_DIR}/external/grpc)
set(GRPC_GIT_TAG      v1.42.0)
set(GRPC_GIT_URL      https://github.com/grpc/grpc.git)
set(GRPC_CONFIGURE    cd ${GRPC_ROOT}/src/grpc && cmake -D CMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/grpc .)
set(GRPC_MAKE         cd ${GRPC_ROOT}/src/grpc && cmake --build . --config Release)
set(GRPC_INSTALL      cd ${GRPC_ROOT}/src/grpc && cmake --install . --config Release)

ExternalProject_Add(
    grpc
    PREFIX            ${GRPC_ROOT}
    GIT_REPOSITORY    ${GRPC_GIT_URL}
    GIT_TAG           ${GRPC_GIT_TAG}
    CONFIGURE_COMMAND ${GRPC_CONFIGURE}
    BUILD_COMMAND     ${GRPC_MAKE}
    INSTALL_COMMAND   ${GRPC_INSTALL}
)

# set(GRPC_LIB       ${GRPC_ROOT}/lib/assimp/libassimp.a)
# set(GRPC_INCLUDE_DIR   ${GRPC_ROOT}/include)