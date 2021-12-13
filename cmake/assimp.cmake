include(ExternalProject)

set(ASSIMP_ROOT         ${CMAKE_SOURCE_DIR}/external/assimp)
set(ASSIMP_GIT_TAG      v5.1.3)
set(ASSIMP_GIT_URL      https://github.com/assimp/assimp.git)
set(ASSIMP_CONFIGURE    cd ${ASSIMP_ROOT}/src/assimp && 
                        cmake -DCMAKE_INSTALL_PREFIX=${ASSIMP_ROOT} 
                              -DLIBRARY_SUFFIX= 
                              -DBUILD_SHARED_LIBS=OFF 
                              -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
                              -DASSIMP_BUILD_TESTS=OFF .)
set(ASSIMP_MAKE         cd ${ASSIMP_ROOT}/src/assimp && cmake --build . --config Release)
set(ASSIMP_INSTALL      cd ${ASSIMP_ROOT}/src/assimp && cmake --install . --config Release)

ExternalProject_Add(
    assimp
    PREFIX            ${ASSIMP_ROOT}
    GIT_REPOSITORY    ${ASSIMP_GIT_URL}
    GIT_TAG           ${ASSIMP_GIT_TAG}
    GIT_SHALLOW       ON
    CONFIGURE_COMMAND ${ASSIMP_CONFIGURE}
    BUILD_COMMAND     ${ASSIMP_MAKE}
    INSTALL_COMMAND   ${ASSIMP_INSTALL}
)

set(ASSIMP_LIB           ${ASSIMP_ROOT}/lib/assimp)
set(ASSIMP_INCLUDE_DIR   ${ASSIMP_ROOT}/include)