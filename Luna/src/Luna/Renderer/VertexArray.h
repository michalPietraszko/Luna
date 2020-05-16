#pragma once

#include <memory>
#include <vector>
#include "Luna/Renderer/Buffer.h"

namespace Luna
{
class VertexArray
{
protected:
    using VertexBuffers = std::vector<std::shared_ptr<VertexBuffer>>;

public:
    virtual ~VertexArray() {}

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
    virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

    virtual const VertexBuffers& getVertexBuffers() const = 0;
    virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

    static VertexArray* create();
};

} // namespace Luna