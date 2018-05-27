using System;

public class TestSystem : ITypedObject
{
    public TestSystem()
    {
        ScriptedSystemInterface.RegisterSystemInstance(this);
    }

    private void Initialize()
    {
        Logging.LogMessage("Initialized a system");
    }

    // private override void EarlyTick()
    // {
    //     Logging.LogMessage("EarlyTick");
    // }

    // private void VariableTick()
    // {
    //     Logging.LogMessage("VariableTick");
    // }

    // private void LateVariableTick()
    // {
    //     Logging.LogMessage("LateTick");
    // }

    private void Deinitialize()
    {
        Logging.LogMessage("Deinitialized a system");
    }
}