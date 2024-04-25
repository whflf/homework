// <copyright file="SimpleCalculator.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace Calculator
{
    using System.ComponentModel;

    /// <summary>
    /// Represents a simple calculator that performs basic arithmetic operations.
    /// </summary>
    public class SimpleCalculator
    {
        /// <summary>
        /// Gets or sets the first operand of the calculator.
        /// </summary>
        [TypeConverter(typeof(DoubleConverter))]
        public double FirstOperand { get; set; } = 0;

        /// <summary>
        /// Gets or sets the second operand of the calculator.
        /// </summary>
        [TypeConverter(typeof(DoubleConverter))]
        public double SecondOperand { get; set; } = double.NegativeInfinity;

        /// <summary>
        /// Gets or sets the operation to be performed by the calculator.
        /// </summary>
        public string Operation { get; set; } = string.Empty;

        /// <summary>
        /// Resets the calculator by clearing operands and operation.
        /// </summary>
        public void Reset()
        {
            this.FirstOperand = 0;
            this.SecondOperand = double.NegativeInfinity;
            this.Operation = string.Empty;
        }

        /// <summary>
        /// Performs a calculation using the current operands and operation.
        /// </summary>
        /// <returns>The result of the calculation.</returns>
        public double Calculate()
        {
            return this.Calculate(this.FirstOperand, this.SecondOperand, this.Operation);
        }

        /// <summary>
        /// Performs a calculation using the specified second operand and operation.
        /// </summary>
        /// <param name="second">The second operand of the calculation.</param>
        /// <param name="operation">The operation to perform.</param>
        /// <returns>The result of the calculation.</returns>
        public double Calculate(double second, string operation)
        {
            return this.Calculate(this.FirstOperand, second, operation);
        }

        /// <summary>
        /// Performs a calculation using the specified operands and operation.
        /// </summary>
        /// <param name="first">The first operand of the calculation.</param>
        /// <param name="second">The second operand of the calculation.</param>
        /// <param name="operation">The operation to perform.</param>
        /// <returns>The result of the calculation.</returns>
        public double Calculate(double first, double second, string operation)
        {
            switch (operation)
            {
                case "+":
                    this.FirstOperand = first + second;
                    break;
                case "-":
                    this.FirstOperand = first - second;
                    break;
                case "*":
                case "×":
                    this.FirstOperand = first * second;
                    break;
                case "/":
                    if (Math.Abs(second) < this.epsilon)
                    {
                        throw new DivideByZeroException();
                    }

                    this.FirstOperand = first / second;
                    break;
                default:
                    throw new ArgumentException("Invalid input operation");
            }

            this.SecondOperand = double.NegativeInfinity;
            this.Operation = string.Empty;

            return this.FirstOperand;
        }

        private readonly double epsilon = Math.Pow(10, -6);
    }
}
