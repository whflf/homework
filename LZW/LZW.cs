using System.Collections.Generic;
using static System.Runtime.InteropServices.JavaScript.JSType;

/// <summary>
/// Provides methods for compressing and decompressing data using the LZW algorithm.
/// </summary>
/// <remarks>
/// Lempel - Ziv - Welch (LZW) is a lossless data compression algorithm. 
/// It works by replacing repeated occurrences of substrings with 
/// fixed-size codes, thus reducing the size of the data.
/// </remarks>
public static class LZW
{
    private static byte[] ReadDataFromFile(string filePath)
    {
        BinaryReader reader = new BinaryReader(File.Open(filePath, FileMode.Open));
        var data = new byte[reader.BaseStream.Length];
        var dataIndex = 0;

        using (reader)
        {
            while (reader.BaseStream.Position != reader.BaseStream.Length)
            {
                data[dataIndex++] = reader.ReadByte();
            }
        }

        return data;
    }

    private static void WriteDataToFile(string filePath, byte[] data)
    {
        using (BinaryWriter writer = new BinaryWriter(File.Open(filePath, FileMode.Create)))
        {
            for (int i = 0; i < data.Length; ++i)
            {
                writer.Write(data[i]);
            }
        }
    }

    private static List<bool> GetOutputCode(string phrase, Trie dictionary)
    {
        var bitLength = 9;
        var bits = new List<bool>();

        while ((1 << bitLength) < Trie.Total)
        {
            ++bitLength;
        }

        var code = dictionary.GetCode(phrase);

        for (int i = bitLength - 1; i >= 0; --i)
        {
            bits.Add((code & (1 << i)) != 0);
        }

        return bits;
    }

    private static byte[] BitsToBytes(List<bool> bits)
    {
        var bytesCount = bits.Count / 8 + (bits.Count % 8 != 0 ? 1 : 0);
        var result = new byte[bytesCount];

        var bitIndex = 0;
        var byteIndex = 0;
        byte currentByte = 0;

        foreach (bool bit in bits)
        {
            if (bit)
            {
                currentByte |= (byte)(1 << (7 - bitIndex));
            }

            ++bitIndex;

            if (bitIndex == 8)
            {
                result[byteIndex++] = currentByte;
                bitIndex = 0;
                currentByte = 0;
            }
        }

        if (bitIndex != 0)
        {
            result[byteIndex] = currentByte;
        }

        return result;
    }

    /// <summary>
    /// Compresses the data from a specified file and writes the compressed data to another file.
    /// </summary>
    /// <param name="filePathRead">The path of the file to compress.</param>
    /// <param name="filePathWrite">The path of the file to write the compressed data to.</param>
    /// <returns>The compression ratio achieved by the compression process.</returns>
    public static double Compress(string filePathRead, string filePathWrite)
    {
        byte[] data = ReadDataFromFile(filePathRead);

        Trie dictionary = new Trie();
        for (int i = 0; i < 256; ++i)
        {
            dictionary.Add(Convert.ToString(Convert.ToChar(i)));
        }

        var bits = new List<bool>();
        var currentPhrase = "";
        var previousPhrase = "";

        for (int i = 0; i < data.Length; ++i)
        {
            var character = Convert.ToString(Convert.ToChar(data[i]));
            currentPhrase += character;

            if (dictionary.Add(currentPhrase))
            {
                bits.AddRange(GetOutputCode(previousPhrase, dictionary));
                currentPhrase = character;
            }
            previousPhrase = currentPhrase;
        }
        bits.AddRange(GetOutputCode(previousPhrase, dictionary));


        var result = BitsToBytes(bits);
        WriteDataToFile(filePathWrite, result);

        return (double)data.Length / (double)result.Length;
    }

    private static List<bool> GetBits(byte[] data)
    {
        var bits = new List<bool>();

        foreach (byte element in data)
        {
            for (int i = 7; i >= 0; --i)
            {
                bits.Add((element & (1 << i)) != 0);
            }
        }

        return bits;
    }

    private static int BinaryToDecimal(bool[] bitCode)
    {
        var code = 0;
        for (int i = 0; i < bitCode.Length; ++i)
        {
            code += (1 << (bitCode.Length - 1 - i)) * Convert.ToInt32(bitCode[i]);
        }

        return code;
    }

    /// <summary>
    /// Decompresses the data from a specified file and writes the decompressed data to another file.
    /// </summary>
    /// <param name="filePathRead">The path of the file to decompress.</param>
    /// <param name="filePathWrite">The path of the file to write the decompressed data to.</param>
    public static void Uncompress(string filePathRead, string filePathWrite)
    {
        byte[] data = ReadDataFromFile(filePathRead);

        var result = "";
        List<bool> bitCodes = GetBits(data);

        var dictionary = new List<string>();
        for (int i = 0; i < 256; ++i)
        {
            dictionary.Add(Convert.ToString(Convert.ToChar(i)));
        }

        var codeLength = 9;
        var index = 0;
        var currentPhrase = "";
        var inputEnd = false;

        while (index != bitCodes.Count)
        {
            bool[] currentCode;
            if (dictionary.Count < 511)
            {
                currentCode = new bool[codeLength];
                for (int j = 0; j < codeLength; ++j)
                {
                    if (index == bitCodes.Count)
                    {
                        inputEnd = true;
                        break;
                    }
                    currentCode[j] = bitCodes[index++];
                }
            }
            else
            {
                currentCode = new bool[codeLength];
                for (int j = 0; j < codeLength; ++j)
                {
                    if (index == bitCodes.Count)
                    {
                        inputEnd = true;
                        break;
                    }
                    currentCode[j] = bitCodes[index++];
                }
            }

            if (inputEnd)
            {
                break;
            }

            var code = BinaryToDecimal(currentCode);
            var phraseIndex = 0;

            string entry;
            try
            {
                entry = dictionary[code];
            }
            catch (ArgumentOutOfRangeException)
            {
                entry = currentPhrase + currentPhrase[0];
            }
            while (phraseIndex < entry.Length)
            {
                currentPhrase += entry[phraseIndex++];
                if (!dictionary.Contains(currentPhrase))
                {
                    dictionary.Add(currentPhrase);
                    if (dictionary.Count == (1 << codeLength) - 1)
                    {
                        ++codeLength;
                    }
                    break;
                }
            }

            result += entry;
            currentPhrase = entry;
        }

        WriteDataToFile(filePathWrite, System.Text.Encoding.Default.GetBytes(result));
    }
}
