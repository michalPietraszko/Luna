#pragma once

#include "RendererAPI.h"

namespace Luna
{
class RenderCommand
{
public:
    static void setClearColor(const glm::vec4& color) { s_RendererAPI->setClearColor(color); }

    static void clear() { s_RendererAPI->clear(); }

    static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        s_RendererAPI->drawIndexed(vertexArray);
    }

private:
    static RendererAPI* s_RendererAPI;
};

} // namespace Luna
