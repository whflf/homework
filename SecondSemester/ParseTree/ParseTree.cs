using System;
using System.Collections.Generic;

public class ParseTree
{
    private readonly Operator? root;

    public ParseTree(string stringTree)
    {
        this.root = this.BuildTree(stringTree);
    }

    public double CalculateExpression()
    {
        if (this.root == null)
        {
            throw new IncorrectInputException();
        }

        return this.root.Calculate();
    }

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
        stringTree = stringTree.Replace('(', ' ');
        stringTree = stringTree.Replace(')', ' ');

        var elements = stringTree.Split(' ');
        var subtrees = new Stack<Operator>();

        Operator? currentSubtree = null;
        foreach (var element in elements)
        {
            if (element == string.Empty)
            {
                continue;
            }

            if (subtrees.Count == 0 && currentSubtree is { Right: not null })
            {
                throw new IncorrectInputException();
            }

            if (this.IsOperator(element))
            {
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

                while (currentSubtree.Right != null && subtrees.TryPop(out var oldSubtree))
                {
                    oldSubtree.Update(currentSubtree);
                    currentSubtree = oldSubtree;
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
