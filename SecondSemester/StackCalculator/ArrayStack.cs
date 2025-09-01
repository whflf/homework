using System;

/// <inheritdoc/>
public class ArrayStack<T> : IStack<T>
{
    private T?[] array = new T?[16];
    private int top = -1;

    /// <inheritdoc/>
    public bool IsEmpty()
        => this.top == -1;

    /// <inheritdoc/>
    public void Push(T element)
    {
        ++this.top;
        if (this.top > this.array.Length - 1)
        {
            Array.Resize(ref this.array, this.array.Length * 2);
        }

        this.array[top] = element;
    }

    /// <inheritdoc/>
    public T Pop()
    {
        if (this.IsEmpty())
        {
            throw new UnderflowException("The stack is empty");
        }

        --this.top;
        var result = this.array[this.top + 1] ?? throw new ArgumentException("Couldn't pop from empty stack");

        return result;
    }
}
