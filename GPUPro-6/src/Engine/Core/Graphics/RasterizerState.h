#pragma once

#include "D3D11.h"
#include <unordered_map>

enum CullState
{
    kCullStateNoCull = 1,
    kCullStateFrontCull = 2,
    kCullStateBackCull = 3
};

enum FillMode
{
    kFillModeSolid = 1,
    kFillModeWireframe = 2
};

struct RasterizerStateDescriptor
{
    CullState m_cullState = kCullStateBackCull;
    FillMode m_fillMode = kFillModeSolid;
    bool m_enableMSAA = false;

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
    RasterizerState();
    ~RasterizerState();

    void SetState(RasterizerStateDescriptor rsd);

private:
    std::unordered_map<RasterizerStateDescriptor, ManualRelease<ID3D11RasterizerState>> m_rasterStates;

    ManualRelease<ID3D11RasterizerState>& RasterizerState::GetStateForDescriptor(RasterizerStateDescriptor rsd);
};
