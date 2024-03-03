using System;

/// <summary>
/// Stack, a last-in-first-out container for double values.
/// </summary>
public class ArrayStack
{
    private int[] array;
    private int capacity;
    private int top;

    public ArrayStack()
    {
        this.capacity = 16;
        this.array = new int[this.capacity];
        this.top = -1;
    }

    /// <summary>
    /// Checks whether the stack contains any value.
    /// </summary>
    /// <returns>True if there is no elements in the stack, otherwise false.</returns>
    public bool IsEmpty()
    {
        return this.top == -1;
    }

    /// <summary>
    /// Adds element to a top of the stack.
    /// </summary>
    /// <param name="value">Element to add.</param>
    public void Push(int element)
    {
        ++this.top;
        if (this.top <= this.capacity - 1)
        {
            this.array[this.top] = element;
        }
        else
        {
            this.capacity *= 2;
            int[] newStack = new int[this.capacity];
            for (int i = 0; i < this.array.Length; ++i)
            {
                newStack[i] = this.array[i];
            }
            this.array = newStack;
        }
    }

    /// <summary>
    /// Gets element from a top of the stack and removes it.
    /// </summary>
    /// <returns>Element that was on the top.</returns>
    /// <exception cref="UnderflowException">Is thrown when the stack is empty.</exception>
    public int Pop()
    {
        if (this.IsEmpty())
        {
            throw new UnderflowException("The stack is empty");
        }

        --this.top;
        return this.array[this.top + 1];
    }
}
