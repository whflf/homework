Console.WriteLine("Enter 1 to transform a string or 2 to detransform: ");
var mode = Console.ReadLine();

if (mode == "1")
{
    Console.WriteLine("Enter a string: ");
    var inputString = Console.ReadLine();

    if (inputString is null)
    {
        Console.WriteLine("The string was null.");
        return;
    }

    var position = BurrowsWheeler.TransformStringAndGetPosition(ref inputString);
    Console.Write($"Transformation result: {inputString}, {position}\n");
}
else if (mode == "2")
{
    Console.WriteLine("Enter the string: ");
    string? inputString = Console.ReadLine();

    if (inputString is null)
    {
        Console.WriteLine("The string was null.");
        return;
    }

    Console.WriteLine("Enter the position: ");
    var position = Convert.ToInt32(Console.ReadLine());

    BurrowsWheeler.DetransformString(ref inputString, position);
    Console.Write($"Detransformation result: {inputString}\n");
}
else
{
    Console.WriteLine("Bad input");
}
