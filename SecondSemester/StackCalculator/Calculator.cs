public enum StackType
{
    ArrayStack,
    ListStack,
}

/// <summary>
/// Calculator that performs operations "+", "-", "*", "/" over an arithmetic expressions written in the postfix notation.
/// </summary>
public static class Calculator
{
    private static void PushResult(string operation, IStack numbers)
    {
        double a;
        double b;
        try
        {
            a = numbers.Pop();
            b = numbers.Pop();
        }
        catch (UnderflowException) 
        {
            throw new IncorrectExpressionException();
        }

        switch (operation)
        {
            case ("+"):
                numbers.Push(b + a);
                break;
            case ("-"): 
                numbers.Push(b - a); 
                break;
            case ("*"):
                numbers.Push(b * a);
                break;
            case ("/"):
                double delta = Math.Pow(10.0, -6.0);
                if (Math.Abs(a) < delta)
                {
                    throw new DivideByZeroException();
                }
                numbers.Push(b / a);
                break;
            default:
                throw new IncorrectExpressionException();
        }
    }

    /// <summary>
    /// Calculates given expression.
    /// </summary>
    /// <param name="postfixNotation">Expression in the postfix notation to compute.</param>
    /// <returns>Expression value.</returns>
    /// <exception cref="IncorrectExpressionException">Is thrown when the input expression cannot be computed.</exception>
    public static double CalcExpression(string postfixNotation, StackType stackType = StackType.ListStack)
    {
        IStack numbers;
        if (stackType == StackType.ArrayStack)
        {
            numbers = new ArrayStack();
        }
        else
        {
            numbers = new ListStack();
        }

        string[] expression = postfixNotation.Split(' ');

        foreach (string element in expression) 
        {
            if (int.TryParse(element, out var value))
            {
                numbers.Push(value);
            }
            else
            {
                PushResult(element, numbers);
            }
        }

        if (numbers.IsEmpty())
        {
            throw new IncorrectExpressionException();
        }

        double result = numbers.Pop();
        if (numbers.IsEmpty())
        {
            return result;
        }
        throw new IncorrectExpressionException();
    }
}
