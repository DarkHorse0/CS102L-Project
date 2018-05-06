#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;


//Struct Definition for Course
struct Course {
	string name;
	string no;
	int creditHours;
	char grade;
};


//Function Prototypes
int gradeValue(char grade);
void manager(double tRate);
string NameSpace(string name);
void BubbleSort(Course c[], int size);


//Class defined for holding Student record data in program
class Student {
	//Class variables
	string name;
	int studentID;
	char isTuitionPaid;
	int numberOfCourses;
	int credits;
	Course* courses;	// Pointer to allow dynamic memory allocation later

public:
	//Destructor to release allocated memory
	~Student()
	{
		delete[] courses;
	}

	//Function to read record data from file. Takes ID as argument, keeps reading from file until it finds a record whose ID matches argument.
	bool read(int ID)
	{
		ifstream ifile("StudentRecords.txt");
		//Read first line of data which doesn't hold student record
		string temp;
		ifile >> temp >> temp;

		//keeps reading until ID matches argument or end of file reached
		while (!ifile.eof())
		{
			ifile >> name >> studentID >> isTuitionPaid >> numberOfCourses;

			name = NameSpace(name);	//Function to separate name from camelCase into string with spaces

			courses = new Course[numberOfCourses + 1];	//Memory dynamically allocated according to number of courses to be read

			credits = 0;
			//loop to read course data into struct array and calculate total credits
			for (int i = 0; i < numberOfCourses; i++)
			{
				ifile >> courses[i].name >> courses[i].no >> courses[i].creditHours >> courses[i].grade;
				credits += courses[i].creditHours;
			}

			//reads lines of . separating student records
			ifile >> temp >> temp >> temp;

			if (ID == studentID)	//Close file and return true if record found
			{
				ifile.close();
				return true;
			}
			else if (ifile.eof())	//Close file and return false if record not found and EOF reached
			{
				ifile.close();
				return false;
			}
			else {					//Delete allocated memory so new memory of appropriate size can be allocated for the next record
				delete[] courses;
			}
		}
	}

	//Function to calculate GPA and return it
	double GPA()
	{
		int gradePoints = 0;
		for (int i = 0; i < numberOfCourses; i++)
		{
			gradePoints += gradeValue(courses[i].grade) * courses[i].creditHours;
		}
		return gradePoints / (float)credits;
	}

	//Function to return total fees
	double feesAmount(double tuition)
	{
		return tuition * credits;
	}

	//Functino to display formatted student grade report
	void display(double tuition)
	{
		cout << "Student Name: " << name << endl;
		cout << "Student ID: " << studentID << endl;
		cout << "Number of courses enrolled : " << numberOfCourses << endl << endl;

		//Displays Grades if tuition paid, message with Pending Fees if not paid
		if (isTuitionPaid == 'Y')
		{
			BubbleSort(courses, numberOfCourses);

			cout << left << setw(15) << "Course No" << setw(15) << "Course Name" << setw(11) << "Credits" << setw(9) << "Grade" << endl;
			for (int i = 0; i < numberOfCourses; i++)
			{
				cout << setw(15) << courses[i].no << setw(18) << courses[i].name << setw(10);
				cout << courses[i].creditHours << setw(9) << courses[i].grade << endl;
			}

			cout << endl << endl;
			cout << "Total No. of credits: " << credits << endl;
			cout << "Mid-semester GPA: " << GPA() << endl;
		}
		else {
			cout << "Due to tuition fees not being paid, result will not be shown." << endl;
			cout << "Pending Fees: " << feesAmount(tuition) << endl;
		}
	}
};




int main()
{
	//Records file opened to read No of Students and Tuition Rate
	ifstream record("StudentRecords.txt");
	int noOfStudents;
	double tuitionRate;
	record >> noOfStudents >> tuitionRate;
	record.close();

	//Function to manage
	manager(tuitionRate);

	return 0;
}

//Function to manage user input, creating object to hold record and displaying
void manager(double tRate)
{
	char choice = 'Y';
	int stID;
	Student std;

	//loop runs until user enters a terminating value
	while (toupper(choice) == 'Y')
	{
		cout << endl << "Enter student ID to display record: ";
		cin >> stID;
		cout << endl;

		//Function in if returns true if ID passed in argument is found in file, false if not
		if (std.read(stID))
		{
			//displays formatted grade report for relevant student
			system("CLS");
			std.display(tRate);
			cout << endl << "Enter Y to see more records. Enter any other key to exit.";
			cin >> choice;
			system("CLS");
		}
		else {
			//asks user to enter different ID
			system("CLS");
			cout << "No record with that ID found. Please enter another ID.";
		}
	}
}


//Function to separate string in CamelCase into string with spaces  
string NameSpace(string name)
{
	string result = "";
	for (int i = 0; i < name.length(); i++)
	{
		//if letter is capital and not first letter then adds a space to final string
		if (i != 0 && name[i] >= 'A' && name[i] <= 'Z')
			result += " ";

		result += name[i];
	}
	return result;
}


//Function that returns a numerical value for the alphabetical grade passed in argument based on given criteria
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

//Function to sort Course array from Student class object in order of course code using BubbleSort Algorithm
void BubbleSort(Course c[], int size)
{
	bool sort = true;

	//outer while loop runs until no sorting operation takes place in inner for loop
	while (sort)
	{
		sort = false;
		//for loop runs over array's indexes except last
		for (int i = 0; i < size - 1; i++)
		{
			//consecutive elements of array are compared and swapped if earlier ones are larger than later ones
			if (c[i].no > c[i + 1].no)
			{
				sort = true;
				//Swapping elements
				Course temp = c[i];
				c[i] = c[i + 1];
				c[i + 1] = temp;
			}
		}
	}

}