#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>
#include <stdio.h>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
        return 1;

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "MST Visualizer", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    while (!glfwWindowShouldClose(window))
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
	return 0;
};
