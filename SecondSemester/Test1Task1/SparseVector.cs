// <copyright file="SparseVector.cs" company="PlaceholderCompany">
// Copyright (c) PlaceholderCompany. All rights reserved.
// </copyright>

namespace Test1Task1;

/// <summary>
/// A sparse vector, vector which may be very large but contains mostly zeros.
/// </summary>
public class SparseVector
{
    public readonly Dictionary<int, int> vector = new Dictionary<int, int>();

    /// <summary>
    /// Initializes a new instance of the <see cref="SparseVector"/> class.
    /// </summary>
    /// <param name="inputList">The list which is used to create the vector with given values and indexes.</param>
    /// /// <param name="size">The vector's size.</param>
    public SparseVector(List<Tuple<int, int>> inputList, int size)
    {
        this.Size = size;
        foreach (var element in inputList)
        {
            this.vector[element.Item1] = element.Item2;
        }
    }

    private enum ArithmeticOperation
    {
        Addition,
        Subtraction,
    }

    /// <summary>
    /// Represents the size of the vector.
    /// </summary>
    public int Size { get; private set; }

    /// <summary>
    /// Checks if the sparse vector is zero or not.
    /// </summary>
    /// <returns>True if zero, otherwise false.</returns>
    public bool IsZero()
    {
        return this.vector.Count == 0;
    }

    /// <summary>
    /// Adds the elements of two sparse vectors.
    /// </summary>
    /// <param name="summand">The sparse vector to add to the current.</param>
    /// <returns>A new vector obtained by addition of the two given vectors.</returns>
    /// <exception cref="DifferentSizesException">Thrown when the vectors have different number of elements.</exception>
    public SparseVector Add(SparseVector summand)
    {
        if (this.Size != summand.Size)
        {
            throw new DifferentSizesException();
        }

        return this.AddOrSubtract(summand, ArithmeticOperation.Addition);
    }

    /// <summary>
    /// Subtracts the elements of two sparse vectors.
    /// </summary>
    /// <param name="summand">The sparse vector to subtract from the current.</param>
    /// <returns>A new vector obtained by subtraction of the two given vectors.</returns>
    /// <exception cref="DifferentSizesException">Thrown when the vectors have different number of elements.</exception>
    public SparseVector Subtract(SparseVector summand)
    {
        if (this.Size != summand.Size)
        {
            throw new DifferentSizesException();
        }

        return this.AddOrSubtract(summand, ArithmeticOperation.Subtraction);
    }

    /// <summary>
    /// Gets the scalar multiplication of the two vectors result.
    /// </summary>
    /// <param name="multiplier">The sparse vector to multiply with.</param>
    /// <returns>The number which represents the result of scalar multiplication of the two vectors.</returns>
    /// <exception cref="DifferentSizesException">Thrown when the vectors have different number of elements.</exception>
    public int Multiply(SparseVector multiplier)
    {
        if (this.Size != multiplier.Size)
        {
            throw new DifferentSizesException();
        }

        var result = 0;

        foreach (var item in this.vector)
        {
            if (!multiplier.vector.ContainsKey(item.Key))
            {
                continue;
            }

            result += item.Value * multiplier.vector[item.Key];
        }

        return result;
    }

    private SparseVector AddOrSubtract(SparseVector anotherVector, ArithmeticOperation operation)
    {
        var resultVector = new SparseVector();
        resultVector.Size = this.Size;

        for (var i = 0; i < this.Size; ++i)
        {
            var inThis = this.vector.ContainsKey(i);
            var inAnother = anotherVector.vector.ContainsKey(i);

            if (!inThis && !inAnother)
            {
                continue;
            }

            if (inThis ^ inAnother)
            {
                resultVector.vector[i] = inThis ? this.vector[i] : anotherVector.vector[i];
                continue;
            }

            switch (operation)
            {
                case ArithmeticOperation.Addition:
                    resultVector.vector[i] = this.vector[i] + anotherVector.vector[i];
                    break;
                case ArithmeticOperation.Subtraction:
                    resultVector.vector[i] = this.vector[i] - anotherVector.vector[i];
                    break;
            }
        }

        return resultVector;
    }
}