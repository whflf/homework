
[TestFixture]
public class LZWTest
{
    [TestCase("""TestBasic-1.txt""", """TestBasic-1.zipped""")]
    [TestCase("""TestBasic-2.txt""", """TestBasic-2.zipped""")]
    [TestCase("""TestTexts\TestRepeated-1.txt""", """TestTexts\TestRepeated-1.zipped""")]
    [TestCase("""TestRepeated-2.txt""", """TestRepeated-2.zipped""")]
    [TestCase("""TestMixed.txt""", """TestMixed.zipped""")]
    [TestCase("""TestSingleCharacter.txt""", """TestSingleCharacter.zipped""")]
    [TestCase("""TestEmpty.txt""", """TestEmpty.zipped""")]
    [TestCase("""TestLong.txt""", """TestLong.zipped""")]
    [Test]
    public void TestDifferentTexts(string fileName, string zippedFileName)
    {
        var oldContent = File.ReadAllText(fileName);

        LZW.Compress(fileName, zippedFileName);
        LZW.Uncompress(zippedFileName, fileName);

        var newContent = File.ReadAllText(fileName);
        File.Delete(zippedFileName);

        Assert.That(oldContent, Is.EqualTo(newContent));
    }
}
