#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;

// ================= DISPLAY =================

void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].assignments[j] << "\t";

        cout << students[i].average << "\t";

        for (int j = 0; j < NUM_COURSES; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
    }
}

// ================= LOAD STUDENTS =================

void loadStudents(Student students[], int& count)
{
    ifstream inFile("Students90.txt");

    count = 0;

    if (!inFile)
    {
        cout << "Error opening Students90.txt\n";
        return;
    }

    while (count < STUDENT_MAX &&
        inFile >> students[count].firstName
        >> students[count].lastName
        >> students[count].id)
    {
        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            inFile >> students[count].assignments[i];
        }

        inFile >> students[count].average;

        for (int i = 0; i < NUM_COURSES; i++)
        {
            inFile >> students[count].courses[i];
        }

        count++;
    }

    inFile.close();
}

// ================= CALCULATE AVERAGE =================

void calculateAverage(Student* s)
{
    double total = 0;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        total += s->assignments[i];
    }

    s->average = total / NUM_ASSIGNMENTS;
}

void calculateAllAverages(Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        calculateAverage(&students[i]);
    }
}

// ================= SEARCH BY COURSE =================

void searchByCourse(Student students[], int count)
{
    string course;
    bool found = false;

    cout << "Enter course code: ";
    cin >> course;

    cout << "\nStudents taking " << course << ":\n";

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (students[i].courses[j] == course)
            {
                cout << students[i].id << " "
                    << students[i].lastName << ", "
                    << students[i].firstName << endl;

                found = true;
            }
        }
    }

    if (!found)
    {
        cout << "No students found for this course.\n";
    }
}

// ================= ASSIGNMENT AVERAGES =================

void showAssignmentAverage(Student students[], int count)
{
    cout << "\n===== ASSIGNMENT AVERAGES =====\n";

    for (int a = 0; a < NUM_ASSIGNMENTS; a++)
    {
        double total = 0;

        for (int i = 0; i < count; i++)
        {
            total += students[i].assignments[a];
        }

        cout << "A" << a + 1 << ": "
            << total / count << endl;
    }
}

// ================= HARDEST ASSIGNMENT =================

void showHardestAssignment(Student students[], int count)
{
    double lowestAverage = 100;
    int hardestAssignment = 0;

    for (int a = 0; a < NUM_ASSIGNMENTS; a++)
    {
        double total = 0;

        for (int i = 0; i < count; i++)
        {
            total += students[i].assignments[a];
        }

        double average = total / count;

        if (average < lowestAverage)
        {
            lowestAverage = average;
            hardestAssignment = a;
        }
    }

    cout << "\nHardest Assignment: A"
        << hardestAssignment + 1
        << " with average "
        << lowestAverage << endl;
}

// ================= COURSE ENROLLMENT =================

void courseEnrollment(Student students[], int count)
{
    string checked[STUDENT_MAX * NUM_COURSES];
    int checkedCount = 0;

    cout << "\n===== COURSE ENROLLMENT =====\n";

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            string course = students[i].courses[j];
            bool alreadyChecked = false;

            for (int k = 0; k < checkedCount; k++)
            {
                if (checked[k] == course)
                {
                    alreadyChecked = true;
                }
            }

            if (!alreadyChecked)
            {
                int total = 0;

                for (int x = 0; x < count; x++)
                {
                    for (int y = 0; y < NUM_COURSES; y++)
                    {
                        if (students[x].courses[y] == course)
                        {
                            total++;
                        }
                    }
                }

                cout << course << ": " << total << endl;

                checked[checkedCount] = course;
                checkedCount++;
            }
        }
    }
}

// ================= SORT BY AVERAGE =================

void sortByAverage(Student students[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (students[j].average > students[i].average)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    displayStudents(students, count);
}

// ================= ADD STUDENT =================

void addStudent(Student students[], int& count)
{
    if (count >= STUDENT_MAX)
    {
        cout << "Student list is full.\n";
        return;
    }

    cout << "Enter first name: ";
    cin >> students[count].firstName;

    cout << "Enter last name: ";
    cin >> students[count].lastName;

    cout << "Enter ID: ";
    cin >> students[count].id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Enter A" << i + 1 << ": ";
        cin >> students[count].assignments[i];
    }

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Enter Course " << i + 1 << ": ";
        cin >> students[count].courses[i];
    }

    calculateAverage(&students[count]);

    count++;

    cout << "Student added.\n";
}

// ================= AT RISK STUDENTS =================

void atRiskStudents(Student students[], int count)
{
    cout << "\n===== AT RISK STUDENTS =====\n";

    bool anyFound = false;

    for (int i = 0; i < count; i++)
    {
        bool hasLowAssignment = false;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            if (students[i].assignments[j] < 50)
            {
                hasLowAssignment = true;
            }
        }

        if (hasLowAssignment &&
            students[i].average >= 50 &&
            students[i].average <= 59)
        {
            cout << students[i].id << " "
                << students[i].lastName << ", "
                << students[i].firstName
                << " Average: " << students[i].average
                << endl;

            anyFound = true;
        }
    }

    if (!anyFound)
    {
        cout << "No at-risk students found.\n";
    }
}

// ================= SAVE STUDENTS =================

void saveStudents(Student students[], int count)
{
    ofstream outFile("Students90.txt");

    if (!outFile)
    {
        cout << "Error saving Students90.txt\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        outFile << students[i].firstName << " "
            << students[i].lastName << " "
            << students[i].id << " ";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            outFile << students[i].assignments[j] << " ";
        }

        outFile << students[i].average << " ";

        for (int j = 0; j < NUM_COURSES; j++)
        {
            outFile << students[i].courses[j] << " ";
        }

        outFile << endl;
    }

    outFile.close();

    cout << "Data saved to Students90.txt\n";
}