using NUnit.Framework;

namespace StackCalculator.tests
{
    [TestFixture]
    public class CalculatorTests
    {
        [Test]
        public void TestBasicOperation()
        {
            Assert.That(Calculator.CalcExpression("4 2 -"), Is.EqualTo(2));
            Assert.That(Calculator.CalcExpression("4 2 -", StackType.ArrayStack), Is.EqualTo(2));
        }

        [Test]
        public void TestMultipleOperations()
        {
            Assert.That(Calculator.CalcExpression("1 2 3 + *"), Is.EqualTo(5));
            Assert.That(Calculator.CalcExpression("1 2 3 + *", StackType.ArrayStack), Is.EqualTo(5));
        }

        [Test]
        public void TestComplexExpression()
        {
            Assert.That(Calculator.CalcExpression("10 2 / 3 4 * -"), Is.EqualTo(-7));
            Assert.That(Calculator.CalcExpression("10 2 / 3 4 * -", StackType.ArrayStack), Is.EqualTo(-7));
        }

        [Test]
        public void TestLargeNumbers()
        {
            Assert.That(Calculator.CalcExpression("99999999 99999999 +"), Is.EqualTo(199999998));
            Assert.That(Calculator.CalcExpression("99999999 99999999 +", StackType.ArrayStack), Is.EqualTo(199999998));

            Assert.That(Calculator.CalcExpression("1000000 2 /"), Is.EqualTo(500000));
            Assert.That(Calculator.CalcExpression("1000000 2 /", StackType.ArrayStack), Is.EqualTo(500000));
        }

        [Test]
        public void TestInvalidInput()
        {
            Assert.Throws<IncorrectExpressionException>(() => Calculator.CalcExpression("5 + 3"));
            Assert.Throws<IncorrectExpressionException>(() => Calculator.CalcExpression("5 + 3", StackType.ArrayStack));

            Assert.Throws<IncorrectExpressionException>(() => Calculator.CalcExpression("4 2 * *"));
            Assert.Throws<IncorrectExpressionException>(() => Calculator.CalcExpression("4 2 * *", StackType.ArrayStack));

            Assert.Throws<IncorrectExpressionException>(() => Calculator.CalcExpression(""));
            Assert.Throws<IncorrectExpressionException>(() => Calculator.CalcExpression("", StackType.ArrayStack));
        }

        [Test]
        public void TestDivisionByZero()
        {
            Assert.Throws<DivideByZeroException>(() => Calculator.CalcExpression("10 0 /"));
            Assert.Throws<DivideByZeroException>(() => Calculator.CalcExpression("10 0 /", StackType.ArrayStack));

            Assert.Throws<DivideByZeroException>(() => Calculator.CalcExpression("0 0 /"));
            Assert.Throws<DivideByZeroException>(() => Calculator.CalcExpression("0 0 /", StackType.ArrayStack));

            Assert.Throws<DivideByZeroException>(() => Calculator.CalcExpression("1 1 100000000 / /"));
            Assert.Throws<DivideByZeroException>(() => Calculator.CalcExpression("1 1 100000000 / /", StackType.ArrayStack));
        }

        [Test]
        public void TestEdgeCases()
        {
            Assert.That(Calculator.CalcExpression("1"), Is.EqualTo(1));
            Assert.That(Calculator.CalcExpression("1", StackType.ArrayStack), Is.EqualTo(1));

            Assert.That(Calculator.CalcExpression("1 1 + 2 2 + +"), Is.EqualTo(6));
            Assert.That(Calculator.CalcExpression("1 1 + 2 2 + +", StackType.ArrayStack), Is.EqualTo(6));
        }

        [Test]
        public void TestPositiveAndNegativeMix()
        {
            Assert.That(Calculator.CalcExpression("-3 4 +"), Is.EqualTo(1));
            Assert.That(Calculator.CalcExpression("-3 4 +", StackType.ArrayStack), Is.EqualTo(1));

            Assert.That(Calculator.CalcExpression("-5 -2 *"), Is.EqualTo(10));
            Assert.That(Calculator.CalcExpression("-5 -2 *", StackType.ArrayStack), Is.EqualTo(10));
        }

        [Test]
        public void TestFloatResult()
        {
            Assert.That(Calculator.CalcExpression("10 8 /"), Is.EqualTo(1.25));
            Assert.That(Calculator.CalcExpression("10 8 /", StackType.ArrayStack), Is.EqualTo(1.25));

            Assert.That(Calculator.CalcExpression("-9 2 /"), Is.EqualTo(-4.5));
            Assert.That(Calculator.CalcExpression("-9 2 /", StackType.ArrayStack), Is.EqualTo(-4.5));
        }
    }
}

