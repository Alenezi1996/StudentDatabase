#include "Student.h"
#include <iostream>

using namespace std;

// ================= MAIN =================

int main()
{
    Student students[STUDENT_MAX];

    int count = 0;
    int choice;

    loadStudents(students, count);
    calculateAllAverages(students, count);

    do
    {
        cout << "\n========== STUDENT DATABASE ==========\n";
        cout << "1. Display Students\n";
        cout << "2. Search By Course\n";
        cout << "3. Assignment Averages\n";
        cout << "4. Hardest Assignment\n";
        cout << "5. Course Enrollment\n";
        cout << "6. Sort By Average\n";
        cout << "7. Add Student\n";
        cout << "8. At Risk Students\n";
        cout << "9. Save Students\n";
        cout << "10. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            displayStudents(students, count);
            break;

        case 2:
            searchByCourse(students, count);
            break;

        case 3:
            showAssignmentAverage(students, count);
            break;

        case 4:
            showHardestAssignment(students, count);
            break;

        case 5:
            courseEnrollment(students, count);
            break;

        case 6:
            sortByAverage(students, count);
            break;

        case 7:
            addStudent(students, count);

            saveStudents(students, count);

            loadStudents(students, count);

            calculateAllAverages(students, count);

            displayStudents(students, count);
            break;

        case 8:
            atRiskStudents(students, count);
            break;

        case 9:
            saveStudents(students, count);
            break;

        case 10:
            cout << "\nGoodbye!\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 10);

    return 0;
}