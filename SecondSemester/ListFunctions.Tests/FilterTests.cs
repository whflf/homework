// <copyright file="FilterTests.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace ListFunctions.Tests
{
    /// <summary>
    /// Contains unit tests for the <see cref="TransformationFunctions.Filter{T}(List{T}, Predicate{T})"/> method.
    /// </summary>
    public class FilterTests
    {
        private static readonly object[] TestData =
        {
            new object[]
            {
                new List<int> { 1, 2, 3, 4, 5 },
                new Predicate<int>(x => x % 2 == 0),
                new List<int> { 2, 4 },
            },

            new object[]
            {
                new List<char> { 'H', 'e', 'L', 'l', 'O' },
                new Predicate<char>(c => char.IsUpper(c)),
                new List<char> { 'H', 'L', 'O' },
            },

            new object[]
            {
                new List<int> { 1, 2, 3, 4 },
                new Predicate<int>(x => true),
                new List<int> { 1, 2, 3, 4 },
            },

            new object[]
            {
                new List<int>() { 1, 2, 3, 4 },
                new Predicate<int>(x => false),
                new List<int>(),
            },

            new object[]
            {
                new List<int>(),
                new Predicate<int>(x => x % 2 == 0),
                new List<int>(),
            },
        };

        /// <summary>
        /// Verifies the correctness of the filtering operation on various input lists and predicates.
        /// </summary>
        /// <typeparam name="T">The type of elements in the list.</typeparam>
        /// <param name="given">The input list to be filtered.</param>
        /// <param name="filter">The predicate function used for filtering.</param>
        /// <param name="expected">The expected output list after filtering.</param>
        [TestCaseSource(nameof(TestData))]
        public static void TestFilter<T>(List<T> given, Predicate<T> filter, List<T> expected)
        {
            var mappedList = TransformationFunctions.Filter(given, filter);
            Assert.That(mappedList, Is.EqualTo(expected));
        }
    }
}
