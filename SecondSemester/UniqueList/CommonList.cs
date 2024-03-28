namespace UniqueList;

public class CommonList<T>
{
    protected ListElement? _head = null;

    public int Count { get; private set; } = 0;

    public virtual void Add(T value)
    {
        ++this.Count;
        _head = new ListElement(value, _head, null);
    }

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