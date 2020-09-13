#pragma once
#include <string>
#include <vector>

using namespace std;

class STUDENT{
private:
	unsigned int id;
	string name;
	unsigned int group;
	string phone;
	string lessonName;
	string teacherName;
	string teacherEmail;
	string date;
	int mark;
public:
	STUDENT(string Data , int ID);
	unsigned int GetId();
	string GetName();
	string GetPhone();
	unsigned int GetGroup();
	string GetLessonName();
	string GetTeacherName();
	int GetMark();
	void ChangePhone(string newPhone);
	void ChangeGroup(unsigned int newGroup);
	void ChangeMark(int newMark);
	void PrintConsole();
	void PrintFile(fstream * out);
	bool operator==(STUDENT second);
};

class TABLE
{
private:
	unsigned int maxsize = 20;
	unsigned int size = 0;
	vector<STUDENT*> students;
public:
	TABLE(vector<STUDENT*> _students);
	TABLE(string filename);
	STUDENT* FindStudentByName(string name);
	STUDENT* FindStudentById(unsigned int ID);
	STUDENT* FindStudentByPhone(string phone);
	void ChangePhoneById(unsigned int id, string newPhone);
	void ChangeGroupById(unsigned int id, unsigned int newGroup);
	void ChangeMarkById(unsigned int id, int newMark);
	void AddStudent();
	void DeleteStudentByName(string name);
	void DeleteStudentByPhone(string phone);
	void DeleteStudentById(unsigned int ID);
	void DeleteAllCopies(STUDENT student);
	void ChangeElement(unsigned int id, STUDENT* newStudent);
	void Sort(int byType); // byType = anything - id, 1 - name, 2 - group, 4 - lessonName , 5 - teacherName, 8 - mark
	void PrintIntoFile(string filename);
	void PrintIntoConsole();
};

bool SortByName(STUDENT* a, STUDENT* b);

bool SortById(STUDENT* a, STUDENT* b);

bool SortByGroup(STUDENT* a, STUDENT* b);
bool SortByLName(STUDENT* a, STUDENT* b);

bool SortByTName(STUDENT* a, STUDENT* b);

bool SortByMark(STUDENT* a, STUDENT* b);

