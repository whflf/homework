namespace SkipList
{
    using System.Collections;

    public class SkipList<T> : IList<T>
        where T : IComparable<T>
    {
        private static readonly int MaxLevelAmount = 33;

        private Node head = new Node(default(T), MaxLevelAmount);

        private int levels = 1;

        private Random random = new Random();

        public int Count { get; private set; } = 0;

        public bool IsReadOnly => throw new NotImplementedException();

        public T this[int index] { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

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

        public IEnumerator<T> GetEnumerator()
        {
            var current = this.head.NextNodes[0];
            while (current != null)
            {
                yield return current.Value;
                current = current.NextNodes[0];
            }
        }

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

        public void Insert(int index, T item)
        {
            this.Add(item);
        }

        public bool Remove(T item)
        {
            var current = this.head;
            var removed = false;
            for (int i = this.levels - 1; i >= 0; --i)
            {
                while (current.NextNodes[i] != null && current.NextNodes[i].Value.CompareTo(item) != 0)
                {
                    current = current.NextNodes[i];
                }

                if (current.NextNodes[i] != null)
                {
                    for (var j = i; j >= 0; --j)
                    {
                        current.NextNodes[j] = current.NextNodes[j].NextNodes[j];
                    }

                    removed = true;
                    break;
                }
            }

            this.Count = removed ? this.Count - 1 : this.Count;
            return removed;
        }

        public void RemoveAt(int index)
        {
            if (index < 0 || index >= this.Count)
            {
                throw new ArgumentOutOfRangeException(nameof(index));
            }

            var nodeToRemove = this.head;
            for (var i = 0; i <= index; ++i)
            {
                nodeToRemove = nodeToRemove.NextNodes[0];
            }

            var level = nodeToRemove.Level;
            var nodesToUpdate = new Node[level];
            for (var i = 0; i < level; ++i)
            {
                var current = this.head;
                for (var j = 0; j < index; ++j)
                {
                    current = current.NextNodes[0];
                }

                nodesToUpdate[i] = current;
            }

            for (var i = 0; i < level; ++i)
            {
                nodesToUpdate[i].NextNodes[i] = nodeToRemove.NextNodes[i];
            }
        }

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
