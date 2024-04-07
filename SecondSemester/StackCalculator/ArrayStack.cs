using System;

/// <inheritdoc/>
public class ArrayStack : IStack
{
    private double[] array;
    private int top;

    public ArrayStack()
    {
        this.array = new double[16];
        this.top = -1;
    }

    /// <inheritdoc/>
    public bool IsEmpty()
        => this.top == -1;

    /// <inheritdoc/>
    public void Push(double element)
    {
        ++this.top;
        if (this.top > this.array.Length - 1)
        {
            Array.Resize(ref this.array, this.array.Length * 2);
        }

        this.array[top] = element;
    }

    /// <inheritdoc/>
    public double Pop()
    {
        if (this.IsEmpty())
        {
            throw new UnderflowException("The stack is empty");
        }

        --this.top;
        return this.array[this.top + 1];
    }
}
