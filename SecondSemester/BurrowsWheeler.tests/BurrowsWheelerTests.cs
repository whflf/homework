

[TestFixture]
public class BurrowsWheelerTests
{
    [TestCase("", "", 0)]
    [TestCase("a", "a", 0)]
    [TestCase("banana", "nnbaaa", 3)]
    [TestCase("aaaaaa", "aaaaaa", 0)]
    [TestCase("the quick brown fox jumps over the lazy dog", "kynxeserl i hhv ottu c uwd rfm ebp gqjoooza", 35)]
    [TestCase("12345", "51234", 0)]
    [TestCase("abc123!@#", "3@c12!#ab", 6)]
    [TestCase("абракадабра", "рдакраааабб", 2)]
    public void TestDifferentStrings(string given, string expected, int position)
    {
        var afterTransform = given;
        var result = BurrowsWheeler.TransformStringAndGetPosition(ref given);
        Assert.That(given, Is.EqualTo(expected));
        Assert.That(result, Is.EqualTo(position));

        BurrowsWheeler.DetransformString(ref given, result);
        Assert.That(given, Is.EqualTo(afterTransform));
    }
}
