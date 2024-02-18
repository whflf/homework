void SortShifts(int[] shifts, string inputString)
{
    for (int i = 0; i < shifts.Length; ++i)
    {
        for (int j = 0; j < shifts.Length - 1 - i; ++j)
        {
            int index1 = shifts[j];
            int index2 = shifts[j + 1];
            while (inputString[index1 % inputString.Length] == inputString[index2 % inputString.Length])
            {
                ++index1;
                ++index2;
            }

            if (inputString[index1 % inputString.Length] > inputString[index2 % inputString.Length])
            {
                (shifts[j], shifts[j + 1]) = (shifts[j + 1], shifts[j]);
            }
        }
    }
}
int TransformStringAndGetPosition(ref string inputString)
{
    int[] shifts = new int[inputString.Length];

    for (int i = 0; i < inputString.Length; ++i)
    {
        shifts[i] = i;
    }
    SortShifts(shifts, inputString);
    char[] charString = inputString.ToCharArray();

    int position = 0;
    for (int i = 0; i < shifts.Length; ++i)
    {
        if (shifts[i] == 0)
        {
            position = i;
        }

        charString[i] = inputString[(shifts[i] + inputString.Length - 1) % inputString.Length];
    }

    inputString = new string(charString);
    return position;
}

int[] GetDetransformationVector(char[] charString)
{
    char[] sortedCharString = new char[charString.Length];
    Array.Copy(charString, sortedCharString, charString.Length);
    Array.Sort(sortedCharString);

    int[] detransformationVector = new int[charString.Length];
    Array.Fill(detransformationVector, -1);

    for (int i = 0; i < charString.Length; ++i)
    {
        for (int j = 0; j < charString.Length; ++j)
        {
            if (charString[i] == sortedCharString[j] && detransformationVector[j] == -1)
            {
                detransformationVector[j] = i;
                break;
            }
        }
    }

    return detransformationVector;
}
void DetransformString(ref string inputString, int position)
{
    char[] charString = inputString.ToArray();
    int[] vector = GetDetransformationVector(charString);
    position = vector[position];

    for (int i = 0; i < charString.Length; ++i)
    {
        charString[i] = inputString[position];
        position = vector[position];
    }

    inputString = new string(charString);
}

Console.WriteLine("Enter 1 to transform a string or 2 to detransform: ");
string? mode = Console.ReadLine();

if (mode == "1")
{
    Console.WriteLine("Enter a string: ");
    string? inputString = Console.ReadLine();

    int position = TransformStringAndGetPosition(ref inputString);
    Console.Write($"Transformation result: {inputString}, {position}\n");
}
else if (mode == "2")
{
    Console.WriteLine("Enter the string: ");
    string? inputString = Console.ReadLine();
    Console.WriteLine("Enter the position: ");
    int position = Convert.ToInt32(Console.ReadLine());

    DetransformString(ref inputString, position);
    Console.Write($"Detransformation result: {inputString}\n");
}
else
{
    Console.WriteLine("Bad input");
}
