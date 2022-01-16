using ProtossLib;

public static class Program
{
    static void ShowGameUnitData(IGameObject go)
    {
        Console.WriteLine($"Name: {go.Name}, minerals: {go.Minerals}, build time: {go.BuildTime}");
    }

    static void StartingFromNexus()
    {
        var nexus = new Nexus();
        ShowGameUnitData((IGameObject)nexus);

        var probe = nexus.CreateUnit("Probe");
        ShowGameUnitData((IGameObject)probe);

        //_ = Marshal.ReleaseComObject(nexus);
        //_ = Marshal.ReleaseComObject(probe);
    }

    static void StartingFromProbe()
    {
        var probe = new Probe();
        ShowGameUnitData((IGameObject)probe);

        var nexus = probe.ConstructBuilding("Nexus");
        ShowGameUnitData((IGameObject)nexus);

        //_ = Marshal.ReleaseComObject(nexus);
        //_ = Marshal.ReleaseComObject(probe);
    }

    [STAThread]
    static void Main()
    {
        StartingFromProbe();
        StartingFromNexus();

        // force release of the COM objects
        GC.Collect();
    }
}
