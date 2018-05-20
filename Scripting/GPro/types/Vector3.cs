public struct Vector3
{
    float x;
    float y;
    float z;
    
    public Vector3(float x, float y, float z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public static Vector3 operator *(Vector3 lhs, float rhs)
    {
        Vector3 result;
        result.x = lhs.x * rhs;
        result.y = lhs.y * rhs;
        result.z = lhs.z * rhs;
        return result;
    }
}