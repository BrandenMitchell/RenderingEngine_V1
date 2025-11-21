#pragma once

#include <glad/glad.h>
#include <vector>


class IndexBuffer {
private: 
	unsigned int m_RendererID;
	unsigned int m_Count;
public: 
	IndexBuffer();
	IndexBuffer(const void* data, const unsigned int count);
	~IndexBuffer();


	void Bind() const;
	void UnBind() const;
	inline unsigned int GetCount() const { return m_Count; }
	void SetCount(unsigned int count);
	void PopulateBuffer(std::vector<unsigned int> indices);

	unsigned int GetID() const { return m_RendererID;  }
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    //  Move constructor
    IndexBuffer(IndexBuffer&& other) noexcept
        : m_RendererID(other.m_RendererID),
        m_Count(other.m_Count)
    {
        // Nullify source so it doesn’t delete the same buffer
        other.m_RendererID = 0;
        other.m_Count = 0;
    }

    //  Move assignment operator
    IndexBuffer& operator=(IndexBuffer&& other) noexcept
    {
        if (this != &other)
        {
            // Delete existing buffer if it exists
            if (m_RendererID != 0)
                glDeleteBuffers(1, &m_RendererID);

            m_RendererID = other.m_RendererID;
            m_Count = other.m_Count;

            // Nullify source
            other.m_RendererID = 0;
            other.m_Count = 0;
        }
        return *this;
    }

};

