/// <summary>
/// Stack, a last-in-first-out container for double values.
/// </summary>
public interface IStack
{
    /// <summary>
    /// Checks whether the stack contains any value.
    /// </summary>
    /// <returns>True if there is no elements in the stack, otherwise false.</returns>
    bool IsEmpty();

    /// <summary>
    /// Adds element to a top of the stack.
    /// </summary>
    /// <param name="value">Element to add.</param>
    public void Push(double element);

    /// <summary>
    /// Gets element from a top of the stack and removes it.
    /// </summary>
    /// <returns>Element that was on the top.</returns>
    /// <exception cref="UnderflowException">Is thrown when the stack is empty.</exception>
    public double Pop();
}
