#include "lnpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Luna
{
VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
{
    switch (Renderer::getAPI())
    {
        case RendererAPI::API::None:
            LN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
    }

    LN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
{
    switch (Renderer::getAPI())
    {
        case RendererAPI::API::None:
            LN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
    }

    LN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Luna