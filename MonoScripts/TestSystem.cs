using System;

class TestSystem
{
    public TestSystem()
    {
        SystemInterface.RegisterSystem(this);
    }

    private void Initialize()
    {
        Console.WriteLine("Initialize");
    }

    // private override void EarlyTick()
    // {
    //     Console.WriteLine("EarlyTick");
    // }

    private void VariableTick()
    {
        Console.WriteLine("VariableTick");
    }

    private void LateVariableTick()
    {
        Console.WriteLine("LateTick");
    }

    private void Deinitialize()
    {
        Console.WriteLine("Deinitialize");
    }
}