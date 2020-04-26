#pragma once
#include "BufferHelpers.h"

namespace Luna
{
struct BufferElement
{
    std::string name;
    ShaderDataType type;
    uint32_t size;
    uint32_t offset;
    bool normalized;

    BufferElement() {}

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
        : name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized)
    {
    }

    uint32_t getComponentCount() const { return BufferHelpers::ShaderDataTypes::get(type).componentCount; }
};

class BufferLayout
{
    using BufferElements = std::vector<BufferElement>;

public:
    BufferLayout() = default;

    BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements) { calculateOffsetsAndStride(); }

    inline uint32_t getStride() const { return m_Stride; }
    inline const BufferElements& getElements() const { return m_Elements; }

    BufferElements::iterator begin() { return m_Elements.begin(); }
    BufferElements::iterator end() { return m_Elements.end(); }
    BufferElements::const_iterator begin() const { return m_Elements.begin(); } // cbegin???
    BufferElements::const_iterator end() const { return m_Elements.end(); }

private:
    void calculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto& element : m_Elements)
        {
            element.offset = offset;
            offset += element.size;
            m_Stride += element.size;
        }
    }

private:
    BufferElements m_Elements;
    uint32_t m_Stride = 0;
};

class VertexBuffer
{
public:
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual const BufferLayout& getLayout() const = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;

    static VertexBuffer* create(float* vertices, uint32_t size);
};

class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual uint32_t getCount() const = 0;

    static IndexBuffer* create(uint32_t* indices, uint32_t size);
};

} // namespace Luna