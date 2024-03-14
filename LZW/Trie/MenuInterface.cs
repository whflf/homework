using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

internal class MenuInterface
{
    private enum MenuOption : int
    {
        exitProgram,
        addStringToTrie,
        checkForStringInTrie,
        removeStringFromTrie,
        checkForPrefixInTrie
    }

    private enum TrieChangingOption
    {
        addString,
        removeString
    }

    private static void Wait()
    {
        Console.WriteLine("Press enter to continue...");
        while (Console.ReadKey().Key != ConsoleKey.Enter);
    }

    private static void ChoiceChangeTrieContent(Trie trie, TrieChangingOption option)
    {
        Console.WriteLine("Enter a string:");
        string? element = Console.ReadLine();

        bool trieIsChanged = option == TrieChangingOption.addString ? trie.Add(element) : trie.Remove(element);
        if (trieIsChanged)
        {
            string output = string.Format("{0}", option == TrieChangingOption.addString ? "added to" : "removed from");
            Console.WriteLine($"String \"{element}\" was successfully {output} the trie");
        }
        else
        {
            string output = string.Format("{0}", option == TrieChangingOption.addString ? "already" : "not");
            Console.WriteLine($"String \"{element}\" is {output} in the trie");
        }
    }

    public static void ProgramLoop(Trie trie)
    {
        string[] menuOptionNames =
        {
            "Exit program",
            "Add new string to the trie",
            "Check for a string in the trie",
            "Remove a string from the trie",
            "Check how many strings stars with the prefix in the trie"
        };

        while (true)
        {
            Console.Clear();

            Console.WriteLine("Enter an operation code to continue:");
            for (int i = 0; i < menuOptionNames.Length; ++i)
            {
                Console.WriteLine($"  {i} - {menuOptionNames[i]}");
            }

            Console.Write("> ");
            int input;
            try
            {
                input = Convert.ToInt32(Console.ReadLine());
            }
            catch
            {
                Console.WriteLine("Bad input. Please enter a valid operation code");
                Wait();
                continue;
            }

            switch (input)
            {
                case (int)MenuOption.exitProgram:
                    Console.WriteLine("Goodbye!");
                    Wait();
                    return;

                case (int)MenuOption.addStringToTrie:
                    ChoiceChangeTrieContent(trie, TrieChangingOption.addString);
                    break;

                case (int)MenuOption.checkForStringInTrie:
                    Console.WriteLine("Enter a string:");
                    Console.WriteLine("The trie {0} that string", 
                        trie.Contains(Console.ReadLine() ?? string.Empty) ? "contains" : "doesn't contain");
                    break;

                case (int)MenuOption.removeStringFromTrie:
                    ChoiceChangeTrieContent(trie, TrieChangingOption.removeString);
                    break;

                case (int)MenuOption.checkForPrefixInTrie:
                    Console.WriteLine("Enter the prefix:");
                    int stringsCount = trie.HowManyStartsWithPrefix(Console.ReadLine() ?? string.Empty);
                    string[] ends = { string.Format("{0}", stringsCount == 1 ? "" : "s"),
                                    string.Format("{0}", stringsCount == 1 ? "s" : "") };

                    Console.WriteLine($"{stringsCount} string{ends[0]} in the trie start{ends[1]} with that prefix");
                    break;
            }

            Wait();
        }
    }
}
