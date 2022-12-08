#ifndef khidki
#define khidki

#include <GLFW/glfw3.h>
#include <iostream>

class Win
{
    public:
        Win();
        ~Win();
        void createWindow();
        bool isClosed();
        void pollEvents();
        void swapBuffers();
        void terminate();
        bool keyPressed(int);
        bool keyReleased(int);
        float getAspectRatio();
        void close();
        static char currentChar;
        static bool charInputEvent;
    private:
        int width = 700;
        int height = 700;
        GLFWwindow* glfwWindow;
        static void resize(GLFWwindow*, int, int);
        static void char_callback(GLFWwindow*,unsigned int);

};

#endif
