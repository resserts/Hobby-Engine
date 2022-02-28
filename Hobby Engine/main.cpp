#include <math.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "shaders.h"
#include "variables.h"
#include "mesh.h"
#include "rb-collider.h"
#include "circle.h"

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


    circle circle[10];

    for (int i = 0; i < 10; i++) {
        circle[i].rb->position = vector(((i % 5) / 2.5f) - 0.8f, (floor(i / 5.0f) - 0.5f));
        circle[i].rb->velocity = vector(rand() % 100 / 10000.0f, rand() % 100 / 10000.0f);
        circle[i].refresh();
    }
         
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        //circleInBoxCol(*circle.collider, circle.rb);
        /*
        if (circlesColliding(*circle.collider, squareCol)) {
            
            //printf("%f", squareRb.velocity.x);
            circlesCollision(circle.rb, &squareRb);
            //printf("%f", circleRb.velocity.x);
        }*/
        for (int i = 0; i < 10; i++) {
			circleInBoxCol(*circle[i].collider, circle[i].rb);
            for (int j = 0; j < 10; j++) {
                if (i != j && circlesColliding(*circle[i].collider, *circle[j].collider)) {
                    circlesCollision(circle[i].rb, circle[j].rb);
                    //circle[j].refresh();
                    //circle[i].refresh();
                }
            }


            //circle[i].refresh();
        }
        for (int i = 0; i < 10; i++){
            circle[i].refresh();
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, (i + 5.0f) / 20.0f, (i + 0.0f) / 20.0f, (i + 10.0f) / 20.0f, 0.5f);

            renderMesh(*circle[i].mesh);
        }
        glfwSwapBuffers(window);
    }

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
