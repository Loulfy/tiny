#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>

// Declared to make C99 happy !
bool     ImGui_ImplGlfw_InitForOpenGL(GLFWwindow* window, bool install_callbacks);
void     ImGui_ImplGlfw_Shutdown();
void     ImGui_ImplGlfw_NewFrame();

bool     ImGui_ImplOpenGL3_Init(const char* glsl_version);
void     ImGui_ImplOpenGL3_Shutdown();
void     ImGui_ImplOpenGL3_NewFrame();
void     ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data);

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

/* Platform */
static GLFWwindow *win;
struct ImGuiContext* ctx;
struct ImGuiIO* io;
    
void gui_init()
{
    // IMGUI_CHECKVERSION();
    ctx = igCreateContext(NULL);
    io  = igGetIO();

    const char* glsl_version = "#version 330 core";
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    igStyleColorsDark(NULL);
}

void gui_terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igDestroyContext(ctx);
}

void gui_render()
{
    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void gui_update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();

    igBegin("Test", NULL, 0);
    igText("Test");
    igButton("Test",(struct ImVec2){0,0});
    igEnd();

    // // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. 
    // // Here we just want to make the demo initial state a bit more friendly!
    // igSetNextWindowPos((struct ImVec2){0,0}, ImGuiCond_FirstUseEver,(struct ImVec2){0,0} ); 
    igShowDemoWindow(NULL);
}


int main(int argc, char** argv)
{
    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tiny", NULL, NULL);
    glfwMakeContextCurrent(win);
    bool err = gladLoadGL() == 0;
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }
    
    gui_init();

    // glfwSetWindowSizeCallback(win, onResize);
    int width, height;
    glfwGetWindowSize(win, &width, &height);
     
    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    
    while (!glfwWindowShouldClose(win))
    {
        /* Input */
        glfwPollEvents();
    
        gui_update();

        /* Draw */
        glfwGetWindowSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 0.0);

        gui_render();

        glfwSwapBuffers(win);
    }

    gui_terminate();
    glfwTerminate();

}
