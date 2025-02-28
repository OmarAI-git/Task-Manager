#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

static string File_Name = "Tasks.txt";

// This function you can put the message as parameter that you want the user to input and retrun the value of input.
string Enter_String(string message)
{
    string input;
    cout << message;
    getline(cin, input);
    return input;
}

//This function to make the string in lower case.
string Make_The_String_Lower(string Task)
{
    for (char &C : Task)
    {
        C = tolower(C);
    }
    return Task;
}

//This function to make the string in upper case.
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

// This function will add anew task as working task.
void Add_Task()
{
    string task = Enter_String("\nPlease, Enter the task: ");

    while (Is_Task_Existing(task))
    {
        task = Enter_String("\nThis task is already exist, Please enter another task: ");
    }

    Save_To_File_Working(task);

    string answer = "no";

    cout << "\nThe task add successfully :-)\n\n";
    cout << "Do you want to add another task (yes,no)? ";
    getline(cin,answer);

    answer = Make_The_String_Lower(answer);
    if(answer == "yes")
    {
        Add_Task();
    }
    else
    {
        cout<<"\n\nThank You :-)\n\n";
    }
}

int main()
{
    Add_Task();
}