#pragma once

#include "D3D11.h"

enum CullState
{
    kCullStateNoCull = 1,
    kCullStateFrontCull = 2,
    kCullStateBackCull = 3
};


class RasterizerState
{
public:
    RasterizerState();
    ~RasterizerState();

    void SetCullState(CullState cs);

private:
    AutoRelease<ID3D11RasterizerState> m_cullBackRasterState;
    AutoRelease<ID3D11RasterizerState> m_noCullRasterState;
};
