using NUnit.Framework;
using System.Collections;

namespace StackCalculator.tests;

public class CalculatorTest
{
    public static IEnumerable<TestCaseData> Stack()
    {
        yield return new TestCaseData(new ListStack<double>());
        yield return new TestCaseData(new ArrayStack<double>());
    }
    
    [TestCaseSource(nameof(Stack))]
    public void TestBasicOperation(IStack<double> stackType)
    {
        Assert.That(Calculator.CalculateExpression("4 2 -", stackType), Is.EqualTo(2));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestMultipleOperations(IStack<double> stackType)
    {
        Assert.That(Calculator.CalculateExpression("1 2 3 + *", stackType), Is.EqualTo(5));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestComplexExpression(IStack<double> stackType)
    {
        Assert.That(Calculator.CalculateExpression("10 2 / 3 4 * -"), Is.EqualTo(-7));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestLargeNumbers(IStack<double> stackType)
    {
        Assert.That(Calculator.CalculateExpression("99999999 99999999 +", stackType), Is.EqualTo(199999998));
        Assert.That(Calculator.CalculateExpression("1000000 2 /", stackType), Is.EqualTo(500000));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestInvalidInput(IStack<double> stackType)
    {
        Assert.Throws<IncorrectExpressionException>(
            () => Calculator.CalculateExpression("5 + 3", stackType));
        Assert.Throws<IncorrectExpressionException>(
            () => Calculator.CalculateExpression("4 2 * *", stackType));
        Assert.Throws<IncorrectExpressionException>(
            () => Calculator.CalculateExpression("", stackType));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestDivisionByZero(IStack<double> stackType)
    {
        Assert.Throws<DivideByZeroException>(
            () => Calculator.CalculateExpression("10 0 /", stackType));
        Assert.Throws<DivideByZeroException>(
            () => Calculator.CalculateExpression("0 0 /", stackType));
        Assert.Throws<DivideByZeroException>(
            () => Calculator.CalculateExpression("1 1 100000000 / /", stackType));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestEdgeCases(IStack<double> stackType)
    {
        Assert.That(Calculator.CalculateExpression("1", stackType), Is.EqualTo(1));
        Assert.That(Calculator.CalculateExpression("1 1 + 2 2 + +", stackType), Is.EqualTo(6));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestPositiveAndNegativeMix(IStack<double> stackType)
    {
        Assert.That(Calculator.CalculateExpression("-3 4 +", stackType), Is.EqualTo(1));
        Assert.That(Calculator.CalculateExpression("-5 -2 *", stackType), Is.EqualTo(10));
    }

    [TestCaseSource(nameof(Stack))]
    public void TestFloatResult(IStack<double> stackType)
    {
        Assert.That(Calculator.CalculateExpression("10 8 /", stackType), Is.EqualTo(1.25));
        Assert.That(Calculator.CalculateExpression("-9 2 /", stackType), Is.EqualTo(-4.5));
    }
}
