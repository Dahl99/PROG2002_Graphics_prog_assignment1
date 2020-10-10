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
#include "pacman.hpp"
#include "ghost.hpp"

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


    auto entityData = map1.GetPGPos(); // Fetching player and ghost positions as well as vertices

    // These indices will be used for player and ghosts
    std::vector<GLuint> charIndices;
    charIndices.push_back(0);
    charIndices.push_back(1);
    charIndices.push_back(2);
    charIndices.push_back(2);
    charIndices.push_back(3);
    charIndices.push_back(1);

    // Setting texture coordinates for player
    entityData.vertices[0].tex = glm::vec2(0.0f, 0.0f);
    entityData.vertices[1].tex = glm::vec2(1.0f / 6.0f, 0.0f);
    entityData.vertices[2].tex = glm::vec2(0.0f, 1.0f / 4.0f);
    entityData.vertices[3].tex = glm::vec2(1.0f / 6.0f, 1.0f / 4.0f);

    // Creating pacman character
    Pacman pacman(entityData.positions[0], entityData.vertices, charIndices);

    // Setting texture coordinates for ghosts
    entityData.vertices[0].tex = glm::vec2(2.0f / 3.0f, 0.0f);
    entityData.vertices[1].tex = glm::vec2(5.0f / 6.0f, 0.0f);
    entityData.vertices[2].tex = glm::vec2(2.0f / 3.0f, 1.0f / 4.0f);
    entityData.vertices[3].tex = glm::vec2(5.0f / 6.0f, 1.0f / 4.0f);

    // Creating ghosts and adding them to a vector
    std::vector<std::shared_ptr<Ghost>> ghosts;
    for (int i = 1; i < entityData.positions.size(); i++)
    {
        auto ghost = std::make_shared<Ghost>(entityData.positions[i], entityData.vertices, charIndices);
        ghosts.push_back(ghost);
    }

    // Creating the MVP matrix
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.8f, 0.0f));
    glm::mat4 projection = glm::ortho(0.0f, 28.0f, 0.0f, 36.0f, -1.0f, 1.0f);
    //glm::mat4 MVP = projection;


    // Initializing shaders, setting projection matrix and texture for entities

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

    // Variables used to find delta time
    GLfloat dt, curTime, lastTime;
    dt = curTime = lastTime = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        updateDeltaTime(dt, curTime, lastTime); // Updating delta time
        glfwPollEvents();

        renderer.Clear();   // Clearing screen

        renderer.Draw(tileVao, tileIbo, tileShader);    // Drawing map

        renderer.Draw(collVao, collIbo, tileShader);



        // Move up
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 0);
            pacman.UpdateSprite(charShader, 0);
        }
        // Move down
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 2);
            pacman.UpdateSprite(charShader, 2);
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 1);
            pacman.UpdateSprite(charShader, 1);
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            pacman.UpdatePos(dt, 3);
            pacman.UpdateSprite(charShader, 3);
        }

        pacman.Draw(charShader);                  // Drawing pacman

        for (auto& ghost : ghosts)                // Drawing all ghosts
        {
            //ghost->UpdateSprite(charShader, 1);
            ghost->Draw(charShader);
        }

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

