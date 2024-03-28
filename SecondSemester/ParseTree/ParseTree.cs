using System;
using System.Collections.Generic;

/// <summary>
/// Represents a parse tree for mathematical expressions.
/// </summary>
public class ParseTree
{
    private readonly Operator? root;

    /// <summary>
    /// Initializes a new instance of the <see cref="ParseTree"/> class with the specified string representation
    /// of the parse tree.
    /// </summary>
    /// <param name="stringTree">The string representation of the parse tree.</param>
    public ParseTree(string stringTree)
    {
        this.root = this.BuildTree(stringTree);
    }

    /// <summary>
    /// Calculates the result of the expression represented by the parse tree.
    /// </summary>
    /// <returns>The result of the expression.</returns>
    public double CalculateExpression()
    {
        if (this.root == null)
        {
            throw new IncorrectInputException();
        }

        return this.root.Calculate();
    }

    /// <summary>
    /// Returns the string representation of the parse tree.
    /// </summary>
    /// <returns>The string representation of the parse tree.</returns>
    public override string ToString() => this.root == null ? "\n" : this.root.ToString();

    private bool IsOperator(string token)
    {
        switch (token)
        {
            case "+":
            case "-":
            case "*":
            case "/":
                return true;
            default:
                return false;
        }
    }

    private Operator? BuildTree(string stringTree)
    {
        var stringTreeWithoutParentheses = stringTree.Replace("(", string.Empty);
        stringTreeWithoutParentheses = stringTreeWithoutParentheses.Replace(")", string.Empty);

        var elements = stringTreeWithoutParentheses.Split(' ');
        var splitFromOriginal = stringTree.Split(' ');
        var subtrees = new Stack<Operator>();

        Operator? currentSubtree = null;
        for (int i = 0; i < elements.Length; ++i)
        {
            var element = elements[i];

            if (subtrees.Count == 0 && currentSubtree is { Right: not null })
            {
                throw new IncorrectInputException();
            }

            if (this.IsOperator(element))
            {
                if (splitFromOriginal[i] != $"({element}")
                {
                    throw new IncorrectInputException();
                }

                var newSubtree = new Operator(element);
                if (currentSubtree is not null)
                {
                    subtrees.Push(currentSubtree);
                }

                currentSubtree = newSubtree;
            }
            else
            {
                if (currentSubtree is null)
                {
                    throw new IncorrectInputException();
                }

                var operand = new Operand(element);
                currentSubtree.Update(operand);

                var parentheses = string.Empty;
                while (currentSubtree.Right is not null && subtrees.TryPop(out var oldSubtree))
                {
                    parentheses += ')';
                    oldSubtree.Update(currentSubtree);
                    currentSubtree = oldSubtree;
                }

                if (currentSubtree.Right != null)
                {
                    parentheses += ')';
                }

                if (splitFromOriginal[i] != $"{element}{parentheses}")
                {
                    throw new IncorrectInputException();
                }
            }
        }

        return currentSubtree;
    }

    private abstract class Node(string value)
    {
        protected string Value { get; private set; } = value;

        public abstract double Calculate();
    }

    private class Operand(string value) : Node(value)
    {
        public override double Calculate()
        {
            if (!double.TryParse(value, out var result))
            {
                throw new IncorrectInputException();
            }

            return result;
        }

        public override string ToString() => value;
    }

    private class Operator(string value) : Node(value)
    {
        public Node? Left { get; set; }

        public Node? Right { get; set; }

        public override double Calculate()
        {
            if (this.Left == null || this.Right == null)
            {
                throw new IncorrectInputException();
            }

            switch (value)
            {
                case "+":
                    return this.Left.Calculate() + this.Right.Calculate();
                case "-":
                    return this.Left.Calculate() - this.Right.Calculate();
                case "*":
                    return this.Left.Calculate() * this.Right.Calculate();
                case "/":
                    return this.Left.Calculate() / this.Right.Calculate();
                default:
                    throw new IncorrectInputException();
            }
        }

        public override string ToString()
        {
            if (this.Left == null || this.Right == null)
            {
                throw new IncorrectInputException();
            }

            return string.Format($"({value} {this.Left} {this.Right})");
        }

        public void Update(Node element)
        {
            if (this.Right != null)
            {
                throw new IncorrectInputException();
            }

            if (this.Left == null)
            {
                this.Left = element;
            }
            else
            {
                this.Right = element;
            }
        }
    }
}
