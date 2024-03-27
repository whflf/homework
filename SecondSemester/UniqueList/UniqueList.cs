namespace UniqueList;

public class UniqueList<T> : CommonList<T>
{
    public override void Add(T value, int position)
    {
        if (this.Contains(value))
        {
            throw new RepeatingValueException();
        }
        
        base.Add(value, position);
    }

    public override void Change(T value, int position)
    {
        if (this.Contains(value))
        {
            throw new RepeatingValueException();
        }
        
        base.Change(value, position);
    }

    private bool Contains(T element)
    {
        if (this._head is null)
        {
            return false;
        }
        
        var current = this._head;
        
        for (var i = 0; i < this.Count; ++i)
        {
            if (current is null)
            {
                return false;
            }

            if (Equals(current.Value, element))
            {
                return true;
            }

            current = current.Next;
        }

        return false;
    }
}