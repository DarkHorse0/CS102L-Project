#include<iostream>
#include<fstream>

using namespace std;

class Course {
	string name;
	string no;
	int creditHours;
	char grade;

public:
	friend class Student;
};

class Student {
	string name;
	int studentID;
	bool isTuitionPaid;
	int numberOfCourses;
	Course* courses;

public:
	Student() {}
	Student()
	{
		name = n;
		studentID = sID;
		isTuitionPaid = iTP;
		numberOfCourses = nOC;
		courses = new Course[nOC];
	}

	~Student()
	{
		delete courses;
	}

	void Write()
	{
		ofstream ofile("StudentRecords.txt");
		ofile << name << " " << studentID << " " << isTuitionPaid << " " << numberOfCourses << endl;

		for (int i = 0; i < numberOfCourses; i++)
		{
			ofile << courses[i].name << " " << courses[i].no << " " << courses[i].creditHours << " " << courses[i].grade << endl;
		}
	}
};

int main()
{
	ifstream record("StudentRecords.txt");
	int noOfStudents;
	double tuitionRate;
	record >> noOfStudents >> tuitionRate;
	cout << noOfStudents;
	return 0;
}
