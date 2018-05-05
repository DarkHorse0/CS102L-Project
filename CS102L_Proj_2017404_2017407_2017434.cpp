// CS102L Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

int gradeValue(char grade);
void manager(double tRate);
string NameSpace(string name);

struct Course {
	string name;
	string no;
	int creditHours;
	char grade;
};

class Student {
	string name;
	int studentID;
	char isTuitionPaid;
	int numberOfCourses;
	int credits;
	Course* courses;
	bool memory;

public:
	Student() {}

	~Student()
	{
		delete[] courses;
	}

	void read(int ID)
	{
		ifstream ifile("StudentRecords.txt");
		string temp;
		ifile >> temp >> temp;
		memory = false;
		while (ID != studentID && !ifile.eof())
		{
			ifile >> name >> studentID >> isTuitionPaid >> numberOfCourses;

			name = NameSpace(name);

			if (!memory)
			{
				courses = new Course[numberOfCourses + 1];
				memory = true;
			}

			credits = 0;

			for (int i = 0; i < numberOfCourses; i++)
			{
				ifile >> courses[i].name >> courses[i].no >> courses[i].creditHours >> courses[i].grade;
				credits += courses[i].creditHours;
			}
		}
		ifile.close();
	}

	double GPA()
	{
		int gradePoints = 0;
		for (int i = 0; i < numberOfCourses; i++)
		{
			gradePoints += gradeValue(courses[i].grade) * courses[i].creditHours;
		}
		return gradePoints / (float)credits;
	}

	double feesAmount(double tuition)
	{
		return tuition * credits;
	}

	void display(double tuition)
	{
		cout << "Student Name: " << name << endl;
		cout << "Student ID: " << studentID << endl;
		cout << "Number of courses enrolled : " << numberOfCourses << endl << endl;

		cout << left << setw(15) << "Course No" << setw(15) << "Course Name" << setw(11) << "Credits" << setw(9) << "Grade" << endl;

		for (int i = 0; i < numberOfCourses; i++)
		{
			cout << setw(15) << courses[i].no << setw(18) << courses[i].name << setw(10) << courses[i].creditHours << setw(9) << courses[i].grade << endl;
		}

		cout << endl << endl;

		if (isTuitionPaid == 'Y')
		{
			cout << "Total No. of credits: " << credits << endl;
			cout << "Mid-semester GPA: " << GPA() << endl;
		}
		else {
			cout << "Due to tuition fees not being paid, result will not be shown." << endl;
			cout << "Bill: " << feesAmount(tuition) << endl;
		}
	}
};

string NameSpace(string name)
{
	string result = "";
	for (int i = 0; i < name.length(); i++)
	{
		if (i != 0 && name[i] >= 'A' && name[i] <= 'Z')
			result += " ";

		result += name[i];
	}
	return result;
}

int gradeValue(char grade)
{
	switch (grade)
	{
	case 'A':
		return 4;
		break;
	case 'B':
		return 3;
		break;
	case 'C':
		return 2;
		break;
	case 'D':
		return 1;
		break;
	case 'F':
		return 0;
		break;
	}
}

int main()
{
	ifstream record("StudentRecords.txt");
	int noOfStudents;
	double tuitionRate;
	record >> noOfStudents >> tuitionRate;
	record.close();

	manager(tuitionRate);

	return 0;
}

void manager(double tRate)
{
	char choice = 'Y';
	int stID;
	Student std;
	while (toupper(choice) == 'Y')
	{
		cout << endl << "Enter student ID to display record: ";
		cin >> stID;
		cout << endl;

		std.read(stID);
		std.display(tRate);
		cout << endl << "Enter Y to see more records. Enter any other key to exit.";
		cin >> choice;
		system("CLS");
	}
}