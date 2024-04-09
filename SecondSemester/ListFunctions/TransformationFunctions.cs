// <copyright file="TransformationFunctions.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace ListFunctions
{
    /// <summary>
    /// Provides functions for transforming lists using mapping and filtering operations.
    /// </summary>
    public static class TransformationFunctions
    {
        /// <summary>
        /// Applies a transformation function to each element of a list and returns a new list containing the results.
        /// </summary>
        /// <typeparam name="TInput">The type of elements in the input list.</typeparam>
        /// <typeparam name="TOutput">The type of elements in the output list after transformation.</typeparam>
        /// <param name="list">The input list to be transformed.</param>
        /// <param name="map">The transformation function to apply to each element.</param>
        /// <returns>A new list containing the results of applying the transformation function to each element of the input list.</returns>
        /// <remarks>
        /// This method iterates over each element in the input list and applies the transformation function
        /// to generate the corresponding element in the output list.
        /// </remarks>
        public static List<TOutput> Map<TInput, TOutput>(List<TInput> list, Func<TInput, TOutput> map)
        {
            var newList = new List<TOutput>();

            for (var i = 0; i < list.Count; ++i)
            {
                newList.Add(map(list[i]));
            }

            return newList;
        }

        /// <summary>
        /// Filters elements from a list based on a predicate function and returns a new list containing the filtered elements.
        /// </summary>
        /// <typeparam name="T">The type of elements in the list.</typeparam>
        /// <param name="list">The input list to be filtered.</param>
        /// <param name="filter">The predicate function used to filter elements.</param>
        /// <returns>A new list containing only the elements that satisfy the predicate function.</returns>
        /// <remarks>
        /// This method iterates over each element in the input list and applies the predicate function
        /// to determine whether the element should be included in the output list.
        /// </remarks>
        public static List<T> Filter<T>(List<T> list, Predicate<T> filter)
        {
            var newList = new List<T>();

            for (var i = 0; i < list.Count; ++i)
            {
                if (filter(list[i]))
                {
                    newList.Add(list[i]);
                }
            }

            return newList;
        }
    }
}
