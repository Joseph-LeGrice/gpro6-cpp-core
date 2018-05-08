using System.IO;
using System.Reflection;

public static class Application
{
    public static string ResourcePath
    {
        get 
        {
            string assemblyPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            return Path.Combine(assemblyPath, "Resources").Replace("/", "\\\\");
        }
    }
}