try
{
    var parseTree = new ParseTree(File.ReadAllText(args[0]));

    Console.Write($"{parseTree} \n Result: {parseTree.CalculateExpression()}\n");
}
catch (IndexOutOfRangeException)
{
    Console.WriteLine("No arguments detected.");
}
catch (FileNotFoundException)
{
    Console.WriteLine($"Could not find file \"{args[0]}\"");
}
catch (IncorrectInputException)
{
    Console.WriteLine(
        """
        The expression for parse tree isn't correct. Please write it as follows:
        (<operator> <operand_1> <operand_2>),
        where <operand_1> and <operand_2> are either trees or numbers.
        """);
    Console.WriteLine("For example: (+ (* 1 2) 2)");
}
catch (DivideByZeroException)
{
    Console.WriteLine("Division by zero is forbidden.");
}
