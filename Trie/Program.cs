Trie myTrie = new Trie();

bool TestAdding()
{
    string[] stringArray = new string[4] { "he", "she", "his", "hers" };
    foreach (string str in stringArray)
    {
        if (!myTrie.Add(str))
        {
            return false;
        }
    }

    return !myTrie.Add("his");
}

bool TestContaining()
{
    return myTrie.Contains("hers") && !myTrie.Contains("hello");
}

bool TestRemoving()
{
    return myTrie.Remove("he") && !myTrie.Remove("hello");
}

bool TestCounting()
{
    return myTrie.HowManyStartsWithPrefix("h") == 2 && myTrie.HowManyStartsWithPrefix("o") == 0;
}

if (!TestAdding() && !TestContaining() && !TestRemoving() && !TestCounting())
{
    Console.WriteLine("~ Tests failed");
}
else
{
    myTrie = new Trie();
    MenuInterface.ProgramLoop(myTrie);
}
