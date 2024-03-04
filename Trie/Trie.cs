using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

internal class Trie
{
    private Trie?[] next;
    private bool isTerminal;
    private int size;

    public Trie()
    {
        this.next = new Trie[256];
    }

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

            this.next[element[position]] = null;
            --this.size;
            return true;
        }

        return this.next[element[position]].Remove(element, ++position);   
    }

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
