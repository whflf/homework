namespace UniqueList;

internal static class MenuInterface
{
    private enum MenuOption : int
    {
        ExitProgram,
        AddElementToUniqueList,
        RemoveElementFromUniqueList,
        ChangeElementInUniqueList,
    }

    private enum ListChangingOption
    {
        AddElement,
        RemoveElement,
        ChangeElement,
    }

    public static void ProgramLoop(UniqueList<string> list)
    {
        string[] menuOptionNames =
        [
            "Exit program",
            "Add new string to the unique list",
            "Remove a string from the unique list",
            "Change the string in the unique list"
        ];

        while (true)
        {
            Console.Clear();

            Console.WriteLine("Enter an operation code to continue:");
            for (var i = 0; i < menuOptionNames.Length; ++i)
            {
                Console.WriteLine($"  {i} - {menuOptionNames[i]}");
            }

            Console.Write("> ");
            if (!int.TryParse(Console.ReadLine(), out var input))
            {
                Console.WriteLine("Bad input. Please enter a valid operation code.");
                Wait();
                continue;
            }

            switch (input)
            {
                case (int)MenuOption.ExitProgram:
                    Console.WriteLine("Goodbye!");
                    Wait();
                    return;

                case (int)MenuOption.AddElementToUniqueList:
                    ChoiceChangeListContent(list, ListChangingOption.AddElement);
                    break;

                case (int)MenuOption.RemoveElementFromUniqueList:
                    ChoiceChangeListContent(list, ListChangingOption.RemoveElement);
                    break;

                case (int)MenuOption.ChangeElementInUniqueList:
                    ChoiceChangeListContent(list, ListChangingOption.ChangeElement);
                    break;
            }

            Wait();
        }
    }

    private static void Wait()
    {
        Console.WriteLine("Press enter to continue...");
        while (Console.ReadKey().Key != ConsoleKey.Enter);
    }

    private static void ChoiceChangeListContent(UniqueList<string> list, ListChangingOption option)
    {
        Console.WriteLine("Enter the string:");
        var stringValue = Console.ReadLine();
        if (stringValue is null)
        {
            Console.WriteLine("The string value was null.");
            return;
        }

        switch (option)
        {
            case ListChangingOption.ChangeElement:
                Console.WriteLine("Enter the position:");
                if (!int.TryParse(Console.ReadLine(), out var position))
                {
                    Console.WriteLine("Bad input. Please enter a correct integer.");
                    return;
                }

                try
                {
                    list.Change(stringValue, position);
                }
                catch (RepeatingValueException)
                {
                    Console.WriteLine("You cannot have two same values in the unique list.");
                }

                Console.WriteLine("The string was successfully changed in the list.");

                break;
            case ListChangingOption.AddElement:
            case ListChangingOption.RemoveElement:
                try
                {
                    if (option == ListChangingOption.AddElement)
                    {
                        list.Add(stringValue);
                    }
                    else
                    {
                        list.Remove(stringValue);
                    }
                }
                catch (ElementNotFoundException)
                {
                    Console.WriteLine("Element with such value doesn't exists at the list.");
                }
                catch (RepeatingValueException)
                {
                    Console.WriteLine("You cannot have two same values in the unique list.");
                }

                Console.WriteLine(
                    "The string was successfully {0} the list.",
                    option == ListChangingOption.AddElement ? "added to" : "removed from");

                break;
        }
    }
}