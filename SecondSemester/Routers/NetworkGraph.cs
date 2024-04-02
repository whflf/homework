namespace Routers;

public class NetworkGraph
{
    private readonly List<List<Tuple<int, int>>> routersWithNeighbours = [];

    public NetworkGraph(string inputFile, string outputFile)
    {
        this.BuildGraph(inputFile);
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
    }

    private void ExtendRoutersList(int count)
    {
        for (var i = 0; i < count; ++i)
        {
            this.routersWithNeighbours.Add([]);
        }
    }

    private void FindMaxSpanningTree()
    {
        var spanningTree = new List<Tuple<int, int, double>>();

        var parents = new int[this.routersWithNeighbours.Count];
        Array.Fill(parents, -1);

        var alreadyInTree = new bool[this.routersWithNeighbours.Count];
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

            spanningTree.Add(new Tuple<int, int, double>(router, parents[router], bandwidth));
            alreadyInTree[router] = true;

            foreach (var neighbour in this.routersWithNeighbours[router])
            {
                if (alreadyInTree[neighbour.Item1] || bandwidth <= neighbour.Item2)
                {
                    continue;
                }

                parents[neighbour.Item1] = router;
                queue.Enqueue(neighbour.Item1, neighbour.Item2);
            }
        }
    }
}
