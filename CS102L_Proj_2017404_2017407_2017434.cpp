#include<iostream>
#include<fstream>

using namespace std;

class Course{
	string name;
	string no;
	int creditHours;
	char grade;
	
public:
	friend class Student;
};

class Student{
	string name;
	int studentID;
	bool isTuitionPaid;
	int numberOfCourses;
	Course* courses;

public:
	Student() {}
	Student(string n, int sID, bool iTP, int nOC)
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
	cout<<"Changed";
	return 0;
}
