#include "lnpch.h"
#include "Renderer.h"

namespace Luna
{
void Renderer::beginScene() {}

void Renderer::endScene() {}

void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray)
{
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}
} // namespace Luna