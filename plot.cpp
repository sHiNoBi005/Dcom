#include "plot.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include<vector>

int margin = 0.5;   

static void drawGrid(int bits, int samp_per_bit) {
    glLineWidth(1.0f);

    // Manchester types
    if (samp_per_bit == 2) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0xAAAA);//hex  rep for 101010...(on/off) making doted line taking 1 bit 
        glColor3f(0.85f, 0.85f, 0.85f);
        glBegin(GL_LINES);
        for (int i = 0; i < bits; i++) {
            glVertex2f(i + 0.5f, -2);
            glVertex2f(i + 0.5f,  2);
        }
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }

    // solid bit boundaries
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_LINES);
    for (int i = 0; i <= bits; i++) {
        glVertex2f(i, -2);
        glVertex2f(i,  2);
    }
    glEnd();

    // voltage reference lines: +1 and -1 light, zero axis darker
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_LINES);
    glVertex2f(0,  1);  glVertex2f(bits,  1);
    glVertex2f(0, -1);  glVertex2f(bits, -1);
    glEnd();

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    glVertex2f(0, 0);   glVertex2f(bits, 0);
    glEnd();
}

static void drawSignal(const std::vector<double>& levels, int samp_per_bit) {
    glColor3f(0.0f, 0.6f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < levels.size(); i++) {
        float x0 = (float)i / samp_per_bit;
        float x1 = (float)(i + 1) / samp_per_bit;
        glVertex2f(x0, levels[i]);
        glVertex2f(x1, levels[i]);
    }
    glEnd();
}

void plotSignal(const std::vector<double>& levels, int samp_per_bit) {
    int bits = levels.size() / samp_per_bit;
    int width = std::min(1800, std::max(800, bits * 40));

    if (!glfwInit()) return;
    GLFWwindow* win = glfwCreateWindow(width, 400,"line encoding", nullptr, nullptr);//title.c_str() converts str to text on window
    if (!win) { glfwTerminate(); return; }
    glfwMakeContextCurrent(win);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-margin, bits + margin, -2, 2, -1, 1);

    while (!glfwWindowShouldClose(win)) {
        int w, h;
        glfwGetFramebufferSize(win, &w, &h);
        glViewport(0, 0, w, h);

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        drawGrid(bits, samp_per_bit);
        drawSignal(levels, samp_per_bit);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwDestroyWindow(win);
    glfwTerminate();
}
void plotSignal(const std::vector<int>& levels, int samplesPerBit) {
    std::vector<double> converted(levels.begin(), levels.end());
    plotSignal(converted, samplesPerBit);
}