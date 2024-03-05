using NUnit.Framework;
using System.Diagnostics;

[TestFixture]
public class Tests : PageTest
{
    private string[] strings;
    private Trie? myTrie;

    [Test]
    public void TestBasicFunctionality()
    { 
        myTrie = new Trie();
        strings = new string[] { "apple", "app", "banana", "bat" };

        foreach (string str in strings)
        {
            Assert.That(myTrie.Add(str), Is.True);
            Assert.That(myTrie.Contains(str), Is.True);
        }

        Assert.That(myTrie.Contains("orange"), Is.False);

        Assert.That(myTrie.HowManyStartsWithPrefix("app"), Is.EqualTo(2));
        Assert.That(myTrie.HowManyStartsWithPrefix("bat"), Is.EqualTo(1));
        Assert.That(myTrie.HowManyStartsWithPrefix("cat"), Is.EqualTo(0));

        Assert.That(myTrie.Remove("app"), Is.True);
        Assert.That(myTrie.Remove("banana"), Is.True);

        Assert.That(myTrie.Contains("app"), Is.False);
        Assert.That(myTrie.Contains("banana"), Is.False);
        Assert.That(myTrie.Contains("apple"), Is.True);

        Assert.That(myTrie.HowManyStartsWithPrefix("app"), Is.EqualTo(1));
        Assert.That(myTrie.HowManyStartsWithPrefix("ba"), Is.EqualTo(1));
    }

    [Test]
    public void LoadTest()
    {
        myTrie = new Trie(); 

        Stopwatch stopwatch = new Stopwatch();
        stopwatch.Start();
        for (int i = 0; i < 100000; ++i)
        {
            string str = string.Format($"string_{i}");
            Assert.That(myTrie.Add(str), Is.True);
        }
        stopwatch.Stop();

        bool result = stopwatch.Elapsed.Seconds < 5;
        Assert.That(result, Is.True);
    }

    [Test]
    public void TestEdgeCases()
    {
        myTrie = new Trie();

        Assert.That(myTrie.Add(""), Is.True);
        Assert.That(myTrie.Contains(""), Is.True);

        Assert.That(myTrie.Add("apple"), Is.True);
        Assert.That(myTrie.Add("apple"), Is.False);
        Assert.That(myTrie.HowManyStartsWithPrefix("apple"), Is.EqualTo(1));
    }
}
