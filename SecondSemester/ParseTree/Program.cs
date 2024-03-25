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
    Console.WriteLine("The expression for parse tree isn't correct.");
}
