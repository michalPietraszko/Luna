#pragma once

#include "Luna/Renderer/RendererAPI.h"

namespace Luna
{
class OpenGLRendererAPI : public RendererAPI
{
public:
    virtual void setClearColor(const glm::vec4& color) override;
    virtual void clear() override;

    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
};

} // namespace Luna