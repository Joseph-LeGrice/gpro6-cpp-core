using System;

class TestScript : MonoScript
{
    public override void Initialize()
    {
        Console.WriteLine("Initialize");
    }

    public override void EarlyTick()
    {
        Console.WriteLine("EarlyTick");
    }

    public override void Tick()
    {
        Console.WriteLine("Tick");
    }

    public override void LateTick()
    {
        Console.WriteLine("LateTick");
    }

    public override void Deinitialize()
    {
        Console.WriteLine("Deinitialize");
    }
}