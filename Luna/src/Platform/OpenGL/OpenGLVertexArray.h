#pragma once

#include "Luna/Renderer/VertexArray.h"

namespace Luna
{
class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

    virtual const VertexBuffers& getVertexBuffers() const { return m_VertexBuffers; }
    virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return m_IndexBuffer; }

private:
    uint32_t m_RendererID;
    VertexBuffers m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

} // namespace Luna