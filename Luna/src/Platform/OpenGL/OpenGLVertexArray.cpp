#include "lnpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Luna
{
static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (shaderDataTypeGlType(type))
    {
        case BufferHelpers::GlType::glFloat:
            return GL_FLOAT;
        case BufferHelpers::GlType::glInt:
            return GL_INT;
        case BufferHelpers::GlType::glBool:
            return GL_BOOL;
    }

    LN_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return {};
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_RendererID); // old-new
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::bind() const
{
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    LN_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

    glBindVertexArray(m_RendererID);
    vertexBuffer->bind();

    uint32_t index = 0;
    const auto& layout = vertexBuffer->getLayout();
    for (const auto& element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            element.getComponentCount(),
            shaderDataTypeToOpenGLBaseType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.getStride(),
            (const void*)element.offset);
        index++;
    }

    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->bind();

    m_IndexBuffer = indexBuffer;
}

} // namespace Luna