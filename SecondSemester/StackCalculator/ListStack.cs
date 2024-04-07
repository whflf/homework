/// <inheritdoc/>
public class ListStack : IStack
{
    private StackElement? head = null;

    /// <inheritdoc/>
    public bool IsEmpty()
    {
        return head == null;
    }

    /// <inheritdoc/>
    public void Push(double value)
    {
        this.head = new StackElement(value, head);
    }

    /// <inheritdoc/>
    public double Pop()
    {
        if (this.IsEmpty())
        {
            throw new UnderflowException("The stack is empty");
        }

        double value = this.head.Value;
        this.head = this.head.Next;

        return value;
    }

    private class StackElement(double value, StackElement? next)
    {
        public double Value { get; set; } = value;
        public StackElement? Next { get; set; } = next;
    }
}
