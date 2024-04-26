// <copyright file="PriorityQueueTests.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace PriorityQueue.Tests
{
    using NUnit.Framework;
    using PriorityQueue;

    /// <summary>
    /// Test class for testing the PriorityQueue class.
    /// </summary>
    [TestFixture]
    public class PriorityQueueTests
    {
        private readonly string[] _items = new string[] { "first", "second", "third" };

        private PriorityQueue<string> _queue = new PriorityQueue<string>();

        /// <summary>
        /// Test for basic enqueue and dequeue operations.
        /// </summary>
        /// <param name="start">Start index for items to enqueue.</param>
        /// <param name="step">Step size for items to enqueue.</param>
        [Test]
        public void TestBasicOperations()
        {
            for (var i = 0; i < this._items.Length; ++i)
            {
                this._queue.Enqueue(this._items[i], i);
            }

            for (var i = this._items.Length - 1; i >= 0; --i)
            {
                Assert.That(this._queue.Dequeue(), Is.EqualTo(this._items[i]));
            }
        }

        /// <summary>
        /// Test for enqueue and dequeue operations with a single element.
        /// </summary>
        [Test]
        public void TestSingleElement()
        {
            var item = "first";

            this._queue.Enqueue(item, 42);
            Assert.That(this._queue.Dequeue(), Is.EqualTo(item));
        }

        /// <summary>
        /// Test for enqueue and dequeue operations with multiple items having the same priority.
        /// </summary>
        [Test]
        public void TestSamePriority()
        {
            for (var i = 0; i < this._items.Length; ++i)
            {
                this._queue.Enqueue(this._items[i], 3);
            }

            for (var i = 0; i < this._items.Length; ++i)
            {
                Assert.That(this._queue.Dequeue(), Is.EqualTo(this._items[i]));
            }
        }

        /// <summary>
        /// Test for dequeue operation on an empty queue.
        /// </summary>
        [Test]
        public void TestEmptyQueue()
        {
            Assert.Throws<InvalidOperationException>(() => this._queue.Dequeue());
        }
    }
}
