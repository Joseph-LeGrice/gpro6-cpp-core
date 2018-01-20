#pragma once

struct Matrix4x4;

class IDrawCommand
{
public:
    virtual void Draw(Matrix4x4 view, Matrix4x4 proj) = 0;
};
