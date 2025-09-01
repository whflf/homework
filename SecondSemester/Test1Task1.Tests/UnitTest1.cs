using Test1Task1;

namespace Test1Task1.Tests;

public class Test1Task1Tests
{
    [Test]
    public void TestCaseZeroVector()
    {
        var vector = new SparseVector(new List<Tuple<int, int>>(), 500);
        Assert.That(vector.IsZero, Is.EqualTo(true));
    }

    [Test]
    public void TestCaseAdding()
    {
        var vectorOne = new SparseVector([new Tuple<int, int>(3, 6), new Tuple<int, int>(5, 8)], 500);
        var vectorTwo = new SparseVector([new Tuple<int, int>(3, 1), new Tuple<int, int>(5, 1),
        new Tuple<int, int>(50, 3)], 500);

        var result = new SparseVector([
            new Tuple<int, int>(3, 7), new Tuple<int, int>(5, 9),
            new Tuple<int, int>(50, 3)
        ], 500);

        foreach (var item in vectorOne.Add(vectorTwo).vector)
        {
            Assert.That(item.Value, Is.EqualTo(result.vector[item.Key]));
        }
    }
    
    [Test]
    public void TestCaseSubtracting()
    {
        var vectorOne = new SparseVector([new Tuple<int, int>(3, 6), new Tuple<int, int>(5, 8)], 500);
        var vectorTwo = new SparseVector([new Tuple<int, int>(3, 1), new Tuple<int, int>(5, 1),
            new Tuple<int, int>(50, 3)], 500);

        var result = new SparseVector([
            new Tuple<int, int>(3, 5), new Tuple<int, int>(5, 7),
            new Tuple<int, int>(50, 3)
        ], 500);

        foreach (var item in vectorOne.Subtract(vectorTwo).vector)
        {
            Assert.That(item.Value, Is.EqualTo(result.vector[item.Key]));
        }
    }
    
    [Test]
    public void TestCaseMultiplying()
    {
        var vectorOne = new SparseVector([new Tuple<int, int>(3, 6), new Tuple<int, int>(5, 8)], 500);
        var vectorTwo = new SparseVector([new Tuple<int, int>(3, 1), new Tuple<int, int>(5, 1),
            new Tuple<int, int>(50, 3)], 500);

        Assert.That(vectorOne.Multiply(vectorTwo), Is.EqualTo(14));
    }
}