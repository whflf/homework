namespace UniqueList;

/// <summary>
/// Represents a common list data structure.
/// </summary>
/// <typeparam name="T">The type of elements in the list.</typeparam>
public class CommonList<T>
{
    /// <summary>
    /// The head element of the list.
    /// </summary>
    protected ListElement? _head = null;

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
        _head = new ListElement(value, _head, null);
    }

    /// <summary>
    /// Removes the first occurrence of a specific element from the list.
    /// </summary>
    /// <param name="value">The value to remove from the list.</param>
    /// <exception cref="ElementNotFoundException">Thrown when the specified element is not found in the list.</exception>
    public virtual void Remove(T value)
    {
        var current = _head;

        for (var i = 0; i < this.Count; ++i)
        {
            if (!Equals(value, current.Value))
            {
                current = current.Next;
                continue;
            }

            if (current.Previous != null)
            {
                current.Previous.Next = current.Next;
            }
            else
            {
                _head = _head.Next;
                if (_head is not null)
                {
                    _head.Previous = null;
                }
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

        var current = _head;
        for (var i = 0; i < position; ++i)
        {
            current = current.Next;
        }
        current.Value = value;
    }

    protected class ListElement(T value, ListElement? next, ListElement? previous)
    {
        public T Value { get; set; } = value;
        public ListElement? Next { get; set; } = next;
        public ListElement? Previous { get; set; } = previous;
    }
}
