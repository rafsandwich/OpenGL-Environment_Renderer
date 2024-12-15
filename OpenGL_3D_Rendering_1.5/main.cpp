#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>  // For random numbers

GLuint generateNoiseTexture(int width, int height) {
    unsigned char* data = new unsigned char[width * height * 3];  // RGB texture

    // Fill the texture with random noise (values between 0 and 255)
    for (int i = 0; i < width * height * 3; i++) {
        data[i] = rand() % 256;  // Random value for R, G, B
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Use linear filtering for smoothing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use linear filtering for magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat texture on X-axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat texture on Y-axis

    // Upload the noise data to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    delete[] data;

    return texture;
}

void renderNoiseTexture(GLuint noiseTexture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, noiseTexture);  // Bind the noise texture

    // Use a full-screen quad to display the texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);  // Bottom-left corner
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);  // Bottom-right corner
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);  // Top-right corner
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);  // Top-left corner
    glEnd();

    glDisable(GL_TEXTURE_2D);
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

    GLuint noiseTexture = generateNoiseTexture(1024, 1024);  // Generate the noise texture
    while (!glfwWindowShouldClose(window)) {
        // Get framebuffer size to adjust to window size
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);  // Adjust the viewport to the new size

        // Clear screen (black background)
        glClear(GL_COLOR_BUFFER_BIT);

        // Render noise texture on full-screen quad
        renderNoiseTexture(noiseTexture);

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