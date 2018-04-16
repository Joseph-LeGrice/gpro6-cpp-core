using System.IO;
using System.Reflection;

static class Application
{
    public static string ResourcePath
    {
        get 
        {
            string assemblyPath = Assembly.GetEntryAssembly().Location;
            return Path.Combine(assemblyPath, "Resources/");
        }
    }
}