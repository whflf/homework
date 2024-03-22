/// <summary>
/// Trie, a tree data structure used for locating specific keys from within a set.
/// </summary>
public class Trie
{
    private class TrieElement
    {
        private TrieElement?[] next;
        private bool isTerminal = false;
        private int size = 0;
        public int code;

        public TrieElement()
        {
            this.next = new TrieElement[256];
        }

        public bool Add(string element, ref int total, int position = 0)
        {
            TrieElement current = this;
            while (position < element.Length)
            {
                if (current.next[element[position]] == null)
                {
                    current.next[element[position]] = new TrieElement();
                    ++current.size;

                    if (position == element.Length - 1)
                    {
                        current.next[element[position]].isTerminal = true;
                        current.next[element[position]].code = total++;
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
            current.code = total++;
            return true;
        }

        public bool Contains(string element, int position = 0)
        {
            TrieElement current = this;
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

        public int GetCode(string element, int position = 0)
        {
            TrieElement current = this;
            while (position < element.Length)
            {
                if (current.next[element[position]] == null)
                {
                    return -1;
                }

                current = current.next[element[position]];
                ++position;
            }

            return current.code;
        }
    }

    public int Total { get; private set; } = 0;

    private TrieElement head;

    public Trie()
    {
        this.head = new TrieElement();
    }

    /// <summary>
    /// Adds the string to trie.
    /// </summary>
    /// <param name="element">String to add.</param>
    /// <param name="position">Character index in the string from which it is necessary to add it (initially 0).</param>
    /// <returns>True if the string was added, otherwise false.</returns>
    public bool Add(string element)
    {
        var tempTotal = this.Total;
        var result = head.Add(element, ref tempTotal);
        this.Total = tempTotal;

        return result;
    }

    /// <summary>
    /// Checks whether the string is in trie or not.
    /// </summary>
    /// <param name="element">String to check.</param>
    /// <param name="position">Character index in the string from which it is necessary to check it (initially 0).</param>
    /// <returns>True if the string is in trie, otherwise false.</returns>
    public bool Contains(string element)
    {
        return head.Contains(element);
    }

    /// <summary>
    /// Allows to know an index number of the element. 
    /// </summary>
    /// <param name="element">Element to get the index of.</param>
    /// <returns>Number code which represents slement's index number.</returns>
    public int GetCode(string element)
    {
        return head.GetCode(element);
    }
}
