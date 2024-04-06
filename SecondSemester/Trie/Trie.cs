/// <summary>
/// Trie, a tree data structure used for locating specific keys from within a set.
/// </summary>
public class Trie
{

    private readonly TrieElement head;

    public Trie()
    {
        this.head = new TrieElement();
    }

    /// <summary>
    /// Adds the string to trie.
    /// </summary>
    /// <param name="element">String to add.</param>
    /// <returns>True if the string was added, otherwise false.</returns>
    public bool Add(string element)
    {
        return head.Add(element);
    }

    /// <summary>
    /// Checks whether the string is in trie or not.
    /// </summary>
    /// <param name="element">String to check.</param>
    /// <returns>True if the string is in trie, otherwise false.</returns>
    public bool Contains(string element)
    {
        return head.Contains(element);
    }

    /// <summary>
    /// Removes the string from trie.
    /// </summary>
    /// <param name="element">String to remove.</param>
    /// <param name="position">Character index in the string from which it is necessary to remove it (initially 0).</param>
    /// <returns>True if the string was added, otherwise false.</returns>
    public bool Remove(string element)
    {
        return head.Remove(element);
    }

    /// <summary>
    /// Counts how many strings in trie starts with a certain prefix.
    /// </summary>
    /// <param name="prefix">Prefix to check.</param>
    /// <param name="position">Character index in the prefix from which it is necessary to count strings (initially 0).</param>
    /// <returns>The amount of strings starting with given prefix.</returns>
    public int HowManyStartsWithPrefix(string prefix)
    {
        return head.HowManyStartsWithPrefix(prefix);
    }

    private class TrieElement
    {
        private readonly TrieElement?[] next;
        private bool isTerminal;
        private int size;

        public TrieElement()
        {
            this.next = new TrieElement[256];
        }

        public bool Add(string element, int position = 0)
        {
            var current = this;
            while (position < element.Length)
            {
                if (current.next[element[position]] == null)
                {
                    current.next[element[position]] = new TrieElement();
                    ++current.size;

                    if (position == element.Length - 1)
                    {
                        current.next[element[position]].isTerminal = true;
                        return true;
                    }
                }

                current = current.next[element[position]];
                ++position;
            }

            if (current.isTerminal)
            {
                return false;
            }

            current.isTerminal = true;
            return true;
        }

        public bool Contains(string element)
        {
            var current = this;
            var position = 0;

            while (position < element.Length)
            {
                if (current.next[element[position]] == null)
                {
                    return false;
                }

                current = current.next[element[position]];
                ++position;
            }

            return current.isTerminal;
        }

        public bool Remove(string element)
        {
            var current = this;
            var position = 0;
            var visitedNodes = new List<TrieElement?> { current };

            while (position < element.Length)
            {
                if (current.next[element[position]] == null)
                {
                    return false;
                }

                current = current.next[element[position]];
                visitedNodes.Add(current);
                ++position;
            }

            if (!current.isTerminal)
            {
                return false;
            }

            current.isTerminal = false;

            if (current.size > 0)
            {
                return true;
            }
            else
            {
                current = null;
            }

            for (var i = visitedNodes.Count - 2; i >= 0; --i)
            {
                if (visitedNodes[i].size-- == 0)
                {
                    visitedNodes[i] = null;
                }
            }

            return true;
        }

        public int HowManyStartsWithPrefix(string prefix)
        {
            var current = this;
            var position = 0;

            while (position < prefix.Length)
            {
                if (current.next[prefix[position]] == null)
                {
                    return 0;
                }

                current = current.next[prefix[position]];
                ++position;
            }

            var result = current.size;

            if (current.isTerminal)
            {
                ++result;
            }

            return result;
        }
    }
}
