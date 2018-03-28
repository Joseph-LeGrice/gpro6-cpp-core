
abstract class ISystem
{
    public virtual void Initialize() { }
    public virtual void EarlyTick() { }
    public virtual void Tick() { }
    public virtual void LateTick() { }
    public virtual void Deinitialize() { }
}