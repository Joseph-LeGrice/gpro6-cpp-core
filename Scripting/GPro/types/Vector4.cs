public struct Vector4
{
    float x;
    float y;
    float z;
    float w;

    public Vector4(float x, float y, float z, float w)
    {
        this.x = x;
        this.y = y;
        this.z = z;
        this.w = w;
    }

    public static Vector4 operator *(Vector4 lhs, float rhs)
    {
        Vector4 result;
        result.x = lhs.x * rhs;
        result.y = lhs.y * rhs;
        result.z = lhs.z * rhs;
        result.w = lhs.w * rhs;
        return result;
    }
}