

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "shaders.h"
#include "variables.h"
#include "vertex-utils.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;

    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);


    float vertices[] = {
        -0.5f * hW, -0.5f,
         0.5f * hW, -0.5f,
         0.5f * hW,  0.5f,
        -0.5f * hW,  0.5f
    };

    unsigned int indices[] = {
        0,1,2,
        0,2,3
    };

    indexVertex vertex;
    bindIndexMesh(vertex, vertices, sizeof(vertices), indices, sizeof(indices));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < sizeof(vertices) / sizeof(float); i++) {
            vertices[i] += 0.01f;
        }

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.1f, 0.1f, 0.1f, 1.0f);

        glBindBuffer(GL_ARRAY_BUFFER, vertex.buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

        glBindVertexArray(vertex.array);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vertex.array);
    glDeleteBuffers(1, &vertex.buffer);
    glDeleteBuffers(1, &vertex.index);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
};
