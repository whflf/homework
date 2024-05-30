using NUnit.Framework;
using StackCalculator;

namespace StackCalculator.tests;

public class CalculatorTest
{
    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestBasicOperation(StackType stackType)
    {
        Assert.That(Calculator.CalculateExpression("4 2 -", stackType), Is.EqualTo(2));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestMultipleOperations(StackType stackType)
    {
        Assert.That(Calculator.CalculateExpression("1 2 3 + *", stackType), Is.EqualTo(5));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestComplexExpression(StackType stackType)
    {
        Assert.That(Calculator.CalculateExpression("10 2 / 3 4 * -"), Is.EqualTo(-7));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestLargeNumbers(StackType stackType)
    {
        Assert.That(Calculator.CalculateExpression("99999999 99999999 +", stackType), Is.EqualTo(199999998));
        Assert.That(Calculator.CalculateExpression("1000000 2 /", stackType), Is.EqualTo(500000));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestInvalidInput(StackType stackType)
    {
        Assert.Throws<IncorrectExpressionException>(
            () => Calculator.CalculateExpression("5 + 3", stackType));
        Assert.Throws<IncorrectExpressionException>(
            () => Calculator.CalculateExpression("4 2 * *", stackType));
        Assert.Throws<IncorrectExpressionException>(
            () => Calculator.CalculateExpression("", stackType));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestDivisionByZero(StackType stackType)
    {
        Assert.Throws<DivideByZeroException>(
            () => Calculator.CalculateExpression("10 0 /", stackType));
        Assert.Throws<DivideByZeroException>(
            () => Calculator.CalculateExpression("0 0 /", stackType));
        Assert.Throws<DivideByZeroException>(
            () => Calculator.CalculateExpression("1 1 100000000 / /", stackType));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestEdgeCases(StackType stackType)
    {
        Assert.That(Calculator.CalculateExpression("1", stackType), Is.EqualTo(1));
        Assert.That(Calculator.CalculateExpression("1 1 + 2 2 + +", stackType), Is.EqualTo(6));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestPositiveAndNegativeMix(StackType stackType)
    {
        Assert.That(Calculator.CalculateExpression("-3 4 +", stackType), Is.EqualTo(1));
        Assert.That(Calculator.CalculateExpression("-5 -2 *", stackType), Is.EqualTo(10));
    }

    [TestCase(StackType.ListStack)]
    [TestCase(StackType.ArrayStack)]
    public void TestFloatResult(StackType stackType)
    {
        Assert.That(Calculator.CalculateExpression("10 8 /", stackType), Is.EqualTo(1.25));
        Assert.That(Calculator.CalculateExpression("-9 2 /", stackType), Is.EqualTo(-4.5));
    }
}
