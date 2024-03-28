namespace UniqueList;

/// <license>
/// https://github.com/whflf/homework/blob/main/LICENSE
/// </license>

/// <summary>
/// Represents a common list data structure.
/// </summary>
/// <typeparam name="T">The type of elements in the list.</typeparam>
public class CommonList<T>
{
    /// <summary>
    /// The head element of the list.
    /// </summary>
    protected ListElement? Head = null;

    protected ListElement? Tail = null;

    /// <summary>
    /// Gets the number of elements contained in the list.
    /// </summary>
    public int Count { get; private set; } = 0;

    /// <summary>
    /// Adds an element to the end of the list.
    /// </summary>
    /// <param name="value">The value to add to the list.</param>
    public virtual void Add(T value)
    {
        ++this.Count;
        Tail = new ListElement(value, null, Tail);
        if (Tail.Previous is not null)
        {
            Tail.Previous.Next = Tail;
        }

        this.Head ??= this.Tail;
    }

    /// <summary>
    /// Removes the first occurrence of a specific element from the list.
    /// </summary>
    /// <param name="value">The value to remove from the list.</param>
    /// <exception cref="ElementNotFoundException">Thrown when the specified element is not found in the list.</exception>
    public virtual void Remove(T value)
    {
        var current = this.Head;

        for (var i = 0; i < this.Count; ++i)
        {
            if (!Equals(value, current.Value))
            {
                current = current.Next;
                continue;
            }

            if (current != this.Head)
            {
                current.Previous.Next = current.Next;
            }
            else
            {
                Head = Head.Next;
                if (Head is not null)
                {
                    Head.Previous = null;
                }
            }

            if (current == this.Tail)
            {
                this.Tail = current.Previous;
            }

            --this.Count;
            return;
        }

        throw new ElementNotFoundException();
    }

    /// <summary>
    /// Changes the value of an element at the specified position in the list.
    /// </summary>
    /// <param name="value">The new value.</param>
    /// <param name="position">The zero-based position of the element to change.</param>
    /// <exception cref="IndexOutOfRangeException">Thrown when the specified position is out of range.</exception>
    public virtual void Change(T value, int position)
    {
        if (position >= this.Count)
        {
            throw new IndexOutOfRangeException();
        }

        var current = this.Head;
        for (var i = 0; i < position; ++i)
        {
            current = current.Next;
        }

        current.Value = value;
    }

    /// <summary>
    /// Represents an element in the list.
    /// </summary>
    /// <param name="value">The value stored in the element.</param>
    /// <param name="next">The next element for the current one.</param>
    /// <param name="previous">The previous element for the current one.</param>
    protected class ListElement(T value, ListElement? next, ListElement? previous)
    {
        /// <summary>
        /// Gets or sets the value of the element.
        /// </summary>
        public T Value { get; set; } = value;

        /// <summary>
        /// Gets or sets the next element for the current one.
        /// </summary>
        public ListElement? Next { get; set; } = next;

        /// <summary>
        /// Gets or sets the previous element for the current one.
        /// </summary>
        public ListElement? Previous { get; set; } = previous;
    }
}
