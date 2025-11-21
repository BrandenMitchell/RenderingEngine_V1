#pragma once
#include <glad/glad.h>
#include "glm/glm.hpp"
#include <iostream>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextCoords;


    bool operator==(const Vertex& right) const {
        if (!(Position == right.Position)) {
            return false;
        }
        if (!(Normal == right.Normal)) {
            return false;
        }
        if (!(TextCoords == right.TextCoords)) {
            return false;
        }
        return true;
    }

};


class VertexBuffer {
private:

    unsigned int m_RendererID = 0;
    unsigned int m_Count = 0;
    unsigned int m_Size = 0;

public:
    
    VertexBuffer();  // default constructor

    VertexBuffer(const void* data, const unsigned int size);
    ~VertexBuffer();

    void VertexBufferPopulate(std::vector<Vertex> vertices);

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() const { return m_Count; }
    inline unsigned int GetSize() const { return m_Size; }

    VertexBuffer(VertexBuffer&& other) noexcept
        : m_RendererID(other.m_RendererID),
        m_Count(other.m_Count),
        m_Size(other.m_Size)
    {
        // Nullify source so it doesn’t delete the same GL buffer
        other.m_RendererID = 0;
        other.m_Count = 0;
        other.m_Size = 0;
    }

    //  Move assignment operator
    VertexBuffer& operator=(VertexBuffer&& other) noexcept
    {
        if (this != &other)
        {
            // Delete existing GL buffer if it exists
            if (m_RendererID != 0)
                glDeleteBuffers(1, &m_RendererID);

            m_RendererID = other.m_RendererID;
            m_Count = other.m_Count;
            m_Size = other.m_Size;

            // Nullify source
            other.m_RendererID = 0;
            other.m_Count = 0;
            other.m_Size = 0;
        }
        return *this;
    }

};
