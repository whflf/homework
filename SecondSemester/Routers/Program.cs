using Routers;

try
{
    var graph = new NetworkGraph("graph.txt");
    graph.GenerateConfiguration("newGraph.txt");
}
catch (UnconnectedNetworkException e)
{
    var errorWriter = Console.Error;
    errorWriter.WriteLine("ERROR: The router network is unconnected. Couldn't generate a configuration.");
}
