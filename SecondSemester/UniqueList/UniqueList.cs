namespace UniqueList;

/// <license>
/// https://github.com/whflf/homework/blob/main/LICENSE
/// </license>

/// <summary>
/// Represents a list that ensures unique elements.
/// </summary>
/// <typeparam name="T">The type of elements in the list.</typeparam>
public class UniqueList<T> : CommonList<T>
{
    /// <inheritdoc/>
    public override void Add(T value)
    {
        if (this.Contains(value))
        {
            throw new RepeatingValueException();
        }

        base.Add(value);
    }

    /// <inheritdoc/>
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
        if (this.head is null)
        {
            return false;
        }

        var current = this.head;

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
