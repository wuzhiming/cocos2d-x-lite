#include "CoreStd.h"

#include "GFXDef.h"

namespace cc {
namespace gfx {

const uint DESCRIPTOR_BUFFER_TYPE = (uint)DescriptorType::STORAGE_BUFFER | (uint)DescriptorType::DYNAMIC_STORAGE_BUFFER |
                                    (uint)DescriptorType::UNIFORM_BUFFER | (uint)DescriptorType::DYNAMIC_UNIFORM_BUFFER;
const uint DESCRIPTOR_SAMPLER_TYPE = (uint)DescriptorType::SAMPLER;
const uint DESCRIPTOR_DYNAMIC_TYPE = (uint)DescriptorType::DYNAMIC_STORAGE_BUFFER | (uint)DescriptorType::DYNAMIC_UNIFORM_BUFFER;

const FormatInfo GFX_FORMAT_INFOS[] = {
    {"UNKNOWN", 0, 0, FormatType::NONE, false, false, false, false},
    {"A8", 1, 1, FormatType::UNORM, true, false, false, false},
    {"L8", 1, 1, FormatType::UNORM, false, false, false, false},
    {"LA8", 1, 2, FormatType::UNORM, false, false, false, false},

    {"R8", 1, 1, FormatType::UNORM, false, false, false, false},
    {"R8SN", 1, 1, FormatType::SNORM, false, false, false, false},
    {"R8UI", 1, 1, FormatType::UINT, false, false, false, false},
    {"R8I", 1, 1, FormatType::INT, false, false, false, false},
    {"R16F", 2, 1, FormatType::FLOAT, false, false, false, false},
    {"R16UI", 2, 1, FormatType::UINT, false, false, false, false},
    {"R16I", 2, 1, FormatType::INT, false, false, false, false},
    {"R32F", 4, 1, FormatType::FLOAT, false, false, false, false},
    {"R32UI", 4, 1, FormatType::UINT, false, false, false, false},
    {"R32I", 4, 1, FormatType::INT, false, false, false, false},

    {"RG8", 2, 2, FormatType::UNORM, false, false, false, false},
    {"RG8SN", 2, 2, FormatType::SNORM, false, false, false, false},
    {"RG8UI", 2, 2, FormatType::UINT, false, false, false, false},
    {"RG8I", 2, 2, FormatType::INT, false, false, false, false},
    {"RG16F", 4, 2, FormatType::FLOAT, false, false, false, false},
    {"RG16UI", 4, 2, FormatType::UINT, false, false, false, false},
    {"RG16I", 4, 2, FormatType::INT, false, false, false, false},
    {"RG32F", 8, 2, FormatType::FLOAT, false, false, false, false},
    {"RG32UI", 8, 2, FormatType::UINT, false, false, false, false},
    {"RG32I", 8, 2, FormatType::INT, false, false, false, false},

    {"RGB8", 3, 3, FormatType::UNORM, false, false, false, false},
    {"SRGB8", 3, 3, FormatType::UNORM, false, false, false, false},
    {"RGB8SN", 3, 3, FormatType::SNORM, false, false, false, false},
    {"RGB8UI", 3, 3, FormatType::UINT, false, false, false, false},
    {"RGB8I", 3, 3, FormatType::INT, false, false, false, false},
    {"RGB16F", 6, 3, FormatType::FLOAT, false, false, false, false},
    {"RGB16UI", 6, 3, FormatType::UINT, false, false, false, false},
    {"RGB16I", 6, 3, FormatType::INT, false, false, false, false},
    {"RGB32F", 12, 3, FormatType::FLOAT, false, false, false, false},
    {"RGB32UI", 12, 3, FormatType::UINT, false, false, false, false},
    {"RGB32I", 12, 3, FormatType::INT, false, false, false, false},

    {"RGBA8", 4, 4, FormatType::UNORM, true, false, false, false},
    {"BGRA8", 4, 4, FormatType::UNORM, true, false, false, false},
    {"SRGB8_A8", 4, 4, FormatType::UNORM, true, false, false, false},
    {"RGBA8SN", 4, 4, FormatType::SNORM, true, false, false, false},
    {"RGBA8UI", 4, 4, FormatType::UINT, true, false, false, false},
    {"RGBA8I", 4, 4, FormatType::INT, true, false, false, false},
    {"RGBA16F", 8, 4, FormatType::FLOAT, true, false, false, false},
    {"RGBA16UI", 8, 4, FormatType::UINT, true, false, false, false},
    {"RGBA16I", 8, 4, FormatType::INT, true, false, false, false},
    {"RGBA32F", 16, 4, FormatType::FLOAT, true, false, false, false},
    {"RGBA32UI", 16, 4, FormatType::UINT, true, false, false, false},
    {"RGBA32I", 16, 4, FormatType::INT, true, false, false, false},

    {"R5G6B5", 2, 3, FormatType::UNORM, false, false, false, false},
    {"R11G11B10F", 4, 3, FormatType::FLOAT, false, false, false, false},
    {"RGB5A1", 2, 4, FormatType::UNORM, true, false, false, false},
    {"RGBA4", 2, 4, FormatType::UNORM, true, false, false, false},
    {"RGB10A2", 2, 4, FormatType::UNORM, true, false, false, false},
    {"RGB10A2UI", 2, 4, FormatType::UINT, true, false, false, false},
    {"RGB9E5", 2, 4, FormatType::FLOAT, true, false, false, false},

    {"D16", 2, 1, FormatType::UINT, false, true, false, false},
    {"D16S8", 3, 1, FormatType::UINT, false, true, true, false},
    {"D24", 3, 1, FormatType::UINT, false, true, false, false},
    {"D24S8", 2, 1, FormatType::UINT, false, true, true, false},
    {"D32F", 4, 1, FormatType::FLOAT, false, true, false, false},
    {"D32FS8", 5, 2, FormatType::FLOAT, false, true, true, false},

    {"BC1", 1, 3, FormatType::UNORM, false, false, false, true},
    {"BC1_ALPHA", 1, 4, FormatType::UNORM, true, false, false, true},
    {"BC1_SRGB", 1, 3, FormatType::UNORM, false, false, false, true},
    {"BC1_SRGB_ALPHA", 1, 4, FormatType::UNORM, true, false, false, true},
    {"BC2", 1, 4, FormatType::UNORM, true, false, false, true},
    {"BC2_SRGB", 1, 4, FormatType::UNORM, true, false, false, true},
    {"BC3", 1, 4, FormatType::UNORM, true, false, false, true},
    {"BC3_SRGB", 1, 4, FormatType::UNORM, true, false, false, true},
    {"BC4", 1, 1, FormatType::UNORM, false, false, false, true},
    {"BC4_SNORM", 1, 1, FormatType::SNORM, false, false, false, true},
    {"BC5", 1, 2, FormatType::UNORM, false, false, false, true},
    {"BC5_SNORM", 1, 2, FormatType::SNORM, false, false, false, true},
    {"BC6H_UF16", 1, 3, FormatType::UFLOAT, false, false, false, true},
    {"BC6H_SF16", 1, 3, FormatType::FLOAT, false, false, false, true},
    {"BC7", 1, 4, FormatType::UNORM, true, false, false, true},
    {"BC7_SRGB", 1, 4, FormatType::UNORM, true, false, false, true},

    {"ETC_RGB8", 1, 3, FormatType::UNORM, false, false, false, true},
    {"ETC2_RGB8", 1, 3, FormatType::UNORM, false, false, false, true},
    {"ETC2_SRGB8", 1, 3, FormatType::UNORM, false, false, false, true},
    {"ETC2_RGB8_A1", 1, 4, FormatType::UNORM, true, false, false, true},
    {"ETC2_SRGB8_A1", 1, 4, FormatType::UNORM, true, false, false, true},
    {"EAC_R11", 1, 1, FormatType::UNORM, false, false, false, true},
    {"EAC_R11SN", 1, 1, FormatType::SNORM, false, false, false, true},
    {"EAC_RG11", 2, 2, FormatType::UNORM, false, false, false, true},
    {"EAC_RG11SN", 2, 2, FormatType::SNORM, false, false, false, true},

    {"PVRTC_RGB2", 2, 3, FormatType::UNORM, false, false, false, true},
    {"PVRTC_RGBA2", 2, 4, FormatType::UNORM, true, false, false, true},
    {"PVRTC_RGB4", 2, 3, FormatType::UNORM, false, false, false, true},
    {"PVRTC_RGBA4", 2, 4, FormatType::UNORM, true, false, false, true},
    {"PVRTC2_2BPP", 2, 4, FormatType::UNORM, true, false, false, true},
    {"PVRTC2_4BPP", 2, 4, FormatType::UNORM, true, false, false, true},
};

uint FormatSize(Format format, uint width, uint height, uint depth) {

    if (!GFX_FORMAT_INFOS[(uint)format].isCompressed) {
        return (width * height * depth * GFX_FORMAT_INFOS[(uint)format].size);
    } else {
        switch (format) {
            case Format::BC1:
            case Format::BC1_ALPHA:
            case Format::BC1_SRGB:
            case Format::BC1_SRGB_ALPHA:
                return (uint)std::ceil(width / 4) * (uint)std::ceil(height / 4) * 8 * depth;
            case Format::BC2:
            case Format::BC2_SRGB:
            case Format::BC3:
            case Format::BC3_SRGB:
            case Format::BC4:
            case Format::BC4_SNORM:
            case Format::BC6H_SF16:
            case Format::BC6H_UF16:
            case Format::BC7:
            case Format::BC7_SRGB:
                return (uint)std::ceil(width / 4) * (uint)std::ceil(height / 4) * 16 * depth;
            case Format::BC5:
            case Format::BC5_SNORM:
                return (uint)std::ceil(width / 4) * (uint)std::ceil(height / 4) * 32 * depth;

            case Format::ETC_RGB8:
            case Format::ETC2_RGB8:
            case Format::ETC2_SRGB8:
            case Format::ETC2_RGB8_A1:
            case Format::ETC2_SRGB8_A1:
            case Format::EAC_R11:
            case Format::EAC_R11SN:
                return (uint)std::ceil(width / 4) * (uint)std::ceil(height / 4) * 8 * depth;
            case Format::EAC_RG11:
            case Format::EAC_RG11SN:
                return (uint)std::ceil(width / 4) * (uint)std::ceil(height / 4) * 16 * depth;

            case Format::PVRTC_RGB2:
            case Format::PVRTC_RGBA2:
            case Format::PVRTC2_2BPP:
                return (uint)std::ceil(std::max(width, 16U) * std::max(height, 8U) / 4) * depth;
            case Format::PVRTC_RGB4:
            case Format::PVRTC_RGBA4:
            case Format::PVRTC2_4BPP:
                return (uint)std::ceil(std::max(width, 16U) * std::max(height, 8U) / 2) * depth;
            default: {
                return 0;
            }
        }
    }
}

const uint GFX_TYPE_SIZES[] = {
    0,  // UNKNOWN
    4,  // BOOL
    8,  // BOOL2
    12, // BOOL3
    16, // BOOL4
    4,  // INT
    8,  // INT2
    12, // INT3
    16, // INT4
    4,  // UINT
    8,  // UINT2
    12, // UINT3
    16, // UINT4
    4,  // FLOAT
    8,  // FLOAT2
    12, // FLOAT3
    16, // FLOAT4
    16, // MAT2
    24, // MAT2X3
    32, // MAT2X4
    24, // MAT3X2
    36, // MAT3
    48, // MAT3X4
    32, // MAT4X2
    48, // MAT4X3
    64, // MAT4
    4,  // SAMPLER1D
    4,  // SAMPLER1D_ARRAY
    4,  // SAMPLER2D
    4,  // SAMPLER2D_ARRAY
    4,  // SAMPLER3D
    4,  // SAMPLER_CUBE
};

uint FormatSurfaceSize(Format format, uint width, uint height, uint depth, uint mips) {

    uint size = 0;

    for (uint i = 0; i < mips; ++i) {
        size += FormatSize(format, width, height, depth);
        width = std::max(width >> 1, 1U);
        height = std::max(height >> 1, 1U);
    }

    return size;
}

void BlendTarget::reset() {
    blend = false;
    blendSrc = BlendFactor::ONE;
    blendDst = BlendFactor::ZERO;
    blendEq = BlendOp::ADD;
    blendSrcAlpha = BlendFactor::ONE;
    blendDstAlpha = BlendFactor::ZERO;
    blendAlphaEq = BlendOp::ADD;
    blendColorMask = ColorMask::ALL;
}

void RasterizerState::reset() {
    isDiscard = false;
    polygonMode = PolygonMode::FILL;
    shadeModel = ShadeModel::GOURAND;
    cullMode = CullMode::BACK;
    isFrontFaceCCW = true;
    depthBiasEnabled = false;
    depthBias = 0.0f;
    depthBiasClamp = 0.0f;
    depthBiasSlop = 0.0f;
    isDepthClip = true;
    isMultisample = false;
    lineWidth = 1.0f;
}

uint RasterizerState::getHash() const {
    uint hashVal = isDiscard;
    hashVal = hashVal * 31 + (uint)polygonMode;
    hashVal = hashVal * 31 + (uint)shadeModel;
    hashVal = hashVal * 31 + (uint)cullMode;
    hashVal = hashVal * 31 + isFrontFaceCCW;
    hashVal = hashVal * 31 + depthBiasEnabled;
    hashVal = hashVal * 31 + depthBias * 100;
    hashVal = hashVal * 31 + depthBiasClamp * 100;
    hashVal = hashVal * 31 + depthBiasSlop * 100;
    hashVal = hashVal * 31 + isDepthClip;
    hashVal = hashVal * 31 + isMultisample;
    hashVal = hashVal * 31 + lineWidth * 100;
    
    return hashVal;
}

void DepthStencilState::reset() {
    depthTest = true;
    depthWrite = true;
    depthFunc = ComparisonFunc::LESS;
    stencilTestFront = false;
    stencilFuncFront = ComparisonFunc::ALWAYS;
    stencilReadMaskFront = 0xffffffff;
    stencilWriteMaskFront = 0xffffffff;
    stencilFailOpFront = StencilOp::KEEP;
    stencilZFailOpFront = StencilOp::KEEP;
    stencilPassOpFront = StencilOp::KEEP;
    stencilRefFront = 1;
    stencilTestBack = false;
    stencilFuncBack = ComparisonFunc::ALWAYS;
    stencilReadMaskBack = 0xffffffff;
    stencilWriteMaskBack = 0xffffffff;
    stencilFailOpBack = StencilOp::KEEP;
    stencilZFailOpBack = StencilOp::KEEP;
    stencilPassOpBack = StencilOp::KEEP;
    stencilRefBack = 1;
}

uint DepthStencilState::getHash() const {
    uint hashVal = (uint)depthTest;
    hashVal = hashVal * 31 + (uint)depthWrite;
    hashVal = hashVal * 31 + (uint)depthFunc;
    hashVal = hashVal * 31 + (uint)stencilTestFront;
    hashVal = hashVal * 31 + (uint)stencilFuncFront;
    hashVal = hashVal * 31 + stencilReadMaskFront;
    hashVal = hashVal * 31 + stencilWriteMaskFront;
    hashVal = hashVal * 31 + (uint)stencilFailOpFront;
    hashVal = hashVal * 31 + (uint)stencilZFailOpFront;
    hashVal = hashVal * 31 + (uint)stencilPassOpFront;
    hashVal = hashVal * 31 + stencilRefFront;
    hashVal = hashVal * 31 + stencilTestBack;
    hashVal = hashVal * 31 + (uint)stencilFuncBack;
    hashVal = hashVal * 31 + stencilReadMaskBack;
    hashVal = hashVal * 31 + stencilWriteMaskBack;
    hashVal = hashVal * 31 + (uint)stencilFailOpBack;
    hashVal = hashVal * 31 + (uint)stencilZFailOpBack;
    hashVal = hashVal * 31 + (uint)stencilPassOpBack;
    hashVal = hashVal * 31 +stencilRefBack;
    
    return hashVal;
}

void BlendState::setTarget(uint index, const BlendTarget &target) {
    const auto size = targets.size();
    if (size <= index) targets.resize(size << 1);

    targets[index] = target;
}

void BlendState::reset() {
    isA2C = false;
    isIndepend = false;
    memset(&blendColor, 0, sizeof(blendColor));
    targets.clear();
    targets.emplace_back(BlendTarget());
}

uint BlendState::getHash() const {
    uint hashVal = (int)isA2C;
    hashVal = hashVal * 31 + (int)isIndepend;

    for (const auto &target : targets) {
        hashVal = hashVal * 31 + target.blend;
        hashVal = hashVal * 31 + (uint)target.blendSrc;
        hashVal = hashVal * 31 + (uint)target.blendDst;
        hashVal = hashVal * 31 + (uint)target.blendEq;
        hashVal = hashVal * 31 + (uint)target.blendSrcAlpha;
        hashVal = hashVal * 31 + (uint)target.blendDstAlpha;
        hashVal = hashVal * 31 + (uint)target.blendAlphaEq;
        hashVal = hashVal * 31 + (uint)target.blendColorMask;
    }

    hashVal = hashVal * 31 + blendColor.x * 100;
    hashVal = hashVal * 31 + blendColor.y * 100;
    hashVal = hashVal * 31 + blendColor.z * 100;
    hashVal = hashVal * 31 + blendColor.w * 100;
    
    return hashVal;
}

} // namespace gfx
} // namespace cc
