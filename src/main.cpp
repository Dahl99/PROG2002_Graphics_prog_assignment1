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
#include "framework/texture.hpp"
#include "framework/renderer.hpp"
#include "framework/entity.hpp"

// Function declarations
GLFWwindow* initWindow();

void updateDeltaTime(GLfloat& dt, GLfloat& ct, GLfloat& lt);

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
    // Reading and creating the map
    framework::Map map1(framework::LEVELPATH0);

    map1.PrintMap();

    // Getting the map data
    framework::ShaderVertData vertices = map1.retMapVertices();
    std::vector<GLuint> wallIndices = map1.retMapIndices(map1.GetNumWalls());
    std::vector<GLuint> collIndices = map1.retMapIndices(map1.GetNumCollecs());

    //  These vertices contain: Position, Color and Texture Coords for pacman
    framework::Vertex CharacterVertices[4] = {
        glm::vec2(14.0f, 14.0f), glm::vec3(0.1f, 0.6f, 0.1f), glm::vec2(0.0f, 0.0f),
        glm::vec2(18.0f, 14.0f), glm::vec3(0.1f, 0.6f, 0.1f), glm::vec2(1.0f / 6.0f, 0.0f),
        glm::vec2(18.0f, 18.0f), glm::vec3(0.1f, 0.6f, 0.1f), glm::vec2(1.0f / 6.0f, 1.0f / 4.0f),
        glm::vec2(14.0f, 18.0f), glm::vec3(0.1f, 0.6f, 0.1f), glm::vec2(0.0f, 1.0f / 4.0f)
    };

    GLuint CharacterIndices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    std::vector<framework::Vertex> charVertices;
    std::vector<GLuint> charIndices;

    for (const framework::Vertex& vertex : CharacterVertices)
        charVertices.push_back(vertex);

    for (const GLuint& index : CharacterIndices)
        charIndices.push_back(index);

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enabling blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glfwSetInputMode(window, GLFW_KEY_ESCAPE, GL_TRUE);
    glfwSetInputMode(window, GLFW_KEY_LEFT, GL_TRUE);
    glfwSetInputMode(window, GLFW_KEY_RIGHT, GL_TRUE);
    glfwSetInputMode(window, GLFW_KEY_UP, GL_TRUE);
    glfwSetInputMode(window, GLFW_KEY_DOWN, GL_TRUE);


    // Preparing walls

    framework::VertexArray tileVao;               // Create a vertex array

    framework::VertexBuffer tileVbo(vertices.wallVertices);    // Create a vertex buffer

    framework::VertexBufferLayout vbl;            // Create a vertex buffer layout
    vbl.Push<GLfloat>(2);                         // Adding position floats to layout
    vbl.Push<GLfloat>(3);                         // Adding color floats to layout
    vbl.Push<GLfloat>(2);                         // Adding tex coords floats to layout

    tileVao.AddBuffer(tileVbo, vbl);              // Populating the vertex buffer

    framework::IndexBuffer tileIbo(wallIndices);


    // Preparing collectibles

    framework::VertexArray collVao;

    framework::VertexBuffer collVbo(vertices.collectibleVertices);

    collVao.AddBuffer(collVbo, vbl);

    framework::IndexBuffer collIbo(collIndices);


    // Creating pacman character
    framework::Entity pacman(glm::vec3(1.0f, 0.5f, 1.0f), charVertices, charIndices);

    // Creating the MVP matrix
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.8f, 0.0f));
    glm::mat4 projection = glm::ortho(0.0f, 28.0f, 0.0f, 36.0f, -1.0f, 1.0f);
    //glm::mat4 MVP = projection;


    // Shaders

    framework::Shader tileShader(framework::TILEVERTSHADERPATH, framework::TILEFRAGSHADERPATH);
    tileShader.Bind();
    tileShader.SetUniformMat4f("u_Projection", projection);

    framework::Shader charShader(framework::CHARVERTGSHADERPATH, framework::CHARFRAGSHADERPATH);
    charShader.Bind();
    charShader.SetUniformMat4f("u_Projection", projection);
    charShader.SetUniform1i("uTexture", 0);

    framework::Texture texture(framework::PACMANPICTUREPATH);
    texture.Bind(0);    //  Binding to texture slot 0

    framework::Renderer renderer;

    GLfloat dt, curTime, lastTime;
    dt = curTime = lastTime = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        updateDeltaTime(dt, curTime, lastTime);
        glfwPollEvents();

        renderer.Clear();   // Clearing screen

        renderer.Draw(tileVao, tileIbo, tileShader);    // Drawing map

        renderer.Draw(collVao, collIbo, tileShader);



        // Move forward
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 0);
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 2);
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 1);
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 3);
        }

        pacman.Draw(charShader);                        // Drawing pacman

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

void updateDeltaTime(GLfloat& dt, GLfloat& ct, GLfloat& lt)
{
    ct = static_cast<GLfloat>(glfwGetTime());
    dt = ct - lt;
    lt = ct;
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

