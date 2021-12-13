include(ExternalProject)

set(GRPC_ROOT         ${CMAKE_SOURCE_DIR}/external/grpc)
set(GRPC_GIT_TAG      v1.42.0)
set(GRPC_GIT_URL      https://github.com/grpc/grpc.git)
set(GRPC_CONFIGURE    cd ${GRPC_ROOT}/src/grpc && 
                      cmake -DCMAKE_INSTALL_PREFIX=${GRPC_ROOT} 
                            -DgRPC_BUILD_GRPC_CSHARP_PLUGIN=OFF
                            -DgRPC_BUILD_GRPC_NODE_PLUGIN=OFF
                            -DgRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN=OFF
                            -DgRPC_BUILD_GRPC_PHP_PLUGIN=OFF
                            -DgRPC_BUILD_GRPC_PYTHON_PLUGIN=OFF
                            -DgRPC_BUILD_GRPC_RUBY_PLUGIN=OFF .)
set(GRPC_BUILD        cd ${GRPC_ROOT}/src/grpc && cmake --build . --config Release)
set(GRPC_INSTALL      cd ${GRPC_ROOT}/src/grpc && cmake --install . --config Release)

ExternalProject_Add(
    grpc
    PREFIX            ${GRPC_ROOT}
    GIT_REPOSITORY    ${GRPC_GIT_URL}
    GIT_TAG           ${GRPC_GIT_TAG}
    GIT_SHALLOW       ON
    CONFIGURE_COMMAND ${GRPC_CONFIGURE}
    BUILD_COMMAND     ${GRPC_BUILD}
    INSTALL_COMMAND   ${GRPC_INSTALL}
)

set(GRPC_LIB ${GRPC_ROOT}/lib/grpc 
             ${GRPC_ROOT}/lib/grpc++ 
             ${GRPC_ROOT}/lib/grpc++_reflection
             ${GRPC_ROOT}/lib/libprotobuf)

set(GRPC_INCLUDE_DIR ${GRPC_ROOT}/include)