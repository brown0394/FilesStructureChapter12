// tsthash.cpp

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
	int count, select, resultFile, resultIndex;
	int recaddr[20], recaddrSearched;
	char removeKey[15], searchKey[15];
	Directory Dir(4);
	resultIndex = Dir.Create("tsthash");
	Recording record, * rec;
	FixedFieldBuffer Buffer(10);
	Buffer.InitFields(); // Add each field size of record to buffer (can change if you need)
	RecordFile<Recording> DataFile(Buffer);

	resultFile = DataFile.Create("datafile.dat", ios::in | ios::out);
	cout << "Create file " << resultFile << endl;


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
	while (1)
	{
		cout << "\nSelect command 1: insert record set, 2. delete a record, 3. print the record set, 4. search the record with key, 5. Quit => ";
		cin >> select;

		switch (select) {
		case 1://input data record set
			cout << "1. insert the record set" << endl;
			for (int i = 0; i < 10; i++)
			{

				cout << (void*)Hash(keys);//(void*) castingÀº bit string
				cout << endl << endl << keys << "  " << (void*)MakeAddress(keys, 16) << endl << endl;
				resultIndex = Dir.Insert(keys, recaddr[i]);

			}
			Dir.Close();
			DataFile.Close();
			break;
		case 2://2. delete a record - 
			resultFile = DataFile.Open("datafile.dat", ios::in | ios::out);

			resultIndex = Dir.Open("tsthash");

			DataFile.Close();
			Dir.Close();
			break;

		case 3://3. print the record set
			resultFile = DataFile.Open("datafile.dat", ios::in | ios::out);

			DataFile.Close();

			break;

		case 4://4. print the record with key
			resultFile = DataFile.Open("datafile.dat", ios::in | ios::out);

			resultIndex = Dir.Open("tsthash");


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