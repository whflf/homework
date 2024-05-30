Console.WriteLine("Enter an expression: ");
var input = Console.ReadLine();
if (input != null)
{
    try
    {
        var result = Calculator.CalculateExpression(input);
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
