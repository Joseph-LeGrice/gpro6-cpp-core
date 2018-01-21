#pragma once

#include "D3D11.h"
#include <unordered_map>

enum BlendFactor
{
    kBlendZero = 1,
    kBlendOne = 2,
    kBlendSrcColor = 3,
    kBlendSrcColorInv = 4,
    kBlendSrcAlpha = 5,
    kBlendSrcAlphaInv = 6,
    kBlendDestAlpha = 7,
    kBlendDestAlphaInv = 8,
    kBlendDestColor = 9,
    kBlendDestColorInv = 10,
    kBlendSrcAlphaSat = 11,
    kBlendBlendFactor = 14,
    kBlendBlendFactorInv = 15,
    kBlendSrc1Color = 16,
    kBlendSrc1ColorInv = 17,
    kBlendSrc1Alpha = 18,
    kBlendSrcOneAlphaInv = 19
};

enum BlendOp
{
    kBlendOpAdd = 1,
    kBlendOpSubtract = 2,
    kBlendOpSubtractRev = 3,
    kBlendOpMin = 4,
    kBlendOpMax = 5
};

struct BlendStateDescriptor
{
    BOOL m_blendEnabled = FALSE;

    BlendFactor m_srcColor = kBlendOne;
    BlendFactor m_destColor = kBlendZero;
    BlendOp m_colorBlendOp = kBlendOpAdd;
    
    BlendFactor m_srcAlpha = kBlendOne;
    BlendFactor m_destAlpha = kBlendZero;
    BlendOp m_alphaBlendOp = kBlendOpAdd;

    UINT8 m_renderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    BlendStateDescriptor(BOOL enabled) : m_blendEnabled(enabled) { }

    BlendStateDescriptor(BlendFactor bf1, BlendFactor bf2, BlendOp bop) : m_blendEnabled(TRUE),
        m_srcColor(bf1), m_destColor(bf2), m_colorBlendOp(bop),
        m_srcAlpha(bf1), m_destAlpha(bf2), m_alphaBlendOp(bop)
    { }

    BlendStateDescriptor(BlendFactor colBf1, BlendFactor coBf2, BlendOp colBop,
        BlendFactor alphaBf1, BlendFactor alphaBf2, BlendOp alphaBop) : m_blendEnabled(TRUE),
        m_srcColor(colBf1), m_destColor(coBf2), m_colorBlendOp(colBop),
        m_srcAlpha(alphaBf1), m_destAlpha(alphaBf2), m_alphaBlendOp(alphaBop)
    { }

    bool operator==(const BlendStateDescriptor& other) const
    {
        return m_blendEnabled == other.m_blendEnabled == true &&
            m_srcColor == other.m_srcColor &&
            m_destColor == other.m_destColor &&
            m_colorBlendOp == other.m_colorBlendOp &&
            m_srcAlpha == other.m_srcAlpha &&
            m_destAlpha == other.m_destAlpha &&
            m_alphaBlendOp == other.m_alphaBlendOp &&
            m_renderTargetWriteMask == other.m_renderTargetWriteMask;
    }
};

namespace std
{
    template<>
    struct hash<BlendStateDescriptor>
    {
        std::size_t operator()(const BlendStateDescriptor& bsd) const
        {
            using std::size_t;
            using std::hash;

            if (bsd.m_blendEnabled)
            {
                return hash<int>()(bsd.m_srcColor)
                    ^ (hash<int>()(bsd.m_destColor) << 1)
                    ^ (hash<int>()(bsd.m_colorBlendOp) << 2)
                    ^ (hash<int>()(bsd.m_srcAlpha) << 3)
                    ^ (hash<int>()(bsd.m_destAlpha) << 4)
                    ^ (hash<int>()(bsd.m_alphaBlendOp) << 5)
                    ^ (hash<int>()(bsd.m_renderTargetWriteMask) << 6);
            }
            else
            {
                return 0;
            }
        }
    };
}

class BlendState
{
public:
    BlendState();
    ~BlendState();

    void SetState(BlendStateDescriptor bsd);

private:
    std::unordered_map<BlendStateDescriptor, ManualRelease<ID3D11BlendState>> m_blendStates;
    
    ManualRelease<ID3D11BlendState>& GetBlendStateForDescriptor(BlendStateDescriptor& bsd);
};

