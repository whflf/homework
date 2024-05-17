// <copyright file="Sortings.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace Sortings;

/// <summary>
/// Provides sorting methods.
/// </summary>
public static class Sortings
{
    /// <summary>
    /// Sorts a list of items using the bubble sort algorithm.
    /// </summary>
    /// <typeparam name="T">The type of the items in the list.</typeparam>
    /// <param name="list">The list to sort.</param>
    /// <param name="comparer">The comparer to use for sorting.</param>
    /// <returns>A new list containing the sorted items.</returns>
    public static List<T> BubbleSort<T>(List<T> list, IComparer<T> comparer)
    {
        var listCopy = new List<T>(list);
        for (var i = 0; i < listCopy.Count - 1; i++)
        {
            for (var j = 0; j < listCopy.Count - i - 1; j++)
            {
                if (comparer.Compare(listCopy[j], listCopy[j + 1]) > 0)
                {
                    var temp = listCopy[j];
                    listCopy[j] = listCopy[j + 1];
                    listCopy[j + 1] = temp;
                }
            }
        }

        return listCopy;
    }
}
