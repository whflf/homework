using Routers;

try
{
    var graph = new NetworkGraph("graph.txt");
    graph.GenerateConfiguration("newGraph.txt");
}
catch (UnconnectedNetworkException)
{
    Console.Error.WriteLine("ERROR: The router network is unconnected. Couldn't generate a configuration.");
}
catch (FormatException)
{
    Console.Error.WriteLine(
        "ERROR: The network topology format in the file is invalid. " +
        "Couldn't generate a configuration. Please check if the data are written correctly.");
}
catch (FileNotFoundException)
{
    Console.Error.WriteLine("ERROR: Couldn't find the file. Please make sure the path is correct.");
}
