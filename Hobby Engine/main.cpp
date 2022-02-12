#include <math.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "shaders.h"
#include "variables.h"
#include "mesh.h"
#include "rb-collider.h"

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


    mesh square = CircleMesh(36, 2);
    mesh circle = CircleMesh(36, 1);

    circle = moveMesh(circle, vector(0.7f, 0.5f));
    square = moveMesh(square, vector(-0.7f, -0.1f));
    circleCollider circleCol(circle.position, 1);
    circleCollider squareCol(square.position, 2);
    rigidBody circleRb(circle.position);
    rigidBody squareRb(square.position);
    
    circleRb.velocity = vector(-0.01f, 0.01f);
    squareRb.velocity = vector(0.01f, -0.01f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*float forceX = 0;
        int stateD = glfwGetKey(window, GLFW_KEY_D);
        if (stateD == GLFW_PRESS)
        {
            forceX = 0.005f;
        }
        int stateA = glfwGetKey(window, GLFW_KEY_A);
        if (stateA == GLFW_PRESS)
        {
            forceX = -0.005f;
        }

        float forceY = 0;
        float gravity = -0.01f;
        int stateW = glfwGetKey(window, GLFW_KEY_W);
        if (stateW == GLFW_PRESS)
        {
            forceY = 0.05f;
        }
        
        rb.velocity.x = forceX;
        rb.velocity.y = forceY;*/

        circleInBoxCol(circleCol, &circleRb);
        circleInBoxCol(squareCol, &squareRb);

        if (circlesColliding(circleCol, squareCol)) {
            
            //printf("%f", squareRb.velocity.x);
            circlesCollision(&circleRb, &squareRb);
            //printf("%f", circleRb.velocity.x);
        }
        
        circleRb.refresh();
        squareRb.refresh();

        square = moveMesh(square, squareRb.velocity);
        circle = moveMesh(circle, circleRb.velocity);
        
        circleCol.position = circle.position;
        squareCol.position = square.position;
        
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.8f, 0.f, 0.5f, 0.5f);
        
        renderMesh(square);
        
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.5f, 0.f, 0.8f, 0.5f);

        renderMesh(circle);

        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &square.vertex.array);
    glDeleteBuffers(1, &square.vertex.buffer);
    glDeleteBuffers(1, &square.vertex.index);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    square.freeArrays();
    circle.freeArrays();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
};
