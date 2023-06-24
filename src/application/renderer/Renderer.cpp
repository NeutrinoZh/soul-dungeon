#include "Renderer.h"

namespace app {
    Renderer::Renderer(Shader* _shader) {
        m_shader = _shader;
        m_canvas = new float[800];
        for (size_t i = 0; i < 800; ++i)
            m_canvas[i] = rand() % 600;

        m_vertices = new float[18]{
            -1.0f, -1.0f,  0.0f,
             1.0f,  1.0f,  0.0f,
            -1.0f,  1.0f,  0.0f,

             1.0f, -1.0f,  0.0f,
            -1.0f, -1.0f,  0.0f,
             1.0f,  1.0f,  0.0f,
        };

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(
            GL_ARRAY_BUFFER, 18 * sizeof(float),
            m_vertices, GL_STATIC_DRAW
        );

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);    
    
        m_shader->use();
    }

    Renderer::~Renderer() {
        delete[] m_vertices;
    }

    void Renderer::draw() {
        m_shader->uFloatArray("canvas", 800, m_canvas);
        for (size_t i = 0; i < 800; ++i)
            m_canvas[i] = ((int)(m_canvas[i] + 1)) % 600;

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}