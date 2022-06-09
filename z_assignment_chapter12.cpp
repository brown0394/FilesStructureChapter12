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
*/
class Student {//use this.
	char SId[5]; char SName[14]; char Dept[10];	int SYear;
};
class CourseRegistration {
	char SId[5]; char CourseName[10]; int Grade;
};
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
#include <iostream>
using namespace std;


int main(int argc, char** argv)
{
	/* This comment for reference. to be deleted.
	int count, select, resultFile, resultIndex;
	int recaddr[20], recaddrSearched;
	char removeKey[15], searchKey[15];
	Directory Dir(4);
	resultIndex = Dir.Create("tsthash");
	Recording record, * rec;
	FixedFieldBuffer Buffer(10);
	Buffer.InitFields(); // Add each field size of record to buffer (can change if you need)
	RecordFile<Recording> DataFile(Buffer);
	Recording* R[10];
	R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[2] = new Recording("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording("BOL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording("EG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	*/
	while (1)
	{
		cout << "\nSelect command 1: insert student record set, 2: insert course registration record set, 3. create a hash file from an student record file,"<<
			"4. create a hash file from an course registration record file, 5. print all course grades that match the input Sid, 6. delete a course registration record with input SId and course name, "
			<<"7. print the course registration record set, 8. Quit => ";
		cin >> select;

		switch (select) {
		case 1://input data record set

			Dir.Close();
			DataFile.Close();
			break;
		case 2://

			Dir.Print(cout);
			DataFile.Close();
			Dir.Close();
			break;

		case 3:

			DataFile.Close();
			cout << endl;
			break;

		case 4:

			DataFile.Close();
			Dir.Close();
			break;
		case 5:

			DataFile.Close();
			Dir.Close();
			break;
		case 6:

			DataFile.Close();
			Dir.Close();
			break;
		case 7:

			DataFile.Close();
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