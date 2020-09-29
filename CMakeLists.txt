cmake_minimum_required(VERSION 3.12)

project(Assignment1)

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(glm_DIR external/glm/cmake/glm)
find_package(glm REQUIRED)


add_subdirectory(external/glfw-3.3.2)
add_subdirectory(external/glew-cmake-2.1.0)
add_subdirectory(external/stb)

add_executable(Assignment1
	src/main.cpp
	
	src/framework/shader.hpp
	src/framework/shader.cpp

	src/framework/texture.hpp
	src/framework/texture.cpp

	src/framework/tilemap.hpp
	src/framework/tilemap.cpp

	src/framework/vao.hpp
	src/framework/vao.cpp
	
	src/framework/vbo.hpp
	src/framework/vbo.cpp
	
	src/framework/ibo.hpp
	src/framework/ibo.cpp
	
	src/framework/vbl.hpp

	src/framework/renderer.hpp
	src/framework/renderer.cpp

	src/framework/entities.hpp
	src/framework/entities.cpp
	
	src/framework/globals.hpp

	res/levels/level0 
	res/shaders/shader.vert
	res/shaders/shader.frag)


target_compile_definitions(Assignment1 PRIVATE GLEW_STATIC)

target_link_libraries(Assignment1
	libglew_static
	glfw
	glm::glm
	stbimage::stbimage
	OpenGL::GL)

# Copy resources to binary directory
add_custom_target(
    copy_res ALL
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
    COMMAND ${CMAKE_COMMAND} -E echo "Copied resource directory to binary directory ${CMAKE_CURRENT_BINARY_DIR}"
)