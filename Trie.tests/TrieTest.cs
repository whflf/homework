using NUnit.Framework;
using System.Diagnostics;

[TestFixture]
public class Tests
{
    private string[] strings = new string[] { "apple", "app", "banana", "bat" };

    //private static Trie? myTrie = new Trie();

    [Test]
    public void TestAdding()
    {
        var myTrie = new Trie();

        foreach (string str in strings)
        {
            Assert.That(myTrie.Add(str), Is.True);
        }
    }

    [Test]
    public void TestAddingAndContaining()
    {
        var myTrie = new Trie();

        foreach (string str in strings)
        {
            myTrie.Add(str);
            Assert.That(myTrie.Contains(str), Is.True);
        }

        Assert.That(myTrie.Contains("orange"), Is.False);
    }

    [Test]
    public void TestAddingAndPrefixCounting()
    { 
        var myTrie = new Trie();

        foreach (string str in strings)
        {
            myTrie.Add(str);
        }

        Assert.That(myTrie.HowManyStartsWithPrefix("app"), Is.EqualTo(2));
        Assert.That(myTrie.HowManyStartsWithPrefix("bat"), Is.EqualTo(1));
        Assert.That(myTrie.HowManyStartsWithPrefix("cat"), Is.EqualTo(0));
    }

    [Test]
    public void TestRemoving()
    {
        var myTrie = new Trie();

        foreach (string str in strings)
        {
            myTrie.Add(str);
        }

        Assert.That(myTrie.Remove("app"), Is.True);
        Assert.That(myTrie.Remove("banana"), Is.True);
    }

    [Test]
    public void TestRemovingAndContaining()
    {
        var myTrie = new Trie();

        foreach (string str in strings)
        {
            myTrie.Add(str);
        }

        myTrie.Remove("app");
        myTrie.Remove("banana");

        Assert.That(myTrie.Contains("app"), Is.False);
        Assert.That(myTrie.Contains("banana"), Is.False);
        Assert.That(myTrie.Contains("apple"), Is.True);
    }

    [Test]
    public void TestRemovingAndPrefixCounting()
    { 
        var myTrie = new Trie();

        foreach (string str in strings)
        {
            myTrie.Add(str);
        }

        myTrie.Remove("app");
        myTrie.Remove("banana");

        Assert.That(myTrie.HowManyStartsWithPrefix("app"), Is.EqualTo(1));
        Assert.That(myTrie.HowManyStartsWithPrefix("ba"), Is.EqualTo(1));
    }

    [Test]
    public void TestEdgeCases()
    {
        var myTrie = new Trie();

        Assert.That(myTrie.Add(""), Is.True);
        Assert.That(myTrie.Contains(""), Is.True);

        Assert.That(myTrie.Add("apple"), Is.True);
        Assert.That(myTrie.Add("apple"), Is.False);
        Assert.That(myTrie.HowManyStartsWithPrefix("apple"), Is.EqualTo(1));
    }
}
