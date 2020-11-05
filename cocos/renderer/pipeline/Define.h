#pragma once

#include "../core/CoreStd.h"
#include "base/Value.h"

namespace cc {
namespace pipeline {

class RenderStage;
class RenderFlow;
struct SubModelView;
struct Light;
struct ModelView;
struct AABB;
struct Frustum;

// The actual uniform vectors used is JointUniformCapacity * 3.
// We think this is a reasonable default capacity considering MAX_VERTEX_UNIFORM_VECTORS in WebGL spec is just 128.
// Skinning models with number of bones more than this capacity will be automatically switched to texture skinning.
// But still, you can tweak this for your own need by changing the number below
// and the JOINT_UNIFORM_CAPACITY macro in cc-skinning shader header.
#define JOINT_UNIFORM_CAPACITY 30

struct CC_DLL RenderObject {
    float depth = 0;
    const ModelView *model = nullptr;
};
typedef vector<struct RenderObject> RenderObjectList;

struct CC_DLL RenderTargetInfo {
    uint width = 0;
    uint height = 0;
};

struct CC_DLL RenderPass {
    uint hash = 0;
    float depth = 0;
    uint shaderID = 0;
    uint passIndex = 0;
    const SubModelView *subModel = nullptr;
};
typedef vector<RenderPass> RenderPassList;

typedef gfx::ColorAttachment ColorDesc;
typedef vector<ColorDesc> ColorDescList;

typedef gfx::DepthStencilAttachment DepthStencilDesc;

struct CC_DLL RenderPassDesc {
    uint index = 0;
    ColorDescList colorAttachments;
    DepthStencilDesc depthStencilAttachment;
};
typedef vector<RenderPassDesc> RenderPassDescList;

struct CC_DLL RenderTextureDesc {
    String name;
    gfx::TextureType type = gfx::TextureType::TEX2D;
    gfx::TextureUsage usage = gfx::TextureUsage::COLOR_ATTACHMENT;
    gfx::Format format = gfx::Format::UNKNOWN;
    int width = -1;
    int height = -1;
};
typedef vector<RenderTextureDesc> RenderTextureDescList;

struct CC_DLL FrameBufferDesc {
    String name;
    uint renderPass = 0;
    vector<String> colorTextures;
    String depthStencilTexture;
};
typedef vector<FrameBufferDesc> FrameBufferDescList;

enum class RenderFlowType : uint8_t {
    SCENE,
    POSTPROCESS,
    UI,
};

typedef vector<RenderStage *> RenderStageList;
typedef vector<RenderFlow *> RenderFlowList;
typedef vector<Light *> LightList;
typedef vector<uint> UintList;

enum class CC_DLL RenderPassStage {
    DEFAULT = 100,
    UI = 200,
};

struct CC_DLL InternalBindingDesc {
    gfx::DescriptorType type;
    gfx::UniformBlock blockInfo;
    gfx::UniformSampler samplerInfo;
    Value defaultValue;
};

struct CC_DLL InternalBindingInst : public InternalBindingDesc {
    gfx::Buffer *buffer = nullptr;
    gfx::Sampler *sampler = nullptr;
    gfx::Texture *texture = nullptr;
};

struct CC_DLL RenderQueueCreateInfo {
    bool isTransparent = false;
    uint phases = 0;
    std::function<bool(const RenderPass &a, const RenderPass &b)> sortFunc;
};

enum class CC_DLL RenderPriority {
    MIN = 0,
    MAX = 0xff,
    DEFAULT = 0x80,
};

enum class CC_DLL RenderQueueSortMode {
    FRONT_TO_BACK,
    BACK_TO_FRONT,
};

struct CC_DLL RenderQueueDesc {
    bool isTransparent = false;
    RenderQueueSortMode sortMode = RenderQueueSortMode::FRONT_TO_BACK;
    StringArray stages;
};
typedef vector<RenderQueueDesc> RenderQueueDescList;

class CC_DLL PassPhase {
public:
    static uint getPhaseID(const String &phaseName) {
        if (phases.find(phaseName) == phases.end()) {
            phases[phaseName] = 1 << phaseNum++;
        }
        return phases[phaseName];
    }

private:
    static map<String, uint> phases;
    static uint phaseNum;
};

CC_INLINE bool opaqueCompareFn(const RenderPass &a, const RenderPass &b) {
    if (a.hash != b.hash)
        return a.hash < b.hash;
    else if (math::IsNotEqualF(a.depth, b.depth))
        return a.depth < b.depth;
    else
        return a.shaderID < b.shaderID;
}

CC_INLINE bool transparentCompareFn(const RenderPass &a, const RenderPass &b) {
    if (a.hash != b.hash)
        return a.hash < b.hash;
    else if (math::IsNotEqualF(a.depth, b.depth))
        return b.depth < a.depth;
    else
        return a.shaderID < b.shaderID;
}

enum class CC_DLL PipelineGlobalBindings {
    UBO_GLOBAL,
    UBO_SHADOW,

