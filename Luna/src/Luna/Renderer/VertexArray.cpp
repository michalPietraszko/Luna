#include "lnpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Luna
{
VertexArray* VertexArray::create()
{
    switch (Renderer::getAPI())
    {
        case RendererAPI::None:
            LN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexArray();
    }

    LN_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Luna