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

#define STRECORDS 7
#define CRRECORDS 35

using namespace std;

void markDeletedStudent(Student& student) {
	student.setId("0000");
	student.setName("0000");
	student.setDepartment("0000");
	student.setYear(0);
}

void markDeletedCourse(CourseRegistration& course) {
	course.setCourseName("0000");
	course.setStudentId("0000");
	course.setGrade(0);
}

void getKey(const char* sid, const char* courseName, char* at) {
	strcpy(at, sid);
	strcat(at, courseName);
}

int createStudentDataFile(RecordFile<Student>& dataFile, char* filename) {
	Student students[STRECORDS] = {
		{"s123", "KilDong Hong", "Computer", 4}, {"s124", "KilSun Hong", "Electronics", 4},
		{"s125", "ChulSoo Kim", "Computer", 2}, {"s126", "YeongHee Kim", "Computer", 1},
		{"s127", "KukJeong Lim", "Electronics", 3}, {"s128", "MongRyong Lee", "Electronics", 3},
		{"s129", "ChunHyang Seong", "Computer", 4}
	};
	int recaddr = 0;
	int result = dataFile.Open(filename, ios::in | ios::out);
	if (!result)
	{
		cout << "Unable to open data file" << endl;
		dataFile.Close();
		return -1;
	}
	for (int i = 0; i < STRECORDS; ++i) {
		recaddr = dataFile.Write(students[i]);
		cout << "DataFile R[" << i << "] at recaddr " << recaddr << endl;
	}
	dataFile.Close();
	return 0;
}
int createCourseDataFile(RecordFile<CourseRegistration>& dataFile, char* filename) {
	CourseRegistration courses[CRRECORDS] = {
		{"s123", "OS", 4.5}, {"s123", "DB", 4.0}, {"s123", "CPP", 4.0}, {"s123", "AI", 3.5}, {"s123", "Big Data", 3.5},
		{"s124", "C Programming", 4.0}, {"s124", "Data Structure", 4.0}, {"s124", "OS", 3.5}, {"s124", "AI", 3.0}, {"s124", "Web Programming", 3.5},
		{"s125", "DB", 3.5}, {"s125", "Network", 4.0}, {"s125", "OS", 4.0}, {"s125", "Big Data", 3.5}, {"s125", "File Structure", 4.5},
		{"s126", "AI", 3.0}, {"s126", "File Structure", 4.0}, {"s126", "Data Structure", 3.5}, {"s126", "C Programming", 4.5}, {"s126", "CPP", 4.0},
		{"s127", "CPP", 4.5}, {"s127", "Web Programming", 4.5}, {"s127", "Big Data", 4.5}, {"s127", "File Structure", 4.5}, {"s127", "DB", 4.5},
		{"s128", "OS", 4.5}, {"s128", "DB", 3.5}, {"s128", "CPP", 3.5}, {"s128", "Network", 3.5}, {"s128", "Web Programming", 3.0},
		{"s129", "File Structure", 4.0}, {"s129", "Data Structure", 4.0}, {"s129", "CPP", 4.5}, {"s129", "AI", 3.5}, {"s129", "DB", 4.5}
	};
	int recaddr = 0;
	int result = dataFile.Open(filename, ios::in | ios::out);
	if (!result)
	{
		cout << "Unable to open data file" << endl;
		dataFile.Close();
		return -1;
	}
	for (int i = 0; i < CRRECORDS; ++i) {
		recaddr = dataFile.Write(courses[i]);
		cout << "DataFile R[" << i << "] at recaddr " << recaddr << endl;
	}
	dataFile.Close();
	return 0;
}

template <class Data>
int dataFileWithStdInput(RecordFile<Data>& dataFile, char* filename) {
	int count = 0;
	int recaddr = 0;
	Data dataElem;
	int result = dataFile.Open(filename, ios::in | ios::out);
	if (!result)
	{
		cout << "Unable to open data file" << endl;
		dataFile.Close();
		return -1;
	}
	while (1) {
		cin >> dataElem;
		if (dataElem.getId()[0] == '\0') {
			break;
		}
		recaddr = dataFile.Write(dataElem);
		cout << "DataFile R[" << count++ << "] at recaddr " << recaddr << endl;
	}
	dataFile.Close();
	return 0;
}

