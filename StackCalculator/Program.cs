using System.ComponentModel.Design;

Console.WriteLine("Enter an expression: ");
string? input = Console.ReadLine();
if (input != null)
{
    double result;
    try
    {
        result = Calculator.CalcExpression(input);
        Console.WriteLine(result);
    }
    catch (IncorrectExpressionException)
    {
        Console.WriteLine("Error: This expression isn't correct");
    }
    catch (DivideByZeroException)
    {
        Console.WriteLine("Error: Division by zero is forbidden");
    }
}
