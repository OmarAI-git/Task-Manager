#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

static string File_Name = "Tasks.txt";
void Start_Program();

// I use enum for the option.
enum enMainMenuOption
{
    Add_Function = 1,
    Delete_Function = 2,
    Show_Function = 3,
    Check_Function = 4,
    Clear_Function = 5,
    Exist_Function = 6
};
enum enMainShowOption
{
    Working_Tasks = 1,
    Done_Tasks = 2,
    Back_To_Menu = 3
};
enum enMainClear
{
    Clear_Working_Tasks = 1,
    Clear_Done_Tasks = 2,
    Clear_All_Tasks = 3,
    Back = 4
};

// This function you can put the message as parameter that you want the user to input and retrun the value of input.
string Enter_String(string message)
{
    string input;
    cout << message;
    cin.sync(); // Flush the input buffer
    getline(cin, input);
    return input;
}

// This function to make the string in lower case.
string Make_The_String_Lower(string Task)
{
    for (char &C : Task)
    {
        C = tolower(C);
    }
    return Task;
}

// This function to make the string in upper case.
string Make_The_String_Upper(string Task)
{
    for (char &C : Task)
    {
        C = toupper(C);
    }
    return Task;
}

// This function will return the Working tasks from file as vector of string.
vector<string> Load_The_Working_Tasks_From_File()
{
    vector<string> vWorkingTasks;

    fstream File;
    File.open(File_Name, ios::in); // read mode

    if (File.is_open())
    {
        string line;
        while (getline(File, line))
        {
            string prefix = "working#//#";
            if (line.find(prefix) == 0)
            {
                line = line.substr(prefix.length());
                vWorkingTasks.push_back(line);
            }
        }
        File.close();
    }
    return vWorkingTasks;
}

// This function will give the task the mode (working) or (done).
string Task_Mode(string Task, string Mode = "working") // The default value here I put working but you can put any thing you want.
{
    string Line_Note = Mode + "#//#";
    Line_Note = Line_Note + Task;
    return Line_Note;
}

// This function will check if the task existing in the file or not.
bool Is_Task_Existing(string task)
{
    vector<string> vTasks;
    vTasks = Load_The_Working_Tasks_From_File();

    for (string Single_Note : vTasks)
    {
        if (Single_Note == task)
        {
            return true;
        }
    }
    return false;
}

// This function is for add the new task as working task to file.
void Save_To_File_Working(string New_Task)
{
    fstream File;
    File.open(File_Name, ios::app); // add without clear all file.

    if (File.is_open())
    {
        string line;
        line = Task_Mode(New_Task);
        File << line << endl;
        File.close();
    }
}

void Add_Screen()
{
    cout << "\t\t\t==================================\n";
    cout << "\t\t\t\tAdd Screen\n";
    cout << "\t\t\t==================================\n";
}

// This function will add anew task as working task.
void Add_Task()
{
    system("cls");

    Add_Screen();

    string task = Enter_String("\nPlease, Enter the task: ");

    while (Is_Task_Existing(task))
    {
        task = Enter_String("\nThis task is already exist, Please enter another task: ");
    }

    Save_To_File_Working(task);

    string answer = "no";

    cout << "\nThe task add successfully :-)\n\n";
    cout << "Do you want to add another task (yes,no)? ";
    getline(cin, answer);

    answer = Make_The_String_Lower(answer);
    if (answer == "yes")
    {
        Add_Task();
    }
    else
    {
        cout << "\n\nThank You :-)\n\n";
    }
}

// Function to get valid user input
int getUserInput()
{
    int num;
    while (!(cin >> num))
    {
        cin.sync();          // Check if input fails
        cin.clear();         // Clear error state
        cin.ignore(100, '\n'); // Discard invalid input
        cout << "\nInvalid input! Please enter a number: ";
    }
    return num;
}

// Main Menu
int menu()
{
    cout << "\nTask Manager\n"
         << "____________\n"
         << "1) Add.\n"
         << "2) Delete.\n"
         << "3) Show.\n"
         << "4) Check.\n"
         << "5) Clear.\n"
         << "6) Exit.\n"
         << "____________\n"
         << "Enter your choice: ";
    return getUserInput();
}

// Show Menu
int show_menu()
{
    cout << "\nShow Tasks\n"
         << "___________________\n"
         << "1) Working Tasks\n"
         << "2) Done Tasks\n"
         << "3) Back to the menu\n"
         << "___________________\n"
         << "Enter your choice: ";
    return getUserInput();
}

