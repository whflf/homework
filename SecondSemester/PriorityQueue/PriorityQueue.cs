// <copyright file="PriorityQueue.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace PriorityQueue
{
    /// <summary>
    /// Represents a priority queue data structure.
    /// </summary>
    /// <typeparam name="T">The type of elements in the priority queue.</typeparam>
    public class PriorityQueue<T>
    {
        private List<(T Item, int Priority)> heap;

        /// <summary>
        /// Initializes a new instance of the <see cref="PriorityQueue{T}"/> class.
        /// </summary>
        public PriorityQueue()
        {
            this.heap = new List<(T, int)>();
        }

        /// <summary>
        /// Gets a value indicating whether the priority queue is empty.
        /// </summary>
        public bool Empty { get => this.heap.Count == 0; }

        /// <summary>
        /// Adds an element to the priority queue with the specified priority.
        /// </summary>
        /// <param name="item">The element to add.</param>
        /// <param name="priority">The priority of the element.</param>
        public void Enqueue(T item, int priority)
        {
            this.heap.Add((Item: item, Priority: priority));

            var i = this.heap.Count - 1;
            while (i > 0)
            {
                var parent = (i - 1) / 2;
                if (this.heap[parent].Priority >= priority)
                {
                    break;
                }

                this.Swap(parent, i);
                i = parent;
            }
        }

        /// <summary>
        /// Removes and returns the element with the highest priority from the priority queue.
        /// </summary>
        /// <returns>The element with the highest priority.</returns>
        public T Dequeue()
        {
            if (this.Empty)
            {
                throw new InvalidOperationException("Queue is empty");
            }

            var item = this.heap[0].Item;
            var lastIndex = this.heap.Count - 1;

            while (lastIndex != 0 && this.heap[lastIndex].Priority == this.heap[lastIndex - 1].Priority)
            {
                --lastIndex;
            }

            this.heap[0] = this.heap[lastIndex];
            this.heap.RemoveAt(lastIndex--);

            var current = 0;
            while (true)
            {
                var left = (current * 2) + 1;
                var right = (current * 2) + 2;

                if (left > lastIndex)
                {
                    break;
                }

                var next = right <= lastIndex && this.heap[right].Priority > this.heap[left].Priority ? right : left;

                if (this.heap[current].Priority >= this.heap[next].Priority)
                {
                    break;
                }

                this.Swap(current, next);
                current = next;
            }

            return item;
        }

        private void Swap(int i, int j)
        {
            var temp = this.heap[i];
            this.heap[i] = this.heap[j];
            this.heap[j] = temp;
        }
    }
}
