using System;

class TestSystem : ISystem
{
    public override void Initialize()
    {
        Console.WriteLine("Initialize");
    }

    // public override void EarlyTick()
    // {
    //     Console.WriteLine("EarlyTick");
    // }

    public override void VariableTick()
    {
        Console.WriteLine("VariableTick");
    }

    public override void LateVariableTick()
    {
        Console.WriteLine("LateTick");
    }

    public override void Deinitialize()
    {
        Console.WriteLine("Deinitialize");
    }
}