namespace UniqueList;

public class CommonList<T>
{
    protected ListElement? _head = null;

    public int Count { get; private set; } = 0;

    public virtual void Add(T value, int position)
    {
        if (position > this.Count)
        {
            throw new IndexOutOfRangeException();
        }

        ++this.Count;
        
        if (position == 0)
        {
            _head = new ListElement(value, _head);
            return;
        }
        
        for (var i = 0; i < this.Count; ++i)
        {
            if (i != position - 1)
            {
                continue;
            }
            
            var previous = this.GetElement(i);
            previous.Next = new ListElement(value, previous.Next);
        }
    }

    public virtual void Remove(int position)
    {
        if (position > this.Count - 1)
        {
            throw new ElementNotFoundException();
        }

        --this.Count;
        
        if (position == 0)
        {
            _head = _head.Next;
            return;
        }
        
        for (var i = 0; i < this.Count; ++i)
        {
            if (i != position - 1)
            {
                continue;
            }
            
            var previous = this.GetElement(i);
            previous.Next = previous.Next.Next;
        }
    }

    public virtual void Change(T value, int position)
    {
        if (position >= this.Count)
        {
            throw new IndexOutOfRangeException();
        }

        this.GetElement(position).Value = value;
    }

    protected ListElement GetElement(int position)
    {
        var current = _head;

        for (var i = 0; i < position; ++i)
        {
            current = current.Next;
        }

        return current;
    }

    protected class ListElement(T value, ListElement? next)
    {
        public T Value { get; set; } = value;
        public ListElement? Next { get; set; } = next;
    }
}