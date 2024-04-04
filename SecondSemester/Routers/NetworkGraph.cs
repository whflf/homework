namespace Routers;

public class NetworkGraph
{
    private readonly List<List<Tuple<int, int>>> routersWithNeighbours = [];

    public NetworkGraph(string inputFile)
    {
        this.BuildGraph(inputFile);
    }

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

            configurationEntry += $"{router.Key + 1}: ";
            for (var i = 0; i < router.Value.Count; ++i)
            {
                configurationEntry += $"{router.Value[i].Item1 + 1} ({-router.Value[i].Item2})";

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

        File.WriteAllText(outputFile, configurationEntry);
    }

    private void BuildGraph(string inputFile)
    {
        var fileContent = File.ReadAllText(inputFile);
        var routers = fileContent.Split('\n');

        foreach (var router in routers)
        {
            var numberAndNeighbours = router.Split(": ");
            var number = int.Parse(numberAndNeighbours[0]);
            var neighbours = numberAndNeighbours[1].Split(", ");

            this.ExtendRoutersList(number - this.routersWithNeighbours.Count);

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
