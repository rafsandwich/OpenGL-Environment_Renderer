#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>  // For random numbers

// Function to generate noise texture
GLuint generateNoiseTexture(int width, int height) {
    unsigned char* data = new unsigned char[width * height * 3];

    // Fill the texture with random noise (values between 0 and 255)
    for (int i = 0; i < width * height * 3; i++) {
        data[i] = rand() % 256;  // Random value for R, G, B
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload the noise data to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete[] data;

    return texture;
}


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

// Function to draw a curved smile (arc)
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

    // Generate the noise texture
    GLuint noiseTexture = generateNoiseTexture(800, 600);

    // Set up coordinate system (2D)
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

        // Draw the static (noise texture) as the background
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, noiseTexture);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);

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