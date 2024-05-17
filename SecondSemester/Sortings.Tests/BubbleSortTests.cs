// <copyright file="BubbleSortTests.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace Sortings.Tests;

/// <summary>
/// Provides test cases for the BubbleSort method in the Sortings class.
/// </summary>
public class BubbleSortTests
{
    private static IEnumerable<TestCaseData> BubbleSortTestCases
    {
        get
        {
            yield return new TestCaseData(
                new List<int> { 3, 2, 1 },
                new List<int> { 1, 2, 3 },
                Comparer<int>.Default);
            yield return new TestCaseData(
                new List<int> { 1, 2, 3 },
                new List<int> { 1, 2, 3 },
                Comparer<int>.Default);
            yield return new TestCaseData(
                new List<int> { -2, 1, -3 },
                new List<int> { 1, -2, -3 },
                Comparer<int>.Create((x, y) => Math.Abs(x).CompareTo(Math.Abs(y))));
            yield return new TestCaseData(
                new List<string> { "dog", "rabbit", "cat" },
                new List<string> { "cat", "dog", "rabbit" },
                Comparer<string>.Default);
            yield return new TestCaseData(
                new List<string> { "dog", "rabbit", "cat" },
                new List<string> { "dog", "cat", "rabbit" },
                Comparer<string>.Create((x, y) => x.Length.CompareTo(y.Length)));
            yield return new TestCaseData(
                new List<string>(),
                new List<string>(),
                Comparer<string>.Default);
            yield return new TestCaseData(
                new List<char> { 'f', 'f', 'f' },
                new List<char> { 'f', 'f', 'f' },
                Comparer<char>.Default);
            yield return new TestCaseData(
                new List<char> { 'f' },
                new List<char> { 'f' },
                Comparer<char>.Default);
        }
    }

    /// <summary>
    /// Tests the BubbleSort method with various test cases.
    /// </summary>
    /// <typeparam name="T">The type of the items in the list.</typeparam>
    /// <param name="list">The list to sort.</param>
    /// <param name="expected">The expected result after sorting.</param>
    /// <param name="comparer">The comparer to use for sorting.</param>
    [TestCaseSource(nameof(BubbleSortTestCases))]
    public void BubbleSortTest<T>(List<T> list, List<T> expected, IComparer<T> comparer)
    {
        var actual = Sortings.BubbleSort(list, comparer);
        for (var i = 0; i < expected.Count; ++i)
        {
            Assert.That(actual[i], Is.EqualTo(expected[i]));
        }
    }
}
