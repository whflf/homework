// <copyright file="MapTests.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace ListFunctions.Tests
{
    /// <summary>
    /// Contains unit tests for the
    /// <see cref="TransformationFunctions.Map{TInput, TOutput}(List{TInput}, Func{TInput, TOutput})"/> method.
    /// </summary>
    public static class MapTests
    {
        private static readonly object[] TestData =
        {
            new object[]
            {
                new List<bool> { true, true, false, false }, 
                new Func<bool, bool>(x => !x),
                new List<bool> { false, false, true, true },
            },

            new object[]
            {
                new List<string> { "HELLO", "WORLD", "!" }, 
                new Func<string, string>(x => x.ToLower()),
                new List<string> { "hello", "world", "!" },
            },

            new object[]
            {
                new List<int> { 1, 2, 3, 4 }, 
                new Func<int, string>(x => x.ToString()),
                new List<string> { "1", "2", "3", "4" },
            },

            new object[]
            {
                new List<int>() { 1, 2, 3, 4 }, 
                new Func<int, int>(x => x * 2),
                new List<int> { 2, 4, 6, 8 },
            },

            new object[]
            {
                new List<int>(),
                new Func<int, int>(x => x * 2),
                new List<int>(),
            },

            new object[]
            {
                new List<int>() { 1, 2, 3, 4 },
                new Func<int, int>(x => x % 2 == 0 ? x : x * 2),
                new List<int> { 2, 2, 6, 4 },
            },
        };

        /// <summary>
        /// Verifies the correctness of the mapping operation on various input lists and mapping functions.
        /// </summary>
        /// <typeparam name="TInput">The type of elements in the input list.</typeparam>
        /// <typeparam name="TOutput">The type of elements in the output list after mapping.</typeparam>
        /// <param name="given">The input list to be mapped.</param>
        /// <param name="map">The mapping function to apply to each element.</param>
        /// <param name="expected">The expected output list after mapping.</param>
        [TestCaseSource(nameof(TestData))]
        public static void TestMap<TInput, TOutput>(List<TInput> given, Func<TInput, TOutput> map, List<TOutput> expected)
        {
            var mappedList = TransformationFunctions.Map(given, map);
            Assert.That(mappedList, Is.EqualTo(expected));
        }
    }
}
