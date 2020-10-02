#include <cstdlib>
#include <ios>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "framework/globals.hpp"
#include "framework/tilemap.hpp"
#include "framework/vao.hpp"
#include "framework/vbo.hpp"
#include "framework/vbl.hpp"
#include "framework/ibo.hpp"
#include "framework/shader.hpp"
#include "framework/renderer.hpp"

// Function declarations
GLFWwindow* initWindow();

// Error function for GLFW
void GLFWErrorCallback(int code, const char* description);

// Error function for OpenGL
void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

// Entry point
int main(void)
{
    framework::Map map1(framework::LEVELPATH0);
    
    map1.PrintMap();

    std::vector<framework::Vertex> vert = map1.retMapVertices();
    std::vector<GLuint> indice = map1.retMapIndices();
    
    //framework::Tile shit;
    //shit.botLeft.pos.x = 0.0f;
    //shit.botLeft.pos.y = 0.0f;
    //shit.botRight.pos.x = 1.0f;
    //shit.botRight.pos.y = 0.0f;
    //shit.topLeft.pos.x = 0.0f;
    //shit.topLeft.pos.y = 1.0f;
    //shit.topRight.pos.x = 1.0f;
    //shit.topRight.pos.y = 1.0f;

    //shit.botLeft.col.x = 0.0f;
    //shit.botLeft.col.y = 0.0f;
    //shit.botLeft.col.z = 1.0f;
    //shit.botRight.col.x = 0.0f;
    //shit.botRight.col.y = 0.0f;
    //shit.botRight.col.z = 1.0f;
    //shit.topLeft.col.x = 0.0f;
    //shit.topLeft.col.y = 0.0f;
    //shit.topLeft.col.z = 1.0f;
    //shit.topRight.col.x = 0.0f;
    //shit.topRight.col.y = 0.0f;
    //shit.topRight.col.z = 1.0f;

    //std::vector<framework::Vertex> vert;
    //vert.push_back(shit.botLeft);
    //vert.push_back(shit.botRight);
    //vert.push_back(shit.topLeft);
    //vert.push_back(shit.topRight);
    //std::vector<GLuint> indice = { 0, 1, 2, 2, 3, 1 };

    glfwSetErrorCallback(GLFWErrorCallback);

    auto window = initWindow();
    if (window == nullptr)
    {
        glfwTerminate();
        std::cin.get();
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
    //GLfloat vertices[28] = {
    //1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //3.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //3.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //1.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
    //};

    //GLuint indices[6] = {
    //    0, 1, 2,
    //    2, 3, 0
    //};

    framework::VertexArray vao;                                 // Create a vertex array

    //framework::VertexBuffer vbo(vertices, sizeof(vertices));    // Create a vertex buffer
    framework::VertexBuffer vbo(vert, sizeof((framework::Vertex*)vert.data()));    // Create a vertex buffer

    framework::VertexBufferLayout vbl;                          // Create a vertex buffer layout
    vbl.Push<GLfloat>(2);                                       // Setting the layout for the vertex buffer
    vbl.Push<GLfloat>(3);                                       // Setting the layout for the vertex buffer
    vbl.Push<GLfloat>(2);                                       // Setting the layout for the vertex buffer

    vao.AddBuffer(vbo, vbl);                                    // Populating the vertex buffer

    framework::IndexBuffer ibo(indice, indice.size());

    framework::Shader shader(framework::VERTSHADERPATH, framework::FRAGSHADERPATH);
    shader.Bind();

    glm::mat4 projection = glm::ortho(0.0f, 28.0f, 0.0f, 36.0f, -1.0f, 1.0f);

    shader.SetUniformMat4f("u_MVP", projection);

    framework::Renderer renderer;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        renderer.Clear();
        renderer.Draw(vao, ibo, shader);

        glfwSwapBuffers(window);

        // Exit the loop if escape is pressed
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------------------
//                                  Functions
//------------------------------------------------------------------------------------------

GLFWwindow* initWindow()
{
    if (!glfwInit())
    {
        std::cin.get();
        return nullptr;
    }

    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(framework::WINDOWSIZEX, framework::WINDOWSIZEY, "2D PacMan", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();

        //std::cin.get();

        return nullptr;
        //return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        //std::cerr << "GLEW intialization failure:" << glewGetErrorString(error) << "\n";
        //std::cin.get();

        glfwTerminate();

        return nullptr;
        //return EXIT_FAILURE;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSwapInterval(1);
    return window;
}

void GLFWErrorCallback(int code, const char* description)
{
    std::cerr << "Error " << "0x" << std::hex << code << ':' << description << "\n";
}

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
