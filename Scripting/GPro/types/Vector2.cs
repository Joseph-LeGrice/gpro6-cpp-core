public struct Vector2
{
    float x;
    float y;

    public Vector2(float x, float y)
    {
        this.x = x;
        this.y = y;
    }

    public static Vector2 operator *(Vector2 lhs, float rhs)
    {
        Vector2 result;
        result.x = lhs.x * rhs;
        result.y = lhs.y * rhs;
        return result;
    }
}