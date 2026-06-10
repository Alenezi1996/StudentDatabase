#include "StudentSystem.h"

// ================= LOAD STUDENTS =================

void loadStudents(Student students[], int& count)
{
    ifstream inFile("students.txt");

    count = 0;

    if (!inFile)
    {
        cout << "Error: could not open students.txt\n";
        return;
    }

    while (count < MAX_STUDENTS &&
        inFile >> students[count].firstName
        >> students[count].lastName
        >> students[count].id
        >> students[count].grade)
    {
        count++;
    }

    inFile.close();
}

// ================= GENERATE GRADES =================

void generateGrades(double grades[][ASSIGNMENTS], int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < ASSIGNMENTS; j++)
        {
            grades[i][j] = rand() % 41 + 60;
        }
    }
}

// ================= CALCULATE AVERAGES =================

void calculateAverages(double grades[][ASSIGNMENTS], Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        double total = 0;

        for (int j = 0; j < ASSIGNMENTS; j++)
        {
            total += grades[i][j];
        }

        students[i].grade = total / ASSIGNMENTS;
    }
}

// ================= DISPLAY ALL STUDENT INFO =================

void displayAllStudentInfo(double grades[][ASSIGNMENTS], Student students[], int count)
{
    cout << "\n===== ALL STUDENT INFO =====\n";

    cout << left << setw(8) << "ID"
        << setw(12) << "FName"
        << setw(12) << "LName";

    for (int j = 0; j < ASSIGNMENTS; j++)
    {
        cout << setw(8) << ("A" + to_string(j + 1));
    }

    cout << setw(8) << "AVG" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(8) << students[i].id
            << setw(12) << students[i].firstName
            << setw(12) << students[i].lastName;

        for (int j = 0; j < ASSIGNMENTS; j++)
        {
            cout << setw(8) << grades[i][j];
        }

        cout << fixed << setprecision(1)
            << setw(8) << students[i].grade << endl;
    }
}

// ================= UPDATE ASSIGNMENT =================

void updateAssignment(double grades[][ASSIGNMENTS], Student students[], int count)
{
    int studentID;
    int assignmentNumber;
    double newGrade;
    bool found = false;

    cout << "\nEnter student ID: ";
    cin >> studentID;

    cout << "Enter assignment number 1-5: ";
    cin >> assignmentNumber;

    if (assignmentNumber < 1 || assignmentNumber > ASSIGNMENTS)
    {
        cout << "Invalid assignment number.\n";
        return;
    }

    cout << "Enter new grade: ";
    cin >> newGrade;

    for (int i = 0; i < count; i++)
    {
        if (students[i].id == studentID)
        {
            grades[i][assignmentNumber - 1] = newGrade;
            found = true;
            cout << "Grade updated.\n";
        }
    }

    if (!found)
    {
        cout << "Student not found.\n";
    }
}

// ================= ADD STUDENT =================

void addStudent(Student students[], int& count, double grades[][ASSIGNMENTS])
{
    if (count >= MAX_STUDENTS)
    {
        cout << "Cannot add more students.\n";
        return;
    }

    cout << "\nEnter first name: ";
    cin >> students[count].firstName;

    cout << "Enter last name: ";
    cin >> students[count].lastName;

    cout << "Enter ID: ";
    cin >> students[count].id;

    for (int j = 0; j < ASSIGNMENTS; j++)
    {
        grades[count][j] = rand() % 41 + 60;
    }

    students[count].grade = 0;
    count++;

    cout << "Student added.\n";
}

// ================= SAVE STUDENTS =================

void saveStudents(Student students[], int count)
{
    ofstream outFile("students.txt");

    if (!outFile)
    {
        cout << "Error: could not save file.\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        outFile << students[i].firstName << " "
            << students[i].lastName << " "
            << students[i].id << " "
            << fixed << setprecision(1)
            << students[i].grade << endl;
    }

    outFile.close();

    cout << "Data saved to students.txt\n";
}

// ================= HIGHLIGHT SEARCH =================

void highlightSearch(double grades[][ASSIGNMENTS], Student students[], int count)
{
    int choice;
    int studentID = -1;
    int assignmentNumber = -1;

    cout << "\n1. Highlight Student Row\n";
    cout << "2. Highlight Assignment Column\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter student ID: ";
        cin >> studentID;
    }
    else if (choice == 2)
    {
        cout << "Enter assignment number 1-5: ";
        cin >> assignmentNumber;

        if (assignmentNumber < 1 || assignmentNumber > ASSIGNMENTS)
        {
            cout << "Invalid assignment number.\n";
            return;
        }
    }
    else
    {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "\n===== HIGHLIGHTED TABLE =====\n";

    cout << left << setw(8) << "ID"
        << setw(12) << "FName"
        << setw(12) << "LName";

    for (int j = 0; j < ASSIGNMENTS; j++)
    {
        cout << setw(8) << ("A" + to_string(j + 1));
    }

    cout << setw(8) << "AVG" << endl;

    for (int i = 0; i < count; i++)
    {
        bool highlightRow = (choice == 1 && students[i].id == studentID);

        if (highlightRow)
        {
            cout << "\033[33m";
        }

        cout << left << setw(8) << students[i].id
            << setw(12) << students[i].firstName
            << setw(12) << students[i].lastName;

        for (int j = 0; j < ASSIGNMENTS; j++)
        {
            if (choice == 2 && j == assignmentNumber - 1)
            {
                cout << "\033[33m" << setw(8) << grades[i][j] << "\033[0m";
            }
            else
            {
                cout << setw(8) << grades[i][j];
            }
        }

        cout << fixed << setprecision(1)
            << setw(8) << students[i].grade;

        if (highlightRow)
        {
            cout << "\033[0m";
        }

        cout << endl;
    }
}