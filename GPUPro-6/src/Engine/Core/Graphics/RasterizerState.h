#pragma once

#include <unordered_map>

class GraphicsDevice;
struct ID3D11RasterizerState;

enum CullState
{
    kCullStateNoCull = 0,
    kCullStateFrontCull = 1,
    kCullStateBackCull = 2
};

enum FillMode
{
    kFillModeSolid = 0,
    kFillModeWireframe = 1
};

struct RasterizerStateDescriptor
{
    CullState m_cullState = kCullStateBackCull;
    FillMode m_fillMode = kFillModeSolid;
    bool m_enableMSAA = false;

	RasterizerStateDescriptor() : m_cullState(kCullStateBackCull),
		m_fillMode(kFillModeSolid),
		m_enableMSAA(false) { }

    RasterizerStateDescriptor(CullState cs, FillMode fm, bool msaa) :
        m_cullState(cs), m_fillMode(fm), m_enableMSAA(msaa) { }

    bool operator==(const RasterizerStateDescriptor& other) const
    {
        return m_cullState == other.m_cullState &&
            m_fillMode == other.m_fillMode &&
            m_enableMSAA == other.m_enableMSAA;
    }
};

namespace std
{
    template<>
    struct hash<RasterizerStateDescriptor>
    {
        std::size_t operator()(const RasterizerStateDescriptor& obj) const
        {
            using std::size_t;
            using std::hash;

            return ((hash<bool>()(obj.m_enableMSAA)
                ^ (hash<int>()(obj.m_cullState) << 1)) >> 1)
                ^ (hash<int>()(obj.m_fillMode) << 1);
        }
    };
}

class RasterizerState
{
public:
	RasterizerState(GraphicsDevice& gfxDevice) : m_gfxDevice(gfxDevice) { }
    ~RasterizerState();

    void SetState(RasterizerStateDescriptor rsd);

private:
	GraphicsDevice& m_gfxDevice;
    std::unordered_map<RasterizerStateDescriptor, ManualRelease<ID3D11RasterizerState>> m_rasterStates;

    ManualRelease<ID3D11RasterizerState>& RasterizerState::GetStateForDescriptor(RasterizerStateDescriptor rsd);
};
