/// <summary>
/// Trie, a tree data structure used for locating specific keys from within a set.
/// </summary>
public class Trie
{
    private Trie?[] next;
    private bool isTerminal;
    private int size;

    public Trie()
    {
        this.next = new Trie[256];
    }

    /// <summary>
    /// Adds the string to trie.
    /// </summary>
    /// <param name="element">String to add.</param>
    /// <param name="position">Character index in the string from which it is necessary to add it (initially 0).</param>
    /// <returns>True if the string was added, otherwise false.</returns>
    public bool Add(string element, int position = 0)
    {
        if (position == element.Length)
        {
            if (this.isTerminal)
            {
                return false;
            }

            this.isTerminal = true;
            return true;
        }

        bool newVertexCreated = false;
        if (this.next[element[position]] == null)
        {
            this.next[element[position]] = new Trie();
            ++this.size;
            newVertexCreated = true;

            if (position == element.Length - 1)
            {
                this.next[element[position]].isTerminal = true;
                return true;
            }
        }

        bool isNewElement = this.next[element[position]].Add(element, ++position);
        if (isNewElement && !newVertexCreated)
        {
            ++this.size;
        }

        return isNewElement;
    }

    /// <summary>
    /// Checks whether the string is in trie or not.
    /// </summary>
    /// <param name="element">String to check.</param>
    /// <param name="position">Character index in the string from which it is necessary to check it (initially 0).</param>
    /// <returns>True if the string is in trie, otherwise false.</returns>
    public bool Contains(string element, int position = 0)
    {
        if (position == element.Length)
        {
            return this.isTerminal;
        }

        if (this.next[element[position]] == null)
        {
            return false;
        }

        return this.next[element[position]].Contains(element, ++position);
    }

    /// <summary>
    /// Removes the string from trie.
    /// </summary>
    /// <param name="element">String to remove.</param>
    /// <param name="position">Character index in the string from which it is necessary to remove it (initially 0).</param>
    /// <returns></returns>
    public bool Remove(string element, int position = 0)
    {
        if (this.next[element[position]] == null)
        {
            return false;
        }

        if (position == element.Length - 1)
        {
            if (!this.next[element[position]].isTerminal)
            {
                return false;
            }

            if (this.size == 1)
            {
                this.next[element[position]] = null;
            }
            else
            {
                this.next[element[position]].isTerminal = false;
            }
            --this.size;
            return true;
        }

        bool isRemoved = this.next[element[position]].Remove(element, ++position);
        if (isRemoved && this.size == 1)
        {
            this.next[element[position]] = null;
        }
        --this.size;

        return isRemoved;
    }

    /// <summary>
    /// Counts how many strings in trie starts with a certain prefix.
    /// </summary>
    /// <param name="prefix">Prefix to check.</param>
    /// <param name="position">Character index in the prefix from which it is necessary to count strings (initially 0).</param>
    /// <returns></returns>
    public int HowManyStartsWithPrefix(string prefix, int position = 0)
    {
        if (position == prefix.Length)
        {
            if (this.isTerminal)
            {
                return this.size + 1;
            }

            return this.size;
        }

        if (this.next[prefix[position]] == null)
        {
            return 0;
        }

        return this.next[prefix[position]].HowManyStartsWithPrefix(prefix, ++position);
    }
}
