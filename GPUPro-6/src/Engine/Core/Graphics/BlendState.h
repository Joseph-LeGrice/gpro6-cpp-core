#pragma once

#include <unordered_map>

struct ID3D11BlendState;
class GraphicsDevice;
enum D3D11_BLEND;
enum D3D11_BLEND_OP;

enum BlendFactor
{
    kBlendZero = 0,
    kBlendOne = 1,
    kBlendSrc = 2,
    kBlendSrcInv = 3,
    kBlendDest = 4,
    kBlendDestInv = 5
    //kBlendSrcAlphaSat = 11,
    //kBlendBlendFactor = 14,
    //kBlendBlendFactorInv = 15,
    //kBlendSrc1Color = 16,
    //kBlendSrc1ColorInv = 17,
    //kBlendSrc1Alpha = 18,
    //kBlendSrcOneAlphaInv = 19
};

enum BlendOperation
{
    kBlendOpAdd = 0,
    kBlendOpSubtract = 1,
    kBlendOpSubtractRev = 2,
    kBlendOpMin = 3,
    kBlendOpMax = 4
};

struct BlendStateDescriptor
{
    BOOL m_blendEnabled = FALSE;

    BlendFactor m_srcColor = kBlendOne;
    BlendFactor m_destColor = kBlendZero;
    BlendOperation m_colorBlendOp = kBlendOpAdd;
    
    BlendFactor m_srcAlpha = kBlendOne;
    BlendFactor m_destAlpha = kBlendZero;
    BlendOperation m_alphaBlendOp = kBlendOpAdd;

    UINT8 m_renderTargetWriteMask;

	BlendStateDescriptor();
	BlendStateDescriptor(BOOL enabled);
    BlendStateDescriptor(BlendFactor bf1, BlendFactor bf2, BlendOperation bop);
    BlendStateDescriptor(BlendFactor colBf1, BlendFactor coBf2, BlendOperation colBop,
        BlendFactor alphaBf1, BlendFactor alphaBf2, BlendOperation alphaBop);

    bool operator==(const BlendStateDescriptor& other) const;
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
	BlendState(GraphicsDevice& gfxDevice) : m_gfxDevice(gfxDevice) { }
    ~BlendState();

    void SetState(BlendStateDescriptor bsd);

private:
	GraphicsDevice& m_gfxDevice;
    std::unordered_map<BlendStateDescriptor, ManualRelease<ID3D11BlendState>> m_blendStates;
    
    ManualRelease<ID3D11BlendState>& GetBlendStateForDescriptor(BlendStateDescriptor& bsd);
	D3D11_BLEND BlendFactorToNative(BlendFactor bf, bool isAlpha);
	D3D11_BLEND_OP BlendOpToNative(BlendOperation bf);
};

