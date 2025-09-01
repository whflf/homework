/// <summary>
/// Calculator that performs operations "+", "-", "*", "/" over an arithmetic expressions written in the postfix notation.
/// </summary>
public static class Calculator
{
    /// <summary>
    /// Calculates given expression.
    /// </summary>
    /// <param name="postfixNotation">Expression in the postfix notation to compute.</param>
    /// <param name="numbers">The stack to store numbers for calculator.</param>
    /// <returns>Expression value.</returns>
    /// <exception cref="IncorrectExpressionException">Is thrown when the input expression cannot be computed.</exception>
    public static double CalculateExpression(string postfixNotation, IStack<double> numbers)
    {
        var expression = postfixNotation.Split(' ');

        foreach (var element in expression) 
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
    
    private static void PushResult(string operation, IStack<double> numbers)
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
}
