/* chpater 12 extendible hashing HW. 
1. page 563: Programming Project: 20,21,22
2. an existing student record file: RecordFile<Student> StudnetDataFile(Buffer);
  - create data file then close it. By reading data file generate hashed index.
  - 	resultIndex = Dir.Create("studenthash");
  Input at least more than 6 record datas.
3. an existing course registration record file: RecordFile<CourseRegistration> CourseRegistrationDataFile(Buffer);
  - 	resultIndex = Dir.Create("coursehash");
  - create data file then close it. By reading data file generate hashed index.
  - Input class subjects to be matched to the each Sid more than four.
4. Problem 22 prints result like below from the input with Sid. (Repetidely search for Sid input from the subject list)
    s123 KilDong Hong  Computer 3
	      DB  3.0
		  OS  4.0
	s124 KilSunHong  Electronics   4
	      File Structure 3.5
		  Data Structure 4.5
5. course list is consist of DB, OS, File Structure, Data Structure, CPP, C Programming, Network, Web Programming, AI, Big Data
6. Course cancelation is done by getting remove key from CourseRegistration index. Mark the data file as deleted with '0000'. 
    do not print out records which are marked as deleted in Read().
	SId means student id.

class Student {//use this.
	char SId[5]; char SName[14]; char Dept[10];	int SYear;
};
class CourseRegistration {
	char SId[5]; char CourseName[10]; int Grade;
};*/
#include "direct.h"
#include "bucket.h"
#include "hash.h"
#include <conio.h>
#include "recording.h"
#include <fstream>
#include <iomanip>
#include <string>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "buffile.h"
#include "recfile.h"
#include "indbuff.h"
#include "CourseRegistration.h"
#include "student.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
	int result, select, recaddr, count;
	Directory Dir(4);
	result = Dir.Create("studenthash");
	Dir.Close();
	result = Dir.Create("coursehash");
	Dir.Close();

	FixedFieldBuffer stBuffer(4);
	Student::InitBuffer(stBuffer);
	FixedFieldBuffer crBuffer(3);
	CourseRegistration::InitBuffer(crBuffer);

	RecordFile<Student> stDataFile(stBuffer);
	RecordFile<CourseRegistration> crDataFile(crBuffer);

	Student student;
	CourseRegistration course;

	result = stDataFile.Create("studentDataFile.dat", ios::in | ios::out);
	cout << "Create studentDataFile" << endl;
	if (!result)
	{
		cout << "Unable to Create file : studentDataFile.dat" << endl;
		return 0;
	}
	result = crDataFile.Create("courseDataFile.dat", ios::in | ios::out);
	cout << "Create courseDataFile" << endl;
	if (!result)
	{
		cout << "Unable to Create file : courseDataFile.dat" << endl;
		return 0;
	}

	while (1)
	{
		cout << "\nSelect command 1: insert student record set, 2: insert course registration record set, 3. create a hash file from an student record file,"<<
			"4. create a hash file from an course registration record file, 5. print all course grades that match the input Sid, 6. delete a course registration record with input SId and course name, "
			<<"7. print the course registration record set, 8. Quit => ";
		cin >> select;

		switch (select) {
		case 1://input data record set
			count = 0;
			while (1) {
				cin >> student;
				if (student.getId()[0] == '\0') {
					break;
				}
				recaddr = stDataFile.Write(student);
				cout << "StudentDataFile R[" << count++ << "] at recaddr " << recaddr << endl;
			}
			stDataFile.Close();
			break;
		case 2://
			count = 0;
			while (1) {
				cin >> course;
				if (course.getStudentId()[0] == '\0') {
					break;
				}
				recaddr = crDataFile.Write(course);
				cout << "CourseDataFile R[" << count++ << "] at recaddr " << recaddr << endl;
			}
			crDataFile.Close();
			break;

		case 3:
			result = stDataFile.Open("studentDataFile.dat", ios::in);
			if (!result)
			{
				cout << "Unable to open student data file" << endl;
				return 0;
			}
			result = Dir.Open("studenthash");
			if (result == 0)
			{
				cout << "Please create studenthash.dir and studenthash.bkt" << endl;
				return 0;
			}

			stDataFile.Rewind();
			while (1) {
				if (stDataFile.Read(student) == -1) break;
				char* keys = student.Key();
				cout << "Inserting with key = " << keys << endl;
				cout << (void*)Hash(keys);//(void*) castingÀº bit string
				cout << endl << endl << keys << "  " << (void*)MakeAddress(keys, 16) << endl << endl;
				result = Dir.Insert(keys, recaddr);
				if (result == 0) cout << "Insert for " << keys << " failed" << endl;
				Dir.Print(cout);
				putchar('\n');
			}

			stDataFile.Close();
			Dir.Close();
			cout << endl;
			break;

		case 4:
			result = crDataFile.Open("courseDataFile.dat", ios::in);
			if (!result)
			{
				cout << "Unable to open course data file" << endl;
				return 0;
			}
			result = Dir.Open("coursehash");
			if (result == 0)
			{
				cout << "Please create coursehash.dir and coursehash.bkt" << endl;
				return 0;
			}

			crDataFile.Rewind();
			while (1) {
				if (crDataFile.Read(course) == -1) break;
				char* keys = course.Key();
				cout << "Inserting with key = " << keys << endl;
				cout << (void*)Hash(keys);//(void*) castingÀº bit string
				cout << endl << endl << keys << "  " << (void*)MakeAddress(keys, 16) << endl << endl;
				result = Dir.Insert(keys, recaddr);
				if (result == 0) cout << "Insert for " << keys << " failed" << endl;
				Dir.Print(cout);
				putchar('\n');
			}

			crDataFile.Close();
			Dir.Close();
			cout << endl;
			break;
		case 5:

			//DataFile.Close();
			Dir.Close();
			break;
		case 6:

			//DataFile.Close();
			Dir.Close();
			break;
		case 7:

			//DataFile.Close();
			Dir.Close();
			break;
		default:
			exit(0);
			break;
		}
	}
	system("pause");
	return 1;
}