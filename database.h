#pragma once
#include <string>
#include <vector>

using namespace std;


class ELEMENT{
private:
	unsigned int id;
	string name;
	string phone;
	string email;
	int salary;
	string managerName;
	string managerPhone;
	string date;
public:
	ELEMENT(string Data , int ID);
	unsigned int GetId();
	string GetName();
	string GetPhone();
	string GetEmail();
	int GetSalary();
	string GetManagerName();
	string GetManagerPhone();
	string GetDate();
	void ChangePhone(string newPhone);
	void ChangeEmail(string newEmail);
	void ChangeSalary(int newSalary);
	void ChangeManager(string newManager);
	void ChangeManagerPhone(string newManagerPhone);
	void PrintConsole();
	void PrintFile(fstream * out);
	bool operator==(ELEMENT second);
};

class TABLE
{
private:
	unsigned int maxsize = 20;
	unsigned int size = 0;
	vector<ELEMENT*> elements;
public:
	TABLE(vector<ELEMENT*> _elements);
	TABLE(string filename);
	ELEMENT* FindElementByName(string name);
	ELEMENT* FindElementById(unsigned int ID);
	ELEMENT* FindElementByPhone(string phone);
	void ChangePhoneById(unsigned int id, string newPhone);
	void ChangeEmailById(unsigned int id, string newEmail);
	void ChangeSalaryById(unsigned int id, int newSalary);
	void ChangeManagerById(unsigned int id, string newManager);
	void ChangeManagerPhoneById(unsigned int id, string newManagerPhone);
	void AddElement();
	void DeleteElementByName(string name);
	void DeleteElementByPhone(string phone);
	void DeleteElementById(unsigned int ID);
	void DeleteAllCopies(ELEMENT element);
	void ChangeElement(unsigned int id, ELEMENT* newElement);
	void Sort(int byType); // byType = anything - id, 1 - name, 2 - email, 4 - managerName
	void PrintIntoFile(string filename);
	void PrintIntoConsole();
};

bool SortByName(ELEMENT* a, ELEMENT* b);

bool SortById(ELEMENT* a, ELEMENT* b);

bool SortByEmail(ELEMENT* a, ELEMENT* b);
bool SortByMName(ELEMENT* a, ELEMENT* b);


