
public abstract class ITypedObject : System.Object
{
    private int m_instanceId = -1;
    
    public int InstanceID { get{ return m_instanceId; } }
}