#include "stdafx.h"
#include "Noise.h"

#include <math.h>

namespace Noise
{
    const int c_perlinHashMask = 255;
    const int c_perlinHash[] = {
        151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
        140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
        247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
        57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
        74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
        60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
        65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
        200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
        52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
        207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
        119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
        129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
        218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
        81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
        184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
        222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180,

        151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
        140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
        247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
        57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
        74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
        60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
        65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
        200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
        52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
        207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
        119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
        129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
        218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
        81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
        184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
        222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180
    };

    const int c_gradients1DMask = 1;
    const float c_gradients1D[] = { 1.0f, -1.0f };

    const int c_gradients2DMask = 7;
    const Vector2 c_gradients2D[] = {
        Vector2( 1.0f,  0.0f),
        Vector2(-1.0f,  0.0f),
        Vector2( 0.0f,  1.0f),
        Vector2( 0.0f, -1.0f),
        Vector2::Normalized(Vector2( 1.0f,  1.0f)),
        Vector2::Normalized(Vector2(-1.0f,  1.0f)),
        Vector2::Normalized(Vector2( 1.0f, -1.0f)),
        Vector2::Normalized(Vector2(-1.0f, -1.0f))
    };
    
    const Vector3 c_gradients3D[] = {
        Vector3( 1.0f, 1.0f, 0.0f),
        Vector3(-1.0f, 1.0f, 0.0f),
        Vector3( 1.0f,-1.0f, 0.0f),
        Vector3(-1.0f,-1.0f, 0.0f),
        Vector3( 1.0f, 0.0f, 1.0f),
        Vector3(-1.0f, 0.0f, 1.0f),
        Vector3( 1.0f, 0.0f,-1.0f),
        Vector3(-1.0f, 0.0f,-1.0f),
        Vector3( 0.0f, 1.0f, 1.0f),
        Vector3( 0.0f,-1.0f, 1.0f),
        Vector3( 0.0f, 1.0f,-1.0f),
        Vector3( 0.0f,-1.0f,-1.0f),

        Vector3( 1.0f, 1.0f, 0.0f),
        Vector3(-1.0f, 1.0f, 0.0f),
        Vector3( 0.0f,-1.0f, 1.0f),
        Vector3( 0.0f,-1.0f,-1.0f)
    };

    const int c_gradientsMask3D = 15;

    float Smooth(float t)
    {
        return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
    }

    float Dot(const Vector2& v, float a, float b)
    {
        return v.X * a + v.Y * b;
    }

    float Dot(Vector3 g, float x, float y, float z)
    {
        return g.X * x + g.Y * y + g.Z * z;
    }
    
    float Value1D(float point, float frequency)
    {
        point *= frequency;
        int i0 = MyMath::FloorToInt(point);
        float t = Smooth(point - i0);
        i0 &= c_perlinHashMask;

        int i1 = i0 + 1;
        int h0 = c_perlinHash[i0];
        int h1 = c_perlinHash[i1];

        return MyMath::Lerp(h0, h1, t) * 1.0f / c_perlinHashMask;
    }

    float Value2D(Vector2 point, float frequency)
    {
        point *= frequency;
        int ix0 = MyMath::FloorToInt(point.X);
        int iy0 = MyMath::FloorToInt(point.Y);
        float tx = Smooth(point.X - ix0);
        float ty = Smooth(point.Y - iy0);
        ix0 &= c_perlinHashMask;
        iy0 &= c_perlinHashMask;
        int ix1 = ix0 + 1;
        int iy1 = iy0 + 1;

        int h0 = c_perlinHash[ix0];
        int h1 = c_perlinHash[ix1];
        int h00 = c_perlinHash[h0 + iy0];
        int h10 = c_perlinHash[h1 + iy0];
        int h01 = c_perlinHash[h0 + iy1];
        int h11 = c_perlinHash[h1 + iy1];

        return MyMath::Lerp(
            MyMath::Lerp(h00, h10, tx),
            MyMath::Lerp(h01, h11, tx),
            ty) * 1.0f / c_perlinHashMask;
    }

