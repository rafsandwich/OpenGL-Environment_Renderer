#include <GLFW/glfw3.h>
#include <cmath>

// Constants for circle resolution
const int SEGMENTS = 100; // Number of segments for smooth circles

// Function to draw a filled circle
void drawCircle(float centerX, float centerY, float radius, float r, float g, float b) {
    glColor3f(r, g, b); // Set colour
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center of circle
    for (int i = 0; i <= SEGMENTS; ++i) {
        float angle = 2.0f * 3.1415926f * float(i) / float(SEGMENTS);
        float x = centerX + radius * cosf(angle);
        float y = centerY + radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw a curved line (arc) for the smile
void drawArc(float centerX, float centerY, float radius, float startAngle, float endAngle, float r, float g, float b) {
    glColor3f(r, g, b); // Set colour
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= SEGMENTS; ++i) {
        float angle = startAngle + (endAngle - startAngle) * i / SEGMENTS;
        float x = centerX + radius * cosf(angle);
        float y = centerY + radius * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

int main() {
    // Initialise GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smiley face confined to the bounds of an old TV!", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the context current
    glfwMakeContextCurrent(window);

    // Set up coordinate system
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Normalise coordinates to [-1, 1]

    // Smiley face position
    float faceX = 0.0f, faceY = 0.0f;
    float speedX = 0.0002f, speedY = 0.0001f;  // How quick it moves across the screen

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Get framebuffer size to adjust to window size
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height); // Adjust the viewport to the new size

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the smiley face
        drawCircle(faceX, faceY, 0.5f, 0.8f, 0.6f, 1.0f);   // Head (light purple)
        drawCircle(faceX - 0.2f, faceY + 0.2f, 0.05f, 0.0f, 0.0f, 0.0f); // Left eye (black)
        drawCircle(faceX + 0.2f, faceY + 0.2f, 0.05f, 0.0f, 0.0f, 0.0f);  // Right eye (black)

        // Draw a curved smile (arc)
        drawArc(faceX, faceY - 0.2f, 0.3f, 3.14f / 6, 5 * 3.14f / 6, 0.0f, 0.0f, 0.0f);

        // Update position of the smiley face
        faceX += speedX;
        faceY += speedY;

        // Bounce off the walls (change direction when hitting the edges)
        if (faceX >= 1.0f || faceX <= -1.0f) {
            speedX = -speedX;
        }
        if (faceY >= 1.0f || faceY <= -1.0f) {
            speedY = -speedY;
        }

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// testing everything works below

//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}