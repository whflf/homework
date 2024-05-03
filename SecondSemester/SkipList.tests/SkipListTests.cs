namespace SkipList.tests
{
    using SkipList;
    public class SkipListTests
    {
        private SkipList<string>? list = new SkipList<string>();

        public static 
            (string[] TestSimpleAdding, 
            string[] TestDuplicateAdding, 
            string[] TestSimpleRemoving, 
            string[] TestRemovingAt, 
            string[] TestCopyingTo) 
            TestCases =
        (
            TestSimpleAdding: new string[] { "apple", "banana", "cucumber" },
            TestDuplicateAdding: new string[] { "apple", "banana", "banana", "cucumber" },
            TestSimpleRemoving: new string[] { "apple", "banana", "cucumber" },
            TestRemovingAt: new string[] { "apple", "banana" },
            TestCopyingTo: new string[] { "pineapple", "pear", "apple", "banana", "cucumber" }
        );

        [Test]
        public void TestSimpleAdding()
        {
            this.list = new SkipList<string>();

            this.list.Add("apple");
            this.list.Add("cucumber");
            this.list.Add("banana");

            var index = 0;
            foreach (var item in list)
            {
                Assert.That(item, Is.EqualTo(TestCases.TestSimpleAdding[index++]));
            }
        }

        [Test]
        public void TestDuplicateAdding()
        {
            this.list = ["apple", "banana", "cucumber"];
            this.list.Add("banana");

            var index = 0;
            foreach (var item in list)
            {
                Assert.That(item, Is.EqualTo(TestCases.TestDuplicateAdding[index++]));
            }
        }

        [Test]
        public void TestSimpleRemoving()
        {
            this.list = ["apple", "banana", "banana", "cucumber"];
            Assert.That(this.list.Remove("banana"), Is.True);

            var index = 0;
            foreach (var item in list)
            {
                Assert.That(item, Is.EqualTo(TestCases.TestSimpleRemoving[index++]));
            }
        }

        [Test]
        public void TestRemovingAt()
        {
            this.list = ["apple", "banana", "cucumber"];
            this.list.RemoveAt(2);

            var index = 0;
            foreach (var item in list)
            {
                Assert.That(item, Is.EqualTo(TestCases.TestRemovingAt[index++]));
            }
        }

        [Test]
        public void TestClearing()
        {
            this.list = ["apple", "banana", "cucumber"];
            this.list.Clear();

            Assert.That(this.list.Count, Is.EqualTo(0));
        }

        [Test]
        public void RemovingFromEmptyList()
        {
            this.list = new SkipList<string>();
            Assert.That(this.list.Remove("banana"), Is.False);
            Assert.That(this.list.Count, Is.EqualTo(0));
        }

        [Test]
        public void TestSearching()
        {
            this.list = new SkipList<string>();

            this.list.Add("apple");
            this.list.Add("banana");
            this.list.Add("cucumber");

            Assert.That(this.list.IndexOf("banana"), Is.EqualTo(1));
        }

        [Test]
        public void TestCopyingTo()
        {
            this.list = ["apple", "banana", "cucumber"];

            var array = new string[] { "pineapple", "pear", "dragonfruit", "peach", "watermelon" };
            this.list.CopyTo(array, 2);

            var index = 0;
            foreach (var item in array)
            {
                Assert.That(item, Is.EqualTo(TestCases.TestCopyingTo[index++]));
            }
        }
    }
}
