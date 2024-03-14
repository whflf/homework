string option;
string filePath;
try
{
    option = args[0];
    filePath = args[1];
}
catch (IndexOutOfRangeException)
{
    Console.WriteLine("No cmd arguments detected.");
    Environment.Exit(1);
}

string[] splittedFilePath = filePath.Split('.');
splittedFilePath = splittedFilePath[0..(splittedFilePath.Length - 1)];

if (option == "-comp")
{
    string newFilePath = string.Join(".", splittedFilePath) + ".zipped";
    var compressionCoefficient = LZW.Compress(filePath, newFilePath);
    Console.WriteLine($"File \"{filePath}\" was successfully compressed with coefficient {compressionCoefficient}.");
}
else if (option == "-unc")
{
    string newFilePath = string.Join(".", splittedFilePath);
    LZW.Uncompress(filePath, newFilePath);
    Console.WriteLine($"File \"{filePath}\" was successfully uncompressed.");
}
