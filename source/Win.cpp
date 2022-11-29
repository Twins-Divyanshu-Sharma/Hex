#include "Win.h"




Win::Win()
{
    createWindow();
}

Win::~Win()
{

}

void Win::createWindow()
{
    if(!glfwInit())
    {
        std::cerr<<"unable to initialize window"<<std::endl;
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,1); 
    glfwWindow = glfwCreateWindow(width,height,"Hex", NULL, NULL);

    
    if(!glfwWindow)
    {
        std::cerr<<"unable to make window"<<std::endl;
        glfwTerminate();
        return;
    }


    glfwMakeContextCurrent(glfwWindow);
    glViewport(0,0,width,height);

    glfwSetFramebufferSizeCallback(glfwWindow,resize);
}

void Win::resize(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

bool Win::isClosed()
{
    return glfwWindowShouldClose(glfwWindow);
}

void Win::pollEvents()
{
    if(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow,true);
    glfwPollEvents();
}

void Win::swapBuffers()
{
    glfwSwapBuffers(glfwWindow);
}

void Win::terminate()
{
    glfwTerminate();
}

bool Win::keyPressed(int keyCode)
{
    return glfwGetKey(glfwWindow, keyCode) == GLFW_PRESS;
}

bool Win::keyReleased(int keyCode)
{
    return glfwGetKey(glfwWindow, keyCode) == GLFW_RELEASE;
}

float Win::getAspectRatio()
{
    return (float)width/(float)height;
}
