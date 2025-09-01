public class ParseTreeTests
{
    [TestCase("(+ 5 5)", 10)]
    [TestCase("(* (+ 1 1) 2)", 4)]
    [TestCase("(- (* (/ 10 2) 3) 1)", 14)]
    public void TestValidExpression(string stringTree, double result)
    {
        var parseTree = new ParseTree(stringTree);
        Assert.That(stringTree, Is.EqualTo(parseTree.ToString()));
        Assert.That(result, Is.EqualTo(parseTree.CalculateExpression()));
    }

    [Test]
    public void TestEmptyExpression()
    {
        Assert.Throws<IncorrectInputException>(() => new ParseTree(""));
    }

    [TestCase("(^ 2 3)")]
    [TestCase("(* 2 3")]
    [TestCase("* 2 3")]
    [TestCase("* 2 3)")]
    public void TestInvalidExpression(string stringTree)
    {
        Assert.Throws<IncorrectInputException>(() => new ParseTree(stringTree));
    }

    [TestCase("(/ 8 0)")]
    [TestCase("(/ (+ 6 7) (- 8 8))")]
    [TestCase("(- (/ 6 (* 7 0)) 5)")]
    public void TestDivisionByZero(string stringTree)
    {
        Assert.Throws<DivideByZeroException>(() => new ParseTree(stringTree).CalculateExpression());
    }

    [TestCase("2 + 2 * 2")]
    [TestCase("catch me if you can, working on my tan, Salvatore")]
    public void TestNotTree(string stringTree)
    {
        Assert.Throws<IncorrectInputException>(() => new ParseTree(stringTree));
    }
}