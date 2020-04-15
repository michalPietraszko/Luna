#pragma once

namespace Luna
{
class GraphicsContext
{
public:
    virtual void init() = 0;
    virtual void swapBuffers() = 0;
};
} // namespace Luna