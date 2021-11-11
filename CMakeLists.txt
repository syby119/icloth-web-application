cmake_minimum_required(VERSION 3.15)

########## include third party library ##########
# add_subdirectory(external/grpc)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/imgui)
add_subdirectory(external/stb)
add_subdirectory(external/tiny_obj_loader)

############## include projects #################
add_subdirectory(client)
# add_subdirectory(server)