    float Value3D(Vector3 point, float frequency)
    {
        point *= frequency;
        int ix0 = MyMath::FloorToInt(point.X);
        int iy0 = MyMath::FloorToInt(point.Y);
        int iz0 = MyMath::FloorToInt(point.Z);
        float tx = point.X - ix0;
        float ty = point.Y - iy0;
        float tz = point.Z - iz0;
        ix0 &= c_perlinHashMask;
        iy0 &= c_perlinHashMask;
        iz0 &= c_perlinHashMask;
        int ix1 = ix0 + 1;
        int iy1 = iy0 + 1;
        int iz1 = iz0 + 1;

        int h0 = c_perlinHash[ix0];
        int h1 = c_perlinHash[ix1];
        int h00 = c_perlinHash[h0 + iy0];
        int h10 = c_perlinHash[h1 + iy0];
        int h01 = c_perlinHash[h0 + iy1];
        int h11 = c_perlinHash[h1 + iy1];
        int h000 = c_perlinHash[h00 + iz0];
        int h100 = c_perlinHash[h10 + iz0];
        int h010 = c_perlinHash[h01 + iz0];
        int h110 = c_perlinHash[h11 + iz0];
        int h001 = c_perlinHash[h00 + iz1];
        int h101 = c_perlinHash[h10 + iz1];
        int h011 = c_perlinHash[h01 + iz1];
        int h111 = c_perlinHash[h11 + iz1];

        tx = Smooth(tx);
        ty = Smooth(ty);
        tz = Smooth(tz);
        return MyMath::Lerp(
            MyMath::Lerp(MyMath::Lerp(h000, h100, tx), MyMath::Lerp(h010, h110, tx), ty),
            MyMath::Lerp(MyMath::Lerp(h001, h101, tx), MyMath::Lerp(h011, h111, tx), ty),
            tz) * (1.0f / c_perlinHashMask);
    }

    float Perlin1D(float point, float frequency)
    {
        point *= frequency;
        int i0 = MyMath::FloorToInt(point);

        float t0 = point - i0;
        float t1 = t0 - 1.0f;
        
        i0 &= c_perlinHashMask;
        int i1 = i0 + 1;

        float g0 = c_gradients1D[c_perlinHash[i0] & c_gradients1DMask];
        float g1 = c_gradients1D[c_perlinHash[i1] & c_gradients1DMask];

        float v0 = g0 * t0;
        float v1 = g1 * t1;

        float t = Smooth(t0);
        return MyMath::Lerp(v0, v1, t) * 2.0f;
    }


    float Perlin2D(Vector2 point, float frequency)
    {
        point *= frequency;
        int ix0 = MyMath::FloorToInt(point.X);
        int iy0 = MyMath::FloorToInt(point.Y);

        float tx0 = point.X - ix0;
        float ty0 = point.Y - iy0;
        float tx1 = tx0 - 1.0f;
        float ty1 = ty0 - 1.0f;

        ix0 &= c_perlinHashMask;
        iy0 &= c_perlinHashMask;
        int ix1 = ix0 + 1;
        int iy1 = iy0 + 1;

        int h0 = c_perlinHash[ix0];
        int h1 = c_perlinHash[ix1];

        Vector2 g00 = c_gradients2D[c_perlinHash[h0 + iy0] & c_gradients2DMask];
        Vector2 g10 = c_gradients2D[c_perlinHash[h1 + iy0] & c_gradients2DMask];
        Vector2 g01 = c_gradients2D[c_perlinHash[h0 + iy1] & c_gradients2DMask];
        Vector2 g11 = c_gradients2D[c_perlinHash[h1 + iy1] & c_gradients2DMask];

        float v00 = Dot(g00, tx0, ty0);
        float v10 = Dot(g10, tx1, ty0);
        float v01 = Dot(g01, tx0, ty1);
        float v11 = Dot(g11, tx1, ty1);

        float tx = Smooth(tx0);
        float ty = Smooth(ty0);
        return MyMath::Lerp(
            MyMath::Lerp(v00, v10, tx),
            MyMath::Lerp(v01, v11, tx),
            ty) * sqrtf(2.0f);
    }