    SAMPLER_SHADOWMAP,
    SAMPLER_ENVIRONMENT, // don't put this as the first sampler binding due to Mac GL driver issues: cubemap at texture unit 0 causes rendering issues

    COUNT,
};

enum class CC_DLL ModelLocalBindings {
    UBO_LOCAL,
    UBO_FORWARD_LIGHTS,
    UBO_SKINNING_ANIMATION,
    UBO_SKINNING_TEXTURE,
    UBO_MORPH,

    SAMPLER_JOINTS,
    SAMPLER_MORPH_POSITION,
    SAMPLER_MORPH_NORMAL,
    SAMPLER_MORPH_TANGENT,
    SAMPLER_LIGHTMAP,
    SAMPLER_SPRITE,

    COUNT,
};

struct CC_DLL BlockInfo {
    gfx::UniformBlock layout;
    gfx::DescriptorSetLayoutBinding bindings;
};
struct CC_DLL SamplerInfo {
    gfx::UniformSampler layout;
    gfx::DescriptorSetLayoutBinding bindings;
};

struct CC_DLL UBOLocalBatched {
    static constexpr uint BATCHING_COUNT = 10;
    static constexpr uint MAT_WORLDS_OFFSET = 0;
    static constexpr uint COUNT = 16 * UBOLocalBatched::BATCHING_COUNT;
    static constexpr uint SIZE = UBOLocalBatched::COUNT * 4;

    static const BlockInfo BLOCK;
};

struct CC_DLL UBOLocal {
    static constexpr uint MAT_WORLD_OFFSET = 0;
    static constexpr uint MAT_WORLD_IT_OFFSET = UBOLocal::MAT_WORLD_OFFSET + 16;
    static constexpr uint LIGHTINGMAP_UVPARAM = UBOLocal::MAT_WORLD_IT_OFFSET + 16;
    static constexpr uint COUNT = UBOLocal::LIGHTINGMAP_UVPARAM + 4;
    static constexpr uint SIZE = UBOLocal::COUNT * 4;

    static const BlockInfo BLOCK;
};

struct CC_DLL UBOForwardLight {
    static constexpr uint LIGHTS_PER_PASS = 1;
    static constexpr uint LIGHT_POS_OFFSET = 0;
    static constexpr uint LIGHT_COLOR_OFFSET = UBOForwardLight::LIGHT_POS_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint LIGHT_SIZE_RANGE_ANGLE_OFFSET = UBOForwardLight::LIGHT_COLOR_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint LIGHT_DIR_OFFSET = UBOForwardLight::LIGHT_SIZE_RANGE_ANGLE_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint COUNT = UBOForwardLight::LIGHT_DIR_OFFSET + UBOForwardLight::LIGHTS_PER_PASS * 4;
    static constexpr uint SIZE = UBOForwardLight::COUNT * 4;

    static const BlockInfo BLOCK;
};

struct CC_DLL UBOSkinningTexture {
    static constexpr uint JOINTS_TEXTURE_INFO_OFFSET = 0;
    static constexpr uint COUNT = UBOSkinningTexture::JOINTS_TEXTURE_INFO_OFFSET + 4;
    static constexpr uint SIZE = UBOSkinningTexture::COUNT * 4;

