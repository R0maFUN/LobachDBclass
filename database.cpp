#include "database.h"
#include "IO.h"
#include <algorithm>
#include <fstream>
//#include <iostream>
//using namespace std;

enum KEYS {
	name,
	group,
	phone,
	lessonName,
	teacherName,
	teacherEmail,
	date,
	mark
};

STUDENT::STUDENT(string Data , int ID)
{
	vector<string>* parsed = ParseString(Data);
	this->name = (*parsed)[KEYS::name];
	this->group = StringToInt((*parsed)[KEYS::group]);
	this->phone = (*parsed)[KEYS::phone];
	this->lessonName = (*parsed)[KEYS::lessonName];
	this->teacherName = (*parsed)[KEYS::teacherName];
	this->teacherEmail = (*parsed)[KEYS::teacherEmail];
	this->date = (*parsed)[KEYS::date];
	this->mark = StringToInt((*parsed)[KEYS::mark]);
	this->id = ID;
}

unsigned int STUDENT::GetId()
{
	return id;
}

string STUDENT::GetName()
{
	return name;
}

string STUDENT::GetPhone()
{
	return phone;
}

unsigned int STUDENT::GetGroup()
{
	return group;
}

string STUDENT::GetLessonName()
{
	return lessonName;
}

string STUDENT::GetTeacherName()
{
	return teacherName;
}

int STUDENT::GetMark()
{
	return mark;
}

void STUDENT::ChangePhone(string newPhone)
{
	this->phone = newPhone;
}

void STUDENT::ChangeGroup(unsigned int newGroup)
{
	this->group = newGroup;
}

void STUDENT::ChangeMark(int newMark)
{
	this->mark = newMark;
}

void STUDENT::PrintConsole()
{
	cout << name << " " << group << " " << phone << " " << lessonName << " " << teacherName << " " << teacherEmail << " " << date << " " << mark << endl;
}

void STUDENT::PrintFile(fstream * out)
{
	*out << name << " " << group << " " << phone << " " << lessonName << " " << teacherName << " " << teacherEmail << " " << date << " " << mark << endl;
}

bool STUDENT::operator==(STUDENT second)
{
	if (name != second.name || group != second.group || phone != second.phone || lessonName != second.lessonName || teacherName != second.teacherName || teacherEmail != second.teacherEmail || date != second.date || mark != second.mark)
		return false;
	return true;
}

TABLE::TABLE(vector<STUDENT*> _students)
{
	for (int i = 0; i < _students.size(); ++i)
		students.push_back(_students[i]);
	size = students.size();
	maxsize = students.max_size();
}

TABLE::TABLE(string filename)
{
	vector<string>* Data = ParseFile(filename);
	for (int i = 0; i < Data->size(); ++i)
	{
		STUDENT* test = new STUDENT((*Data)[i] , i);
		students.push_back(test);
	}
}

STUDENT* TABLE::FindStudentByName(string name)
{
	for (int i = 0; i < students.size(); ++i)
		if ( (students[i])->GetName() == name)
			return students[i];
}

STUDENT* TABLE::FindStudentById(unsigned int ID)
{
	for (int i = 0; i < students.size(); ++i)
		if ((students[i])->GetId() == ID)
			return students[i];
}

STUDENT* TABLE::FindStudentByPhone(string phone)
{
	for (int i = 0; i < students.size(); ++i)
		if ((students[i])->GetPhone() == phone)
			return students[i];
}

void TABLE::ChangePhoneById(unsigned int id, string newPhone)
{
	STUDENT* tmp = FindStudentById(id);
	tmp->ChangePhone(newPhone);
}

void TABLE::ChangeGroupById(unsigned int id, unsigned int newGroup)
{
	STUDENT* tmp = FindStudentById(id);
	tmp->ChangeGroup(newGroup);
}

void TABLE::ChangeMarkById(unsigned int id, int newMark)
{
	STUDENT* tmp = FindStudentById(id);
	tmp->ChangeMark(newMark);
}

void TABLE::AddStudent()
{
	string inp;
	cout << "Enter the data about student" << endl;
	cin.get();
	getline(cin, inp);
	// isCorrect();
	STUDENT* p = new STUDENT(inp , students.size());
	students.push_back(p);
}

void TABLE::DeleteStudentByName(string name)
{
	int i = 0;
	for (i = 0; i < students.size(); ++i)
		if ((students[i])->GetName() == name)
			break;
	students.erase(students.begin() + i);
}

void TABLE::DeleteStudentByPhone(string phone)
{
	int i = 0;
	for (i = 0; i < students.size(); ++i)
		if ((students[i])->GetPhone() == phone)
			break;
	students.erase(students.begin() + i);
}

void TABLE::DeleteStudentById(unsigned int ID)
{
	int i = 0;
	for (i = 0; i < students.size(); ++i)
		if ((students[i])->GetId() == ID)
		{
			students.erase(students.begin() + i);
			break;
		}
}

void TABLE::DeleteAllCopies(STUDENT student)
{
	for (int i = 0; i < students.size(); ++i)
	{
		if ( *(students[i]) == student)
		{
			students.erase(students.begin() + i);
			--i;
		}
	}
}

void TABLE::ChangeElement(unsigned int id, STUDENT* newStudent)
{
	STUDENT* tmp = FindStudentById(id);
	tmp = newStudent;
}

void TABLE::Sort(int byType)
{
	switch (byType)
	{
	case 1:
		sort(students.begin(), students.end(), SortByName);
		break;
	case 2:
		sort(students.begin(), students.end(), SortByGroup);
		break;
	case 4:
		sort(students.begin(), students.end(), SortByLName);
		break;
	case 5:
		sort(students.begin(), students.end(), SortByTName);
		break;
	case 8:
		sort(students.begin(), students.end(), SortByMark);
		break;
	default:
		sort(students.begin(), students.end(), SortById);
		break;
	}
}

void TABLE::PrintIntoFile(string filename)
{
	fstream out(filename);
	for (int i = 0; i < students.size(); ++i)
	{
		STUDENT* student = students[i];
		student->PrintFile(&out);
	}
}

void TABLE::PrintIntoConsole()
{
	for (int i = 0; i < students.size(); ++i)
	{
		STUDENT* student = students[i];
		student->PrintConsole();
	}
}

bool SortByName(STUDENT* a, STUDENT* b)
{
	return a->GetName() < b->GetName();
}

bool SortById(STUDENT* a, STUDENT* b)
{
	return a->GetId() < b->GetId();
}

bool SortByGroup(STUDENT* a, STUDENT* b)
{
	return a->GetGroup() < b->GetGroup();
}

bool SortByLName(STUDENT* a, STUDENT* b)
{
	return a->GetLessonName() < b->GetLessonName();
}

bool SortByTName(STUDENT* a, STUDENT* b)
{
	return a->GetTeacherName() < b->GetTeacherName();
}

bool SortByMark(STUDENT* a, STUDENT* b)
{
	return a->GetMark() < b->GetMark();
}