    float Perlin3D(Vector3 point, float frequency)
    {
        point *= frequency;
        int ix0 = MyMath::FloorToInt(point.X);
        int iy0 = MyMath::FloorToInt(point.Y);
        int iz0 = MyMath::FloorToInt(point.Z);
        float tx0 = point.X - ix0;
        float ty0 = point.Y - iy0;
        float tz0 = point.Z - iz0;
        float tx1 = tx0 - 1.0f;
        float ty1 = ty0 - 1.0f;
        float tz1 = tz0 - 1.0f;
        ix0 &= c_perlinHashMask;
        iy0 &= c_perlinHashMask;
        iz0 &= c_perlinHashMask;
        int ix1 = ix0 + 1;
        int iy1 = iy0 + 1;
        int iz1 = iz0 + 1;

        int h0 = c_perlinHash[ix0];
        int h1 = c_perlinHash[ix1];
        int h00 = c_perlinHash[h0 + iy0];
        int h10 = c_perlinHash[h1 + iy0];
        int h01 = c_perlinHash[h0 + iy1];
        int h11 = c_perlinHash[h1 + iy1];
        Vector3 g000 = c_gradients3D[c_perlinHash[h00 + iz0] & c_gradientsMask3D];
        Vector3 g100 = c_gradients3D[c_perlinHash[h10 + iz0] & c_gradientsMask3D];
        Vector3 g010 = c_gradients3D[c_perlinHash[h01 + iz0] & c_gradientsMask3D];
        Vector3 g110 = c_gradients3D[c_perlinHash[h11 + iz0] & c_gradientsMask3D];
        Vector3 g001 = c_gradients3D[c_perlinHash[h00 + iz1] & c_gradientsMask3D];
        Vector3 g101 = c_gradients3D[c_perlinHash[h10 + iz1] & c_gradientsMask3D];
        Vector3 g011 = c_gradients3D[c_perlinHash[h01 + iz1] & c_gradientsMask3D];
        Vector3 g111 = c_gradients3D[c_perlinHash[h11 + iz1] & c_gradientsMask3D];

        float v000 = Dot(g000, tx0, ty0, tz0);
        float v100 = Dot(g100, tx1, ty0, tz0);
        float v010 = Dot(g010, tx0, ty1, tz0);
        float v110 = Dot(g110, tx1, ty1, tz0);
        float v001 = Dot(g001, tx0, ty0, tz1);
        float v101 = Dot(g101, tx1, ty0, tz1);
        float v011 = Dot(g011, tx0, ty1, tz1);
        float v111 = Dot(g111, tx1, ty1, tz1);

        float tx = Smooth(tx0);
        float ty = Smooth(ty0);
        float tz = Smooth(tz0);
        return MyMath::Lerp(
            MyMath::Lerp(MyMath::Lerp(v000, v100, tx), MyMath::Lerp(v010, v110, tx), ty),
            MyMath::Lerp(MyMath::Lerp(v001, v101, tx), MyMath::Lerp(v011, v111, tx), ty),
            tz);
    }

    float Perlin3DFractal(Vector3 point, float baseFrequency, float octaves, float lacunarity, float persistence)
    {
        float frequency = baseFrequency;
        float sum = Perlin3D(point, frequency);
        float amplitude = 1.0f;
        float range = 1.0f;
        for (int i = 0; i < octaves; i++)
        {
            frequency *= lacunarity;
            amplitude *= persistence;
            range += amplitude;
            sum += Perlin3D(point, frequency) * amplitude;
        }
        return sum / range;
    }

}
