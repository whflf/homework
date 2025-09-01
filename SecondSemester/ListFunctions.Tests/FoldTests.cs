// <copyright file="FoldTests.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace ListFunctions.Tests
{
    /// <summary>
    /// Contains unit tests for the <see cref="CalculationFunctions.Fold{T}(List{T}, T, Func{T, T, T})"/> method.
    /// </summary>
    public class FoldTests
    {
        private static readonly object[] TestData =
        {
            new object[]
            {
                new List<int> { 1, 2, 3, 4 },
                0,
                new Func<int, int, int>((acc, elem) => acc + elem),
                10,
            },

            new object[]
            {
                new List<int>(),
                0,
                new Func<int, int, int>((acc, elem) => acc + elem),
                0,
            },

            new object[]
            {
                new List<string>() { "Hello", " ", "World" },
                string.Empty,
                new Func<string, string, string>((acc, elem) => acc + elem),
                "Hello World",
            },
        };

        /// <summary>
        /// Verifies the correctness of the folding operation on various input lists, initial values, and folding functions.
        /// </summary>
        /// <typeparam name="T">The type of elements in the list.</typeparam>
        /// <param name="given">The input list to be folded.</param>
        /// <param name="initial">The initial value for the folding operation.</param>
        /// <param name="fold">The binary function used for folding.</param>
        /// <param name="expected">The expected result after folding.</param>
        [TestCaseSource(nameof(TestData))]
        public static void TestFold<T>(List<T> given, T initial, Func<T, T, T> fold, T expected)
        {
            var result = CalculationFunctions.Fold(given, initial, fold);
            Assert.That(result, Is.EqualTo(expected));
        }
    }
}
