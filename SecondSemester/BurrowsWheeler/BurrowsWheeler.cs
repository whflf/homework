/// <summary>
/// Provides methods for performing the Burrows-Wheeler Transform (BWT) and its inverse transform.
/// </summary>
public static class BurrowsWheeler
{
    private static void SortShifts(int[] shifts, string inputString)
    {
        for (var i = 0; i < shifts.Length; ++i)
        {
            for (var j = 0; j < shifts.Length - 1 - i; ++j)
            {
                var index1 = shifts[j];
                var index2 = shifts[j + 1];
                var comparisons = 0;

                while (inputString[index1 % inputString.Length] == inputString[index2 % inputString.Length])
                {
                    ++index1;
                    ++index2;

                    if (++comparisons == inputString.Length)
                    {
                        break;
                    }
                }

                if (inputString[index1 % inputString.Length] > inputString[index2 % inputString.Length])
                {
                    (shifts[j], shifts[j + 1]) = (shifts[j + 1], shifts[j]);
                }
            }
        }
    }

    /// <summary>
    /// Transforms the input string using the Burrows-Wheeler Transform and returns the position of the original string.
    /// </summary>
    /// <param name="inputString">The input string to be transformed.</param>
    /// <returns>The position of the original string within the transformed string.</returns>
    public static (string transformed, int position) TransformStringAndGetPosition(string inputString)
    {
        var result = (transformed: string.Empty, position: 0);

        var shifts = new int[inputString.Length];

        for (var i = 0; i < inputString.Length; ++i)
        {
            shifts[i] = i;
        }

        SortShifts(shifts, inputString);
        var charString = inputString.ToCharArray();

        for (var i = 0; i < shifts.Length; ++i)
        {
            if (shifts[i] == 0)
            {
                result.position = i;
            }

            charString[i] = inputString[(shifts[i] + inputString.Length - 1) % inputString.Length];
        }

        result.transformed = new string(charString);
        return result;
    }

    private static int[] GetDetransformationVector(char[] charString)
    {
        var sortedCharString = new char[charString.Length];
        Array.Copy(charString, sortedCharString, charString.Length);
        Array.Sort(sortedCharString);

        var detransformationVector = new int[charString.Length];
        Array.Fill(detransformationVector, -1);

        for (var i = 0; i < charString.Length; ++i)
        {
            for (var j = 0; j < charString.Length; ++j)
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

    /// <summary>
    /// Performs the inverse Burrows-Wheeler Transform to reconstruct the original string.
    /// </summary>
    /// <param name="inputString">The transformed string to be detransformed.</param>
    /// <param name="position">The position of the original string within the transformed string.</param>
    public static string DetransformString(string inputString, int position)
    {
        var detransformed = string.Empty;

        var charString = inputString.ToArray();
        var vector = GetDetransformationVector(charString);

        if (vector.Length == 0)
        {
            return detransformed;
        }

        position = vector[position];

        for (var i = 0; i < charString.Length; ++i)
        {
            charString[i] = inputString[position];
            position = vector[position];
        }

        detransformed = new string(charString);

        return detransformed;
    }
}
