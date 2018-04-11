using System.Runtime.CompilerServices;


abstract class ISystem
{
    public virtual void Initialize() { }
    public virtual void FixedTick() { }
    public virtual void EarlyVariableTick() { }
    public virtual void VariableTick() { }
    public virtual void LateVariableTick() { }
    public virtual void Deinitialize() { }

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    private extern static void RegisterSystem(ISystem newSystem);

    public ISystem()
    {
        RegisterSystem(this);
    }
}