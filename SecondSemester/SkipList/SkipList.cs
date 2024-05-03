// <copyright file="SkipList.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace SkipList
{
    using System.Collections;

    /// <summary>
    /// Represents a skip list data structure.
    /// </summary>
    /// <typeparam name="T">The type of elements in the skip list.</typeparam>
    public class SkipList<T> : IList<T>
        where T : IComparable<T>
    {
        private static readonly int MaxLevelAmount = 33;

        private Node head = new Node(default(T), MaxLevelAmount);

        private int levels = 1;

        private Random random = new Random();

        /// <inheritdoc/>
        public int Count { get; private set; } = 0;

        /// <inheritdoc/>
        public bool IsReadOnly => false;

        /// <inheritdoc/>
        public T this[int index]
        {
            get
            {
                if (index < 0 || index >= this.Count)
                {
                    throw new ArgumentOutOfRangeException(nameof(index));
                }

                var current = this.head.NextNodes[0];
                for (int i = 0; i < index; i++)
                {
                    current = current.NextNodes[0];
                }

                return current.Value;
            }

            set
            {
                if (index < 0 || index >= this.Count)
                {
                    throw new ArgumentOutOfRangeException(nameof(index));
                }

                var current = this.head.NextNodes[0];
                for (int i = 0; i < index; i++)
                {
                    current = current.NextNodes[0];
                }

                current.Value = value;
            }
        }

        /// <inheritdoc/>
        public void Add(T item)
        {
            var level = 0;
            for (int R = this.random.Next(); (R & 1) == 1; R >>= 1)
            {
                ++level;
                if (level == this.levels)
                {
                    ++this.levels;
                }
            }

            var newNode = new Node(item, level + 1);

            var current = this.head;
            for (var i = this.levels - 1; i >= 0; --i)
            {
                while (current.NextNodes[i] != null && current.NextNodes[i].Value.CompareTo(item) < 0)
                {
                    current = current.NextNodes[i];
                }

                if (i <= level)
                {
                    newNode.NextNodes[i] = current.NextNodes[i];
                    current.NextNodes[i] = newNode;
                }
            }

            ++this.Count;
        }

        /// <inheritdoc/>
        public void Clear()
        {
            if (this.head.NextNodes[0] == null)
            {
                return;
            }

            for (var i = 0; i < this.Count; ++i)
            {
                this.Remove(this.head.NextNodes[0].Value);
            }

            this.Count = 0;
        }

        /// <inheritdoc/>
        public bool Contains(T item)
        {
            var current = this.head;
            for (int i = this.levels - 1; i >= 0; --i)
            {
                while (current.NextNodes[i] != null && current.NextNodes[i].Value.CompareTo(item) != 0)
                {
                    current = current.NextNodes[i];
                }

                if (current.NextNodes[i] != null)
                {
                    return true;
                }
            }

            return false;
        }

        /// <inheritdoc/>
        public void CopyTo(T[] array, int arrayIndex)
        {
            if (array == null)
            {
                throw new ArgumentNullException(nameof(array));
            }

            if (arrayIndex < 0 || arrayIndex > array.Length)
            {
                throw new ArgumentOutOfRangeException(nameof(arrayIndex));
            }

            if (array.Length - arrayIndex < this.Count)
            {
                throw new ArgumentException("The number of elements in the SkipList is greater than the available space from arrayIndex to the end of the destination array.");
            }

            var current = this.head.NextNodes[0];
            for (var i = 0; i < this.Count; ++i)
            {
                array[arrayIndex + i] = current.Value;
                current = current.NextNodes[0];
            }
        }

        /// <inheritdoc/>
        public IEnumerator<T> GetEnumerator()
        {
            var current = this.head.NextNodes[0];
            while (current != null)
            {
                yield return current.Value;
                current = current.NextNodes[0];
            }
        }

        /// <inheritdoc/>
        public int IndexOf(T item)
        {
            var current = this.head;
            for (var i = 0; i < this.Count; ++i)
            {
                if (current.NextNodes[0].Value.CompareTo(item) == 0)
                {
                    return i;
                }

                current = current.NextNodes[0];
            }

            throw new ArgumentException("There is no item with such value in the list.");
        }

        /// <inheritdoc/>
        public void Insert(int index, T item)
        {
            this.Add(item);
        }

        /// <inheritdoc/>
        public bool Remove(T item)
        {
            var removed = false;
            var current = this.head;
            for (int i = this.levels - 1; i >= 0; --i)
            {
                while (current.NextNodes[i] != null && current.NextNodes[i].Value.CompareTo(item) < 0)
                {
                    current = current.NextNodes[i];
                }

                if (current.NextNodes[i] != null && current.NextNodes[i].Value.CompareTo(item) == 0)
                {
                    current.NextNodes[i] = current.NextNodes[i].NextNodes[i];
                    removed = true;
                }
            }

            this.Count = removed ? this.Count - 1 : this.Count;
            return removed;
        }

        /// <inheritdoc/>
        public void RemoveAt(int index)
            => this.Remove(this[index]);

        /// <inheritdoc/>
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }

        private class Node(T? value, int height)
        {
            public T? Value { get; set; } = value;

            public Node[] NextNodes { get; set; } = new Node[height];

            public int Level => this.NextNodes.Length;
        }
    }
}
