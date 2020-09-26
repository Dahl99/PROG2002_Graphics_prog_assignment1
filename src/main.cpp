#include <cstdlib>
#include <ios>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "framework/globals.hpp"
#include "framework/tilemap.hpp"
#include "framework/vbo.hpp"
#include "framework/shader.hpp"



// Error function for GLFW
void GLFWErrorCallback(int code, const char* description)
{
    std::cerr << "Error " << "0x" << std::hex << code << ':' << description << "\n";
}

// Error function for OpenGL
void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    std::cerr << "GL CALLBACK:" << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") <<
        "type = 0x" << type <<
        ", severity = 0x" << severity <<
        ", message =" << message << "\n";
}

// Entry point
int main(void)
{
    framework::Map map1(framework::LEVELPATH0);
    
    map1.PrintMap();

    glfwSetErrorCallback(GLFWErrorCallback);

    // Initialization of glfw.
    if (!glfwInit())
    {
        std::cin.get();

        return EXIT_FAILURE;
    }//*-

    // Create a window
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    auto window = glfwCreateWindow(800, 600, "Hello Triangle", nullptr, nullptr);
    if (window == nullptr)
    {

        glfwTerminate();

        std::cin.get();

        return EXIT_FAILURE;
    }

    //Set the OpenGL context
    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        std::cerr << "GLEW intialization failure:" << glewGetErrorString(error) << "\n";
        std::cin.get();

        glfwTerminate();

        return EXIT_FAILURE;
    }

    // Enable capture of debug output.
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    // Print OpenGL data
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    // Clear the background
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);

    // Create a triangle geometry
    GLfloat triangle[3 * 2] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.0f, 0.5f
    };

    // Create a vertex array
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    // Create a vertex buffer
    framework::VertexBuffer vbo(triangle, sizeof(triangle));

    // Populate the vertex buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
    glEnableVertexAttribArray(0);

    framework::Shader shader(framework::VERTSHADERPATH, framework::FRAGSHADERPATH);
    shader.Bind();

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        vbo.Bind();
        shader.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        // Exit the loop if escape is pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}