#pragma once

namespace Luna
{
enum class ShaderDataType
{ // clang-format off
    None = 0, 
    Float, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool
}; // clang-format on

namespace BufferHelpers
{
enum class GlType
{
    glFloat,
    glInt,
    glBool
};

struct ShaderDataTypeProps
{
    ShaderDataType type{};
    uint32_t typeSize{};
    uint32_t componentCount{};
    GlType glBaseType{GlType::glFloat};
};

class ShaderDataTypes
{
    constexpr static auto floatSize = sizeof(float);
    constexpr static auto intSize = sizeof(int);
    constexpr static auto boolSize = sizeof(bool);

    constexpr static auto CMP_CNT_1 = 1u;
    constexpr static auto CMP_CNT_2 = 2u;
    constexpr static auto CMP_CNT_3 = 3u;
    constexpr static auto CMP_CNT_4 = 4u;
    constexpr static auto CMP_CNT_9 = CMP_CNT_3 * CMP_CNT_3;
    constexpr static auto CMP_CNT_16 = CMP_CNT_4 * CMP_CNT_4;

    constexpr static auto glFloat = GlType::glFloat;
    constexpr static auto glInt = GlType::glFloat;
    constexpr static auto glBool = GlType::glFloat;

    // clang-format off
    constexpr static auto numOfShaderDataTypes = 11u;
    constexpr static std::array<ShaderDataTypeProps, numOfShaderDataTypes> shaderTypesInfos
    {
        ShaderDataTypeProps{ShaderDataType::Float,  floatSize * CMP_CNT_1,  CMP_CNT_1,  glFloat},
        ShaderDataTypeProps{ShaderDataType::Float2, floatSize * CMP_CNT_2,  CMP_CNT_2,  glFloat},
        ShaderDataTypeProps{ShaderDataType::Float3, floatSize * CMP_CNT_3,  CMP_CNT_3,  glFloat},
        ShaderDataTypeProps{ShaderDataType::Float4, floatSize * CMP_CNT_4,  CMP_CNT_4,  glFloat},
        ShaderDataTypeProps{ShaderDataType::Mat3,   floatSize * CMP_CNT_9,  CMP_CNT_9,  glFloat},
        ShaderDataTypeProps{ShaderDataType::Mat4,   floatSize * CMP_CNT_16, CMP_CNT_16, glFloat},
        ShaderDataTypeProps{ShaderDataType::Int,    intSize   * CMP_CNT_1,  CMP_CNT_1,  glInt},
        ShaderDataTypeProps{ShaderDataType::Int2,   intSize   * CMP_CNT_2,  CMP_CNT_2,  glInt},
        ShaderDataTypeProps{ShaderDataType::Int3,   intSize   * CMP_CNT_3,  CMP_CNT_3,  glInt},
        ShaderDataTypeProps{ShaderDataType::Int4,   intSize   * CMP_CNT_4,  CMP_CNT_4,  glInt},
        ShaderDataTypeProps{ShaderDataType::Bool,   boolSize  * CMP_CNT_1,  CMP_CNT_1,  glBool}
    }; // clang-format on

public:
    constexpr static ShaderDataTypeProps get(const ShaderDataType type)
    {
        for (int i = 0; i < numOfShaderDataTypes; i++)
        {
            if (shaderTypesInfos.at(i).type == type) return shaderTypesInfos.at(i);
        }
        LN_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return {};
    }
};
} // namespace BufferHelpers

static uint32_t shaderDataTypeSize(ShaderDataType type)
{
    return BufferHelpers::ShaderDataTypes::get(type).typeSize;
}

static auto shaderDataTypeGlType(ShaderDataType type)
{
    return BufferHelpers::ShaderDataTypes::get(type).glBaseType;
}
} // namespace Luna