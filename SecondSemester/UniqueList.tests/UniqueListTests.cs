namespace UniqueList.tests;

public class UniqueListTests
{
    private UniqueList<int> testUniqueList;
    private CommonList<int> list;

    [SetUp]
    public void Setup()
    {
        this.testUniqueList = new UniqueList<int>();
        for (var i = 9; i > 0; i -= 2)
        {
            this.testUniqueList.Add(i);
        }

        this.list = new CommonList<int>();
    }

    [Test]
    public void TestUnqieListAdding()
    {
        Assert.Throws<RepeatingValueException>(() => this.testUniqueList.Add(7));
    }

    [Test]
    public void TestUniqueListRemoving()
    {
        this.testUniqueList.Remove(1);
        this.testUniqueList.Remove(9);
        Assert.Throws<ElementNotFoundException>(() => this.testUniqueList.Remove(1));
    }

    [Test]
    public void TestUniqueListChangingValue()
    {
        this.testUniqueList.Change(11, 1);
        this.testUniqueList.Change(7, 2);
        Assert.Throws<RepeatingValueException>(() => this.testUniqueList.Change(1, 0));
    }

    [Test]
    public void TestCommonListAdding()
    {
        list.Add(1);
        list.Add(2);
        Assert.That(this.list.Count, Is.EqualTo(2));
    }

    [Test]
    public void TestCommonListRemoving()
    {
        this.list.Add(1);
        this.list.Add(2);
        this.list.Remove(1);
        Assert.That(this.list.Count, Is.EqualTo(1));
    }
}
