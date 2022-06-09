#include "CourseRegistration.h"
#include <strstream>
#include <iomanip>

CourseRegistration::CourseRegistration() :SId{ "\0" }, 
CourseName{ "\0" }, Grade{0}
{
}

CourseRegistration::CourseRegistration(const CourseRegistration& course) {
	strcpy_s(this->SId, SIDMAX, course.SId);
	strcpy_s(this->CourseName, CNAMEMAX, course.CourseName);
	this->Grade = course.Grade;
}

CourseRegistration::CourseRegistration(char* studentId, char* courseName, float grade) {
	strcpy_s(this->SId, SIDMAX, studentId);
	strcpy_s(this->CourseName, CNAMEMAX, courseName);
	this->Grade = grade;
}
CourseRegistration::~CourseRegistration() {
}

CourseRegistration& CourseRegistration::operator =(const CourseRegistration& course) {
	strcpy_s(this->SId, SIDMAX, course.SId);
	strcpy_s(this->CourseName, CNAMEMAX, course.CourseName);
	this->Grade = course.Grade;
	return *this;
}

void CourseRegistration::setStudentId(const char* id) {
	strcpy_s(this->SId, SIDMAX, id);
}
char* CourseRegistration::getStudentId() {
	return this->SId;
}
void CourseRegistration::setGrade(float grade) {
	this->Grade = grade;
}
float CourseRegistration::getGrade() {
	return this->Grade;
}
void CourseRegistration::setCourseName(const char* courseName) {
	strcpy_s(this->CourseName, CNAMEMAX, courseName);
}
char* CourseRegistration::getCourseName() {
	return this->CourseName;
}


std::ostream& operator << (std::ostream& stream, const CourseRegistration& course) {
	stream << "Student Id : " << course.SId <<
		"\nCourse Name : " << course.CourseName <<
		"\nGrade : " << course.Grade << "\n\n";
	return stream;
}

void checkValid(char *str) {
	for (char* c = str; *c != '\0'; ++c) {
		if (!(isdigit(*c))) {
			if ((*c) == '.') {
				continue;
			}
			str[0] = '0'; str[1] = '\0'; break;
		}
	}
}

std::istream& operator >> (std::istream& stream, CourseRegistration& course) {
	char buffer[10];
	std::cout << "Enter student id, or <cr> to end : " << std::flush;
	stream.getline(buffer, SIDMAX);
	course.setStudentId(buffer);
	if (strlen(course.SId) == 0) return stream;
	std::cout << "Enter course name: " << std::flush; stream.getline(buffer, CNAMEMAX);
	course.setCourseName(buffer);
	std::cout << "Enter course grade: " << std::flush; stream.getline(buffer, 5);
	checkValid(buffer);
	course.setGrade(atof(buffer));
	return stream;
}

int CourseRegistration::InitBuffer(FixedFieldBuffer& Buffer)
// initialize a FixedTextBuffer to be used for Persons
{
	int result;
	result = Buffer.AddField(SIDMAX); // SId;
	result = result && Buffer.AddField(CNAMEMAX); // CourseName;
	result = result && Buffer.AddField(4); // Grade [5];
	return result;
}

void toString(char* str, float fnum) {
	sprintf(str, "%-4.2f", fnum);
}

void CourseRegistration::Clear()
{
	// set each field to an empty string
	SId[0] = 0;
	CourseName[0] = 0;
	Grade = 0;
}

int CourseRegistration::InitBuffer(LengthFieldBuffer& Buffer)
// initialize a LengthTextBuffer to be used for Persons
{
	return TRUE;
}
/*
int CourseRegistration::InitBuffer(DelimFieldBuffer& Buffer)
// initialize a DelimTextBuffer to be used for Persons
{
	return TRUE;
}*/

int CourseRegistration::Pack(IOBuffer& Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(SId);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(CourseName);
	if (numBytes == -1) return FALSE;
	char credit[5];
	toString(credit, Grade);
	numBytes = Buffer.Pack(credit);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int CourseRegistration::Unpack(IOBuffer& Buffer)
{
	Clear();
	int numBytes;
	//power of virtual functions
	numBytes = Buffer.Unpack(SId);
	if (numBytes == -1) return FALSE;
	SId[numBytes] = 0;
	numBytes = Buffer.Unpack(CourseName);
	if (numBytes == -1) return FALSE;
	CourseName[numBytes] = 0;
	char num[5];
	numBytes = Buffer.Unpack(num);
	if (numBytes == -1) return FALSE;
	num[numBytes] = 0;
	Grade = atof(num);

	return TRUE;
}

void getSplittedHalf(const char* str, char* at, char delim) {
	int i = 0;
	for (; i < strlen(str); ++i) {
		if (str[i] == delim) break;
		at[i] = str[i];
	}
}

char* CourseRegistration::Key() const
{// produce key as concatenation of Label and IdNum
	std::ostrstream key;
	char splitName[CNAMEMAX];
	getSplittedHalf(CourseName, splitName, ' ');
	key << SId << splitName << ends;
	return key.str();
}
/*
ostream& CourseRegistration::PrintLine(ostream& stream)
{
	stream.setf(ios::right, ios::adjustfield);
	stream << studentId << '\t';
	stream.setf(ios::right, ios::adjustfield);
	stream << '\t' << setw(6) << courseId << '\t';
	stream.setf(ios::left, ios::adjustfield);
	stream << setw(30) << courseName;
	stream.setf(ios::right, ios::adjustfield);
	stream << '\t' << numberOfCreditHours;
	stream.setf(ios::right | ios::fixed, ios::floatfield);
	stream.precision(2);
	stream << '\t' << setw(8) << setprecision(2) << grade << endl;
	return stream;
}*/