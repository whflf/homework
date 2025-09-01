// <copyright file="CalculatorTests.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace CalculatorTests
{
    using Calculator;
    using NUnit.Framework;

    /// <summary>
    /// Contains unit tests for the SimpleCalculator class.
    /// </summary>
    [TestFixture]
    public class CalculatorTests
    {
        private SimpleCalculator _calculator = new SimpleCalculator();

        /// <summary>
        /// Tests simple arithmetic operations (+, -, *, /) with integer operands.
        /// </summary>
        /// <param name="first">The first operand.</param>
        /// <param name="second">The second operand.</param>
        /// <param name="operation">The operation to perform.</param>
        /// <param name="expected">The expected result of the operation.</param>
        [TestCase(2, 2, "+", 4)]
        [TestCase(2, 1, "-", 1)]
        [TestCase(3, 3, "*", 9)]
        [TestCase(8, 2, "/", 4)]
        public void TestSimpleOperations(int first, int second, string operation, int expected)
        {
            Assert.That(this._calculator.Calculate(first, second, operation), Is.EqualTo(expected));
            this._calculator.Reset();
        }

        /// <summary>
        /// Tests complex arithmetic operations with integer operands and multiple operations.
        /// </summary>
        /// <param name="first">The first operand.</param>
        /// <param name="second">The second operand.</param>
        /// <param name="third">The third operand.</param>
        /// <param name="operationOne">The first operation to perform.</param>
        /// <param name="operationTwo">The second operation to perform.</param>
        /// <param name="expected">The expected result of the operation.</param>
        [TestCase(2, 2, 2, "+", "-", 2)]
        [TestCase(2, 1, 5, "-", "*", 5)]
        [TestCase(3, 3, 3, "*", "/", 3)]
        [TestCase(8, 2, 3, "/", "+", 7)]
        public void TestComplexOperations(int first, int second, int third, string operationOne, string operationTwo, int expected)
        {
            this._calculator.Calculate(first, second, operationOne);
            Assert.That(this._calculator.Calculate(third, operationTwo), Is.EqualTo(expected));
            this._calculator.Reset();
        }

        /// <summary>
        /// Tests explicit assignment of operands and operation.
        /// </summary>
        [Test]
        public void TestExplicitOperandAssigning()
        {
            this._calculator.FirstOperand = 7;
            this._calculator.SecondOperand = 6;
            this._calculator.Operation = "*";

            Assert.That(this._calculator.Calculate(), Is.EqualTo(42));
            this._calculator.Reset();
        }

        /// <summary>
        /// Tests division by zero scenario.
        /// </summary>
        /// <param name="zero">The zero value for the divisor.</param>
        [TestCase(0)]
        [TestCase(0.000000001)]
        public void TestDivisionByZero(double zero)
        {
            Assert.Throws<DivideByZeroException>(() => this._calculator.Calculate(1, zero, "/"));
            this._calculator.Reset();
        }

        /// <summary>
        /// Tests an invalid operation scenario.
        /// </summary>
        /// <param name="operation">The invalid operation.</param>
        [TestCase("")]
        [TestCase("qwerty")]
        public void TestInvalidOperation(string operation)
        {
            Assert.Throws<ArgumentException>(() => this._calculator.Calculate(1, 1, operation));
            this._calculator.Reset();
        }
    }
}
