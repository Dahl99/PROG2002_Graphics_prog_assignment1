cmake_minimum_required(VERSION 3.12)

project(Assignment1)

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external/glfw-3.3.2)
add_subdirectory(external/glew-cmake-2.1.0)

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
	
	src/framework/consts.hpp)


target_compile_definitions(Assignment1 PRIVATE GLEW_STATIC)

target_link_libraries(Assignment1
	libglew_static
	glfw
	OpenGL::GL)
