#include "StudentSystem.h"

// ================= MAIN =================

int main()
{
    srand(time(0));

    Student students[MAX_STUDENTS];
    double grades[MAX_STUDENTS][ASSIGNMENTS];

    int count = 0;
    int choice;

    loadStudents(students, count);
    generateGrades(grades, count);
    calculateAverages(grades, students, count);

    do
    {
        cout << "\n===== STUDENT GRADE SYSTEM =====\n";
        cout << "1. Display All Student Info\n";
        cout << "2. Update Assignment\n";
        cout << "3. Add Student\n";
        cout << "4. Save to File\n";
        cout << "5. Highlight Student / Assignment\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayAllStudentInfo(grades, students, count);
            break;

        case 2:
            updateAssignment(grades, students, count);
            calculateAverages(grades, students, count);
            displayAllStudentInfo(grades, students, count);
            break;

        case 3:
            addStudent(students, count, grades);
            calculateAverages(grades, students, count);
            displayAllStudentInfo(grades, students, count);
            break;

        case 4:
            saveStudents(students, count);
            break;

        case 5:
            highlightSearch(grades, students, count);
            break;

        case 6:
            cout << "\nGoodbye!\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}