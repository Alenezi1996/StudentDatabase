#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// ================= CONSTANTS =================

const int MAX_STUDENTS = 23;
const int ASSIGNMENTS = 5;

// ================= STRUCT =================

struct Student
{
    string firstName;
    string lastName;
    int id;
    double grade;
};

// ================= PROTOTYPES =================

void loadStudents(Student students[], int& count);
void generateGrades(double grades[][ASSIGNMENTS], int count);
void calculateAverages(double grades[][ASSIGNMENTS], Student students[], int count);
void displayAllStudentInfo(double grades[][ASSIGNMENTS], Student students[], int count);
void updateAssignment(double grades[][ASSIGNMENTS], Student students[], int count);
void addStudent(Student students[], int& count, double grades[][ASSIGNMENTS]);
void saveStudents(Student students[], int count);
void highlightSearch(double grades[][ASSIGNMENTS], Student students[], int count);