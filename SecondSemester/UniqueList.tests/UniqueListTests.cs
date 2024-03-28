namespace UniqueList.tests;

public class UniqueListTests
{
    [Test]
    public void TestAdding()
    {
        var testList = CreateTestList();

        Assert.Throws<RepeatingValueException>(() => testList.Add(7));
    }

    [Test]
    public void TestRemoving()
    {
        var testList = this.CreateTestList();

        testList.Remove(1);
        testList.Remove(9);
        Assert.Throws<ElementNotFoundException>(() => testList.Remove(1));
    }

    [Test]
    public void TestChangingValue()
    {
        var testList = this.CreateTestList();

        testList.Change(11, 1);
        Assert.Throws<RepeatingValueException>(() => testList.Change(1, 0));
    }

    private UniqueList<int> CreateTestList()
    {
        var testList = new UniqueList<int>();
        for (var i = 9; i > 0; i -= 2)
        {
            testList.Add(i);
        }

        return testList;
    }
}
