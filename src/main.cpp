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


    framework::ShaderVertData vert = map1.retMapVertices();
    std::vector<GLuint> *indice = map1.retMapIndices();


    //  These vertices contain: Position, Color and Texture Coords
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


    framework::VertexArray tileVao;                             // Create a vertex array
    framework::VertexArray characterVao;                        // Create a vertex array

    framework::VertexBuffer tileVbo(vert.wallVertices);    // Create a vertex buffer
    framework::VertexBuffer characterVbo(CharacterVertices, sizeof(CharacterVertices));    // Create a vertex buffer


    framework::IndexBuffer ibo(indice[0]);

    framework::VertexBufferLayout vbl;          // Create a vertex buffer layout
    vbl.Push<GLfloat>(2);                       // Adding position floats to layout
    vbl.Push<GLfloat>(3);                       // Adding color floats to layout
    vbl.Push<GLfloat>(2);                       // Adding tex coords floats to layout


    tileVao.AddBuffer(tileVbo, vbl);                    // Populating the vertex buffer
    characterVao.AddBuffer(characterVbo, vbl);      // Populating the vertex buffer


    //framework::VertexArray vao2;
    //framework::VertexBuffer vbo2(vert.collectibleVertices);
    //framework::VertexBufferLayout vbl2;

    //vbl2.Push<GLfloat>(2);                   // Adding position floats to the layout
    //vbl2.Push<GLfloat>(3);                   // Adding color floats to the layout
    //vbl2.Push<GLfloat>(2);                   // Adding texture coord floats to the layout

    framework::IndexBuffer tileIbo(indice[0]);
    //framework::IndexBuffer ibo2(indice[1]);
    framework::IndexBuffer characterIbo(CharacterIndices, 6);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.8f, 0.0f));
    glm::mat4 projection = glm::ortho(0.0f, 28.0f, 0.0f, 36.0f, -1.0f, 1.0f);
    glm::mat4 MVP = projection;

    framework::Shader tileShader(framework::TILEVERTSHADERPATH, framework::TILEFRAGSHADERPATH);
    tileShader.Bind();
    tileShader.SetUniformMat4f("u_MVP", projection);

    framework::Shader charShader(framework::CHARVERTGSHADERPATH, framework::CHARFRAGSHADERPATH);
    charShader.Bind();
    charShader.SetUniformMat4f("u_MVP", projection);
    charShader.SetUniform1i("uTexture", 0);

    framework::Texture texture(framework::PACMANPICTUREPATH);
    texture.Bind(0);    //  Binding to texture slot 0

    framework::Renderer renderer;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        renderer.Clear();
        renderer.Draw(tileVao, tileIbo, tileShader);
        renderer.Draw(characterVao, characterIbo, charShader);

        //renderer.Clear();
        //renderer.Draw(vao2, ibo2, tileShader);

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
