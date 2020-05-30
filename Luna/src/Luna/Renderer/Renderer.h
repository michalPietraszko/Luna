#pragma once

#include "RendererCommand.h"

namespace Luna
{
class Renderer
{
public:
    static void beginScene();
    static void endScene();

    static void submit(const std::shared_ptr<VertexArray>& vertexArray);

    static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
};

} // namespace Luna