template <class Data>
int createHashFile(RecordFile<Data>& dataFile, Directory& Dir,  char* dataFilename, char* hashFilename) {
	int recaddr = 0;
	Data dataElem;
	int result = dataFile.Open(dataFilename, ios::in | ios::out);
	if (!result)
	{
		cout << "Unable to open data file" << endl;
		return -1;
	}
	result = Dir.Open(hashFilename);
	if (result == 0)
	{
		cout << "Please create " << hashFilename << ".dir and " << hashFilename <<".bkt" << endl;
		return -1;
	}

	dataFile.Rewind();
	while (1) {
		recaddr = dataFile.Read(dataElem);
		if (recaddr == -1) break;
		char* keys = dataElem.Key();
		cout << "Inserting with key = " << keys << endl;
		cout << (void*)Hash(keys);//(void*) castingÀº bit string
		cout << endl << endl << keys << "  " << (void*)MakeAddress(keys, 16) << endl << endl;
		result = Dir.Insert(keys, recaddr);
		if (result == 0) cout << "Insert for " << keys << " failed" << endl;
		Dir.Print(cout);
		putchar('\n');
	}
	dataFile.Close();
	Dir.Close();
	cout << endl;
	return 0;
}

int printCourseGrades(RecordFile<Student>& stDataFile, RecordFile<CourseRegistration>& crDataFile, Directory& Dir,
	char* studentDataFilename, char* studentHashFilename, char* courseDataFilename, char* courseHashFilename, const char courseList[][20]) {
	Student student;
	CourseRegistration course;
	int recaddr = 0;
	int result = stDataFile.Open(studentDataFilename, ios::in);
	if (!result)
	{
		cout << "Unable to open student data file" << endl;
		return -1;
	}
	result = Dir.Open(studentHashFilename);
	if (result == 0)
	{
		cout << "Please create " << studentHashFilename << ".dir and " << studentHashFilename << ".bkt" << endl;
		return -1;
	}
	char inputKey[30];
	cout << "Insert student id to search : ";
	cin >> inputKey;
	recaddr = Dir.Search(inputKey);
	if (recaddr == -1) {
		cout << "Found no matching key with " << inputKey << endl;
		return -1;
	}
	stDataFile.Read(student, recaddr);
	stDataFile.Close();
	Dir.Close();
	cout.setf(ios::left, ios::adjustfield);
	cout << '\n' << setw(5) << student.getId() << setw(17) << student.getName() << setw(10) <<
		student.getDepartment() << setw(2) << student.getYear() << endl;

	result = crDataFile.Open(courseDataFilename, ios::in);
	if (!result)
	{
		cout << "Unable to open course data file" << endl;
		return -1;
	}
	result = Dir.Open(courseHashFilename);
	if (result == 0)
	{
		cout << "Please create " << courseHashFilename << ".dir and " << courseHashFilename << ".bkt" << endl;
		return -1;
	}
	for (int i = 0; i < 10; ++i) {
		getKey(student.getId(), courseList[i], inputKey);
		recaddr = Dir.Search(inputKey);
		if (recaddr < 0) continue;
		crDataFile.Read(course, recaddr);
		cout.setf(ios::left, ios::adjustfield);
		cout << "      " << setw(18) << course.getCourseName();
		cout.setf(ios::left, ios::fixed | ios::floatfield);
		cout << setw(5) << setprecision(2) << course.getGrade() << endl;
	}

	crDataFile.Close();
	Dir.Close();
	return 0;
}

int unregisterCourse(RecordFile<CourseRegistration>& crDataFile, Directory& Dir, char* courseDataFilename, char* courseHashFilename) {
	char sidInput[5], courseInput[20], keyToDelete[25];
	int result = 0, recaddr = 0;
	CourseRegistration course;
	cout << "Input student id to delete : ";
	cin >> sidInput;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << "Input course name to delete : ";
	cin.getline(courseInput, 20, '\n');
	getKey(sidInput, courseInput, keyToDelete);
	result = crDataFile.Open(courseDataFilename, ios::in | ios::out);
	if (!result)
	{
		cout << "Unable to open course data file" << endl;
		return -1;
	}
	result = Dir.Open(courseHashFilename);
	if (result == 0)
	{
		cout << "Please create " << courseHashFilename << ".dir and " << courseHashFilename << ".bkt" << endl;
		return -1;
	}
	recaddr = Dir.Search(keyToDelete);
	if (recaddr == -1) {
		cout << "Found no matching key with " << keyToDelete << endl;
		return -1;
	}
	crDataFile.Read(course, recaddr);
	cout << course << "Deleted" << endl;
	markDeletedCourse(course);
	crDataFile.Write(course, recaddr);
	Dir.Remove(keyToDelete);
	crDataFile.Close();
	Dir.Close();
	return 0;
}