// Clear Menu
int clear_menu()
{
    cout << "\nClear Tasks\n"
         << "______________________\n"
         << "1) Clear Working Tasks\n"
         << "2) Clear Done Tasks\n"
         << "3) Clear All Tasks\n"
         << "4) Back to the menu\n"
         << "______________________\n"
         << "Enter your choice: ";
    return getUserInput();
}

void Back_To_Main_Menu()
{
    system("cls"); // I use this code to clear the screen.
    Start_Program();
}
// This function will change the 'working' task to 'done' task based on user request.
void check()
{
    system("cls"); // to clear the screen.

    while (true)
    {
        int c = 0, userChoice = -9999;
        string content, line;
        cout << "****************************" << endl;
        cout << "These are the \'Working\' task\n\n";
        for (auto task : Load_The_Working_Tasks_From_File())
        { // print all the 'working' tasks
            c++;
            cout << c << ") " + task + "\n";
        }

        cout << "****************************" << endl;
        cout << "\nPlease enter the completed task: ";
        cin >> userChoice;
        string userTask = Load_The_Working_Tasks_From_File()[userChoice - 1];
        fstream File;
        File.open(File_Name, ios::in); // Read mode
        while (getline(File, line))
        {                                            // This loop's for copying all the content of the file EXCEPT the user choice word.
            if (line.find(userTask) == string::npos) // if the word isn't found
                content += line + "\n";
            else
            {
                line = Task_Mode(userTask, "done"); // convert the word to "done"
                content += line + "\n";
            }
        }
        File.close();
        File.open(File_Name, ios::out); // Write mode
        File << content << endl;
        File.close();
        // Ask the user if he wanna do it again
        string answer = "no";
        cout << "Congratulations!! you have completed the " + userTask + " task!\n";
        cout << "\nDo you have another task completed? (yes/no)\n>> ";
        cin >> answer;
        if (answer == "no")
            cout << "\n\nThank You :-)\n\n";
        break;
    }
}

// This code will run and call all function.
void Start_Program()
{
    short choice = menu();
    switch (choice)
    {
    case (enMainMenuOption::Add_Function):
    {
        Add_Task();
        Back_To_Main_Menu();
        break;
    }
    case (enMainMenuOption::Delete_Function):
    {
        system("cls");
        cout << "\n\nThe Delete Function must be here.";
        system("pause>0");
        Back_To_Main_Menu();
        break;
    }
    case (enMainMenuOption::Show_Function):
    {
        short option = show_menu();
        switch (option)
        {
        case (enMainShowOption::Working_Tasks):
        {
            cout << "Show Working Tasks must be here.";
            system("pause>0");
            Back_To_Main_Menu();
            break;
        }
        case (enMainShowOption::Done_Tasks):
        {
            cout << " Show Done Tasks must be here.";
            system("pause>0");
            Back_To_Main_Menu();
            break;
        }
        case (enMainShowOption::Back_To_Menu):
        {
            cout << "Back To Main menu function must be here.";
            system("pause>0");
            Back_To_Main_Menu();
            break;
        }
        }
    }
    case (enMainMenuOption::Check_Function):
    {
        check();
        system("pause>0");
        Back_To_Main_Menu();
        break;
    }
    case (enMainMenuOption::Clear_Function):
    {
        short option = clear_menu();
        switch (option)
        {
        case (enMainClear::Clear_Working_Tasks):
        {
            cout << "Clear Working Task function must be here.";
            system("pause>0");
            Back_To_Main_Menu();
            break;
        }
        case (enMainClear::Clear_Done_Tasks):
        {
            cout << "Clear Done Task function must be here.";
            system("pause>0");
            Back_To_Main_Menu();
            break;
        }
        case (enMainClear::Clear_All_Tasks):
        {
            cout << "Clear All Task function must be here.";
            system("pause>0");
            Back_To_Main_Menu();
            break;
        }
        case (enMainClear::Back):
        {
            cout << "Back To Main menu function must be here.";
            system("pause>0");
            Back_To_Main_Menu();
            break;
        }
        }
    }
    case (enMainMenuOption::Exist_Function):
    {
        system("cls");
        cout << "\n\nThank you for using our program :-)\n\n";
        system("pause>0");
        break;
    }

    default:
    {
        system("cls");
        Start_Program();
    }
    }
}

int main()
{
    Start_Program();
}
