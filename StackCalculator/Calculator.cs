using System;

public class IncorrectExpressionException : Exception { }

/// <summary>
/// Calculator that performs operations "+", "-", "*", "/" over an arithmetic expressions written in the postfix notation.
/// </summary>
public class Calculator
{
    private static Stack numbers = new Stack();

    private static void PushResult(string operation)
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
    public static double CalcExpression(string postfixNotation)
    {
        string[] expression = postfixNotation.Split(' ');

        foreach (string element in expression) 
        {
            if (int.TryParse(element, out int value))
            {
                numbers.Push(value);
            }
            else
            {
                PushResult(element);
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
