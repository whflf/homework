using Routers;

namespace Routers.tests;

public class RoutersTests
{
    [TestCase("TestValidCase.txt", "TestValidCaseResult.txt", "1: 2 (10), 3 (5)\n")]
    [TestCase("TestSingleRouterCase.txt", "TestSingleRouterCaseResult.txt", "1")]
    [TestCase(
        "TestLargeNetworkCase.txt",
        "TestLargeNetworkResult.txt",
        "1: 2 (10), 4 (8), 6 (6)\n2: 5 (7)\n5: 3 (9)\n")]
    [TestCase(
        "TestFullyConnectedCase.txt",
        "TestFullyConnectedCaseResult.txt",
        "1: 2 (10), 3 (10), 4 (10)\n")]
    [TestCase("TestValidCase.txt", "TestValidCaseResult.txt", "1: 2 (10), 3 (5)\n")]
    public void TestValidCase(string inputFile, string outputFile, string expected)
    {
        new NetworkGraph(inputFile).GenerateConfiguration(outputFile);
        Assert.That(File.ReadAllText(outputFile), Is.EqualTo(expected));
    }

    [TestCase("TestDisconnectedCase.txt", "TestDisconnectedCaseResult.txt")]
    [TestCase("TestDisconnectedSingleCase.txt", "TestDisconnectedSingleCaseResult.txt")]
    public void TestDisconnectedCase(string inputFile, string outputFile)
    {
        Assert.Throws<UnconnectedNetworkException>(
            () => new NetworkGraph(inputFile).GenerateConfiguration(outputFile));
    }
}