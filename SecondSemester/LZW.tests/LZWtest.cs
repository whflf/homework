
[TestFixture]
public class LZWTest
{
    [TestCase("""TestTexts/TestBasic-1.txt""", """TestBasic-1.zipped""")]
    [TestCase("""TestTexts/TestBasic-2.txt""", """TestBasic-2.zipped""")]
    [TestCase("""TestTexts/TestRepeated-1.txt""", """TestTexts\TestRepeated-1.zipped""")]
    [TestCase("""TestTexts/TestRepeated-2.txt""", """TestRepeated-2.zipped""")]
    [TestCase("""TestTexts/TestMixed.txt""", """TestMixed.zipped""")]
    [TestCase("""TestTexts/TestSingleCharacter.txt""", """TestSingleCharacter.zipped""")]
    [TestCase("""TestTexts/TestEmpty.txt""", """TestEmpty.zipped""")]
    [TestCase("""TestTexts/TestLong.txt""", """TestLong.zipped""")]
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