    static const BlockInfo BLOCK;
};

struct CC_DLL UBOSkinningAnimation {
    static constexpr uint JOINTS_ANIM_INFO_OFFSET = 0;
    static constexpr uint COUNT = UBOSkinningAnimation::JOINTS_ANIM_INFO_OFFSET + 4;
    static constexpr uint SIZE = UBOSkinningAnimation::COUNT * 4;

    static const BlockInfo BLOCK;
};

struct CC_DLL UBOSkinning {
    static constexpr uint JOINTS_OFFSET = 0;
    static constexpr uint COUNT = UBOSkinning::JOINTS_OFFSET + JOINT_UNIFORM_CAPACITY * 12;
    static constexpr uint SIZE = UBOSkinning::COUNT * 4;

    static const BlockInfo BLOCK;
};

struct CC_DLL UBOMorph {
    static const uint MAX_MORPH_TARGET_COUNT;
    static const uint OFFSET_OF_WEIGHTS;
    static const uint OFFSET_OF_DISPLACEMENT_TEXTURE_WIDTH;
    static const uint OFFSET_OF_DISPLACEMENT_TEXTURE_HEIGHT;
    static const uint COUNT_BASE_4_BYTES;
    static const uint SIZE;

    static const BlockInfo BLOCK;
};

enum class CC_DLL ForwardStagePriority {
    FORWARD = 10,
    UI = 20
};

enum class CC_DLL ForwardFlowPriority {
    SHADOW = 0,
    FORWARD = 1,
    UI = 10,
};

enum class CC_DLL RenderFlowTag {
    SCENE,
    POSTPROCESS,
    UI,
};

struct CC_DLL UBOGlobal : public Object {
    static constexpr uint TIME_OFFSET = 0;
    static constexpr uint SCREEN_SIZE_OFFSET = UBOGlobal::TIME_OFFSET + 4;
    static constexpr uint SCREEN_SCALE_OFFSET = UBOGlobal::SCREEN_SIZE_OFFSET + 4;
    static constexpr uint NATIVE_SIZE_OFFSET = UBOGlobal::SCREEN_SCALE_OFFSET + 4;
    static constexpr uint MAT_VIEW_OFFSET = UBOGlobal::NATIVE_SIZE_OFFSET + 4;
    static constexpr uint MAT_VIEW_INV_OFFSET = UBOGlobal::MAT_VIEW_OFFSET + 16;
    static constexpr uint MAT_PROJ_OFFSET = UBOGlobal::MAT_VIEW_INV_OFFSET + 16;
    static constexpr uint MAT_PROJ_INV_OFFSET = UBOGlobal::MAT_PROJ_OFFSET + 16;
    static constexpr uint MAT_VIEW_PROJ_OFFSET = UBOGlobal::MAT_PROJ_INV_OFFSET + 16;
    static constexpr uint MAT_VIEW_PROJ_INV_OFFSET = UBOGlobal::MAT_VIEW_PROJ_OFFSET + 16;
    static constexpr uint CAMERA_POS_OFFSET = UBOGlobal::MAT_VIEW_PROJ_INV_OFFSET + 16;
    static constexpr uint EXPOSURE_OFFSET = UBOGlobal::CAMERA_POS_OFFSET + 4;
    static constexpr uint MAIN_LIT_DIR_OFFSET = UBOGlobal::EXPOSURE_OFFSET + 4;
    static constexpr uint MAIN_LIT_COLOR_OFFSET = UBOGlobal::MAIN_LIT_DIR_OFFSET + 4;
    static constexpr uint AMBIENT_SKY_OFFSET = UBOGlobal::MAIN_LIT_COLOR_OFFSET + 4;
    static constexpr uint AMBIENT_GROUND_OFFSET = UBOGlobal::AMBIENT_SKY_OFFSET + 4;
    static constexpr uint GLOBAL_FOG_COLOR_OFFSET = UBOGlobal::AMBIENT_GROUND_OFFSET + 4;
    static constexpr uint GLOBAL_FOG_BASE_OFFSET = UBOGlobal::GLOBAL_FOG_COLOR_OFFSET + 4;
    static constexpr uint GLOBAL_FOG_ADD_OFFSET = UBOGlobal::GLOBAL_FOG_BASE_OFFSET + 4;
    static constexpr uint COUNT = UBOGlobal::GLOBAL_FOG_ADD_OFFSET + 4;
    static constexpr uint SIZE = UBOGlobal::COUNT * 4;

