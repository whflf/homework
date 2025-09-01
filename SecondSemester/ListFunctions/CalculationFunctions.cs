// <copyright file="CalculationFunctions.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace ListFunctions
{
    /// <summary>
    /// Provides a generic folding operation on a list of elements.
    /// </summary>
    public static class CalculationFunctions
    {
        /// <summary>
        /// Folds a list of elements into a single result using a specified binary function.
        /// </summary>
        /// <typeparam name="T">The type of elements in the list.</typeparam>
        /// <param name="list">The list of elements to fold.</param>
        /// <param name="value">The initial value for the folding operation.</param>
        /// <param name="fold">The binary function that defines the folding operation.</param>
        /// <returns>The result of folding the list using the specified function.</returns>
        /// <remarks>
        /// This method iterates over each element in the list and applies the folding function
        /// to combine the current accumulated value with the next element in the list.
        /// </remarks>
        public static T Fold<T>(List<T> list, T value, Func<T, T, T> fold)
        {
            for (var i = 0; i < list.Count; ++i)
            {
                value = fold(value, list[i]);
            }

            return value;
        }
    }
}
