/// <inheritdoc/>
public class ListStack<T> : IStack<T>
{
    private StackElement? head;

    /// <inheritdoc/>
    public bool IsEmpty()
        => head == null;

    /// <inheritdoc/>
    public void Push(T value)
    {
        this.head = new StackElement(value, head);
    }

    /// <inheritdoc/>
    public T Pop()
    {
        if (this.IsEmpty())
        {
            throw new UnderflowException("The stack is empty");
        }

        T value = this.head.Value ?? throw new ArgumentException("The stack is empty");
        this.head = this.head.Next;

        return value;
    }

    private class StackElement(T value, StackElement? next)
    {
        public T Value { get; set; } = value;
        public StackElement? Next { get; set; } = next;
    }
}