    static const BlockInfo BLOCK;
};

struct CC_DLL UBOShadow : public Object {
    static constexpr uint MAT_LIGHT_PLANE_PROJ_OFFSET = 0;
    static constexpr uint MAT_LIGHT_VIEW_PROJ_OFFSET = UBOShadow::MAT_LIGHT_PLANE_PROJ_OFFSET + 16;
    static constexpr uint SHADOW_COLOR_OFFSET = UBOShadow::MAT_LIGHT_VIEW_PROJ_OFFSET + 16;
    static constexpr uint SHADOW_INFO_OFFSET = UBOShadow::SHADOW_COLOR_OFFSET + 4;
    static constexpr uint COUNT = UBOShadow::SHADOW_INFO_OFFSET + 4;
    static constexpr uint SIZE = UBOShadow::COUNT * 4;

    static const BlockInfo BLOCK;
};

class CC_DLL SamplerLib : public Object {
public:
    gfx::Sampler *getSampler(uint hash);
};

struct CC_DLL DescriptorSetLayoutInfos : public gfx::DescriptorSetLayoutInfo {
    union record {
        unordered_map<String, BlockInfo> blocks;
        unordered_map<String, SamplerInfo> samplers;
    };
};

uint genSamplerHash(const gfx::SamplerInfo &);
gfx::Sampler *getSampler(uint hash);

enum class LayerList : uint {
    NONE = 0,
    IGNORE_RAYCAST = (1 << 20),
    GIZMOS = (1 << 21),
    EDITOR = (1 << 22),
    UI_3D = (1 << 23),
    SCENE_GIZMO = (1 << 24),
    UI_2D = (1 << 25),

    PROFILER = (1 << 28),
    DEFAULT = (1 << 30),
    ALL = 0xffffffff,
};

//TODO
const uint CAMERA_DEFAULT_MASK = ~static_cast<uint>(LayerList::UI_2D) & ~static_cast<uint>(LayerList::PROFILER);
//constexpr CAMERA_DEFAULT_MASK = Layers.makeMaskExclude([Layers.BitMask.UI_2D, Layers.BitMask.GIZMOS, Layers.BitMask.EDITOR,
//                                                           Layers.BitMask.SCENE_GIZMO, Layers.BitMask.PROFILER]);

uint nextPow2(uint val);
enum class CC_DLL SetIndex {
    GLOBAL,
    MATERIAL,
    LOCAL,
};
extern CC_DLL uint GLOBAL_SET;
extern CC_DLL uint MATERIAL_SET;
extern CC_DLL uint LOCAL_SET;

extern CC_DLL uint SKYBOX_FLAG;
extern CC_DLL DescriptorSetLayoutInfos globalDescriptorSetLayout;
extern CC_DLL DescriptorSetLayoutInfos localDescriptorSetLayout;
extern CC_DLL const SamplerInfo UNIFORM_SHADOWMAP;
extern CC_DLL const SamplerInfo UNIFORM_ENVIRONMENT;
extern CC_DLL const SamplerInfo UniformJointTexture;
extern CC_DLL const SamplerInfo UniformPositionMorphTexture;
extern CC_DLL const SamplerInfo UniformNormalMorphTexture;
extern CC_DLL const SamplerInfo UniformTangentMorphTexture;
extern CC_DLL const SamplerInfo UniformLightingMapSampler;
extern CC_DLL const SamplerInfo UniformSpriteSampler;
} // namespace pipeline
} // namespace cc