template <class Data>
int printRecordData(RecordFile<Data>& dataFile, char* filename) {
	int recaddr = 0;
	Data dataElem;
	int result = dataFile.Open(filename, ios::in | ios::out);
	if (!result)
	{
		cout << "Unable to open " << filename << endl;
		return -1;
	}
	dataFile.Rewind();
	while(true)
	{
		recaddr = dataFile.Read(dataElem);
		if (recaddr < 0) break;
		if (strcmp(dataElem.getId(), "0000") == 0) continue;
		cout << dataElem << endl;
	}
	dataFile.Close();
}

int main(int argc, char** argv)
{
	int select, result, end = 1;
	const char courseList[10][20] = {
	{"DB"}, {"OS"}, {"File Structure"}, {"Data Structure"},
	{"CPP"}, {"C Programming"}, {"Network"},
	{"Web Programming"}, {"AI"}, {"Big Data"}
	};
	char* studentDataFileName = "studentDataFile.dat";
	char* courseDataFileName = "courseDataFile.dat";
	char* studentHashFileName = "studenthash";
	char* courseHashFileName = "coursehash";
	Directory Dir(4);
	result = Dir.Create(studentHashFileName);
	Dir.Close();
	result = Dir.Create(courseHashFileName);
	Dir.Close();

	FixedFieldBuffer stBuffer(4);
	Student::InitBuffer(stBuffer);
	FixedFieldBuffer crBuffer(3);
	CourseRegistration::InitBuffer(crBuffer);

	RecordFile<Student> stDataFile(stBuffer);
	RecordFile<CourseRegistration> crDataFile(crBuffer);

	result = stDataFile.Create(studentDataFileName, ios::in | ios::out);
	cout << "Create studentDataFile" << endl;
	if (!result)
	{
		cout << "Unable to Create file : " << studentDataFileName << endl;
		return 0;
	}
	stDataFile.Close();
	result = crDataFile.Create(courseDataFileName, ios::in | ios::out);
	cout << "Create courseDataFile" << endl;
	if (!result)
	{
		cout << "Unable to Create file : " << courseDataFileName << endl;
		return 0;
	}
	crDataFile.Close();
	while (end)
	{
		cout << "\nSelect command 1: insert student record set, 2: insert course registration record set, 3. create a hash file from an student record file,"<<
			"4. create a hash file from an course registration record file, 5. print all course grades that match the input Sid, 6. delete a course registration record with input SId and course name, "
			<<"7. print the course registration record set, 8. Quit => ";
		cin >> select;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch (select) {
			case 1:{//input data record set
				//dataFileWithStdInput(stDataFile, studentDataFileName);
				createStudentDataFile(stDataFile, studentDataFileName);
				break;
			case 2://
				//dataFileWithStdInput(crDataFile, courseDataFileName);
				createCourseDataFile(crDataFile, courseDataFileName);
				break;
			}
			case 3:{
				createHashFile(stDataFile, Dir, studentDataFileName, studentHashFileName);
				break;
			}
			case 4:{
				createHashFile(crDataFile, Dir, courseDataFileName, courseHashFileName);
				break;
			}
			case 5:{
				printCourseGrades(stDataFile, crDataFile, Dir, studentDataFileName, studentHashFileName,
					courseDataFileName, courseHashFileName, courseList);
				break;
			}
			case 6:{
				unregisterCourse(crDataFile, Dir, courseDataFileName, courseHashFileName);
				break;
			}
			case 7:{
				printRecordData(crDataFile, courseDataFileName);
				break;
			}
			case 8: {
				end = 0;
				break;
			}
			default:{
				//exit(0);
				cout << select << " is a wrong input" << endl;
				break;
			}
		}
	}
	system("pause");
	return 1;
}