using System;

/// <summary>
/// Stack, a last-in-first-out container for double values.
/// </summary>
public class Stack
{
    private class StackElement
    {
        public double Value { get; set; }
        public StackElement? Next { get; set; }

        public StackElement(double value)
        {
            this.Value = value;
        }
    }

    private StackElement? head = null;

    /// <summary>
    /// Checks whether the stack contains any value.
    /// </summary>
    /// <returns>True if there is no elements in the stack, otherwise false.</returns>
    public bool IsEmpty()
    {
        return head == null;
    }

    /// <summary>
    /// Adds element to a top of the stack.
    /// </summary>
    /// <param name="value">Element to add.</param>
    public void Push(double value)
    {
        StackElement newHead = new StackElement(value);
        newHead.Next = head;
        this.head = newHead;
    }

    /// <summary>
    /// Gets element from a top of the stack and removes it.
    /// </summary>
    /// <returns>Element that was on the top.</returns>
    /// <exception cref="UnderflowException">Is thrown when the stack is empty.</exception>
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
}
