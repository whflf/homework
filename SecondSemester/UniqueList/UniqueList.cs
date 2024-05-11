// <copyright file="UniqueList.cs" company="Elena Makarova">
// Copyright (c) Elena Makarova. All rights reserved.
// </copyright>

namespace UniqueList;

/// <summary>
/// Represents a list that ensures unique elements.
/// </summary>
/// <typeparam name="T">The type of elements in the list.</typeparam>
public class UniqueList<T> : CommonList<T>
{
    /// <inheritdoc/>
    public override void Add(T value)
    {
        if (this.GetIndex(value) != -1)
        {
            throw new RepeatingValueException();
        }

        base.Add(value);
    }

    /// <inheritdoc/>
    public override void Change(T value, int position)
    {
        var index = this.GetIndex(value);
        if (index != -1)
        {
            throw new RepeatingValueException();
        }

        if (index == position)
        {
            return;
        }

        base.Change(value, position);
    }
}
