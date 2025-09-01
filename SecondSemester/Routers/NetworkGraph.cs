// <copyright file="NetworkGraph.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace Routers;

/// <license>
/// https://github.com/whflf/homework/blob/main/LICENSE .
/// </license>
/// <summary>
/// Represents a network graph and provides methods to generate router configurations.
/// </summary>
/// <remarks>
/// This class can read a network topology from an input file, build a graph representation, and generate router configurations based on a maximum spanning tree algorithm.
/// </remarks>
public class NetworkGraph
{
    private readonly List<List<Tuple<int, int>>> routersWithNeighbours = [];

    /// <summary>
    /// Initializes a new instance of the <see cref="NetworkGraph"/> class with the specified input file.
    /// </summary>
    /// <param name="inputFile">The path to the input file containing the network topology.</param>
    public NetworkGraph(string inputFile)
    {
        this.BuildGraph(inputFile);
    }

    /// <summary>
    /// Generates router configurations based on the maximum spanning tree of the network
    /// graph and writes them to the specified output file.
    /// </summary>
    /// <param name="outputFile">The path to the output file where the router configurations will be written.</param>
    /// <exception cref="UnconnectedNetworkException">
    /// Thrown when the network graph is not connected (contains disconnected components).
    /// </exception>
    public void GenerateConfiguration(string outputFile)
    {
        var configuration = this.FindMaxSpanningTree();
        var configurationEntry = string.Empty;

        foreach (var router in configuration)
        {
            if (router.Key == -1)
            {
                continue;
            }

            var orderedRouter = router.Value.OrderBy(tuple => tuple.Item1).ToList();

            configurationEntry += $"{router.Key + 1}: ";
            for (var i = 0; i < router.Value.Count; ++i)
            {
                configurationEntry += $"{orderedRouter[i].Item1 + 1} ({-orderedRouter[i].Item2})";

                if (i != router.Value.Count - 1)
                {
                    configurationEntry += ", ";
                }
                else
                {
                    configurationEntry += '\n';
                }
            }
        }

        if (configurationEntry == string.Empty)
        {
            configurationEntry = "1";
        }

        File.WriteAllText(outputFile, configurationEntry);
    }

    private void BuildGraph(string inputFile)
    {
        var fileContent = File.ReadAllText(inputFile);
        var routers = fileContent.Split('\n');

        foreach (var router in routers)
        {
            var numberAndNeighbours = router.Split(": ");
            var number = int.Parse(numberAndNeighbours[0].Replace(":", string.Empty));

            this.ExtendRoutersList(number - this.routersWithNeighbours.Count);

            string[] neighbours;
            try
            {
                neighbours = numberAndNeighbours[1].Split(", ");
            }
            catch (IndexOutOfRangeException)
            {
                continue;
            }

            if (neighbours[0] == string.Empty)
            {
                continue;
            }

            foreach (var neighbour in neighbours)
            {
                var current =
                    neighbour.Replace("(", string.Empty).Replace(")", string.Empty);
                var currentInfo = current.Split();

                int neighbourNumber = int.Parse(currentInfo[0]), neighbourBandwidth = int.Parse(currentInfo[1]);
                this.ExtendRoutersList(neighbourNumber - this.routersWithNeighbours.Count);

                this.routersWithNeighbours[number - 1].Add(
                    new Tuple<int, int>(neighbourNumber - 1, -neighbourBandwidth));
                this.routersWithNeighbours[neighbourNumber - 1].Add(
                    new Tuple<int, int>(number - 1, -neighbourBandwidth));
            }
        }

        if (this.routersWithNeighbours.Contains([]))
        {
            throw new UnconnectedNetworkException();
        }
    }

    private void ExtendRoutersList(int count)
    {
        for (var i = 0; i < count; ++i)
        {
            this.routersWithNeighbours.Add([]);
        }
    }

    private Dictionary<int, List<Tuple<int, double>>> FindMaxSpanningTree()
    {
        var spanningTree = new Dictionary<int, List<Tuple<int, double>>>();

        var parents = new int[this.routersWithNeighbours.Count];
        Array.Fill(parents, -1);

        var alreadyInTree = new bool[this.routersWithNeighbours.Count];
        var bandwidthes = new int[this.routersWithNeighbours.Count];
        var queue = new PriorityQueue<int, double>();

        for (var i = 0; i < this.routersWithNeighbours.Count; ++i)
        {
            if (i == 0)
            {
                queue.Enqueue(i, double.NegativeInfinity);
            }
            else
            {
                queue.Enqueue(i, 0);
            }
        }

        while (queue.TryDequeue(out var router, out var bandwidth))
        {
            if (parents[router] == -1 && router != 0)
            {
                throw new UnconnectedNetworkException();
            }

            if (alreadyInTree[router])
            {
                continue;
            }

            if (!spanningTree.ContainsKey(parents[router]))
            {
                spanningTree.Add(parents[router], [new Tuple<int, double>(router, bandwidth)]);
            }
            else
            {
                spanningTree[parents[router]].Add(new Tuple<int, double>(router, bandwidth));
            }

            alreadyInTree[router] = true;

            foreach (var neighbour in this.routersWithNeighbours[router])
            {
                if (alreadyInTree[neighbour.Item1] || bandwidthes[neighbour.Item1] <= neighbour.Item2)
                {
                    continue;
                }

                parents[neighbour.Item1] = router;
                bandwidthes[neighbour.Item1] = neighbour.Item2;
                queue.Enqueue(neighbour.Item1, neighbour.Item2);
            }
        }

        return spanningTree;
    }
}
