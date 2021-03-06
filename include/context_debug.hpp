#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GraphicsEngine {
    #ifdef GL_DEBUG
        inline size_t error_count = 0;

        void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

        void debug_activate();
    #endif
}