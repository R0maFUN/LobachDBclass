#include "database.h"
#include "IO.h"
#include <algorithm>
#include <fstream>
//#include <iostream>
//using namespace std;


enum KEYS {
	name,
	phone,
	email,
	salary,
	managerName,
	managerPhone,
	date
};

ELEMENT::ELEMENT(string Data , int ID)
{
	vector<string>* parsed = ParseString(Data);
	this->name = (*parsed)[KEYS::name];
	this->phone = (*parsed)[KEYS::phone];
	this->email = (*parsed)[KEYS::email];
	this->salary = StringToInt((*parsed)[KEYS::salary]);
	this->managerName = (*parsed)[KEYS::managerName];
	this->managerPhone = (*parsed)[KEYS::managerPhone];
	this->date = (*parsed)[KEYS::date];
	this->id = ID;
}

unsigned int ELEMENT::GetId()
{
	return id;
}

string ELEMENT::GetName()
{
	return name;
}

string ELEMENT::GetPhone()
{
	return phone;
}

string ELEMENT::GetEmail()
{
	return email;
}

int ELEMENT::GetSalary()
{
	return salary;
}

string ELEMENT::GetManagerName()
{
	return managerName;
}

string ELEMENT::GetManagerPhone()
{
	return managerPhone;
}

string ELEMENT::GetDate()
{
	return date;
}



void ELEMENT::ChangePhone(string newPhone)
{
	this->phone = newPhone;
}

void ELEMENT::ChangeEmail(string newEmail)
{
	this->email = newEmail;
}

void ELEMENT::ChangeSalary(int newSalary)
{
	this->salary = newSalary;
}

void ELEMENT::ChangeManager(string newManager)
{
	this->managerName = newManager;
}

void ELEMENT::ChangeManagerPhone(string newManagerPhone)
{
	this->managerPhone = newManagerPhone;
}


void ELEMENT::PrintConsole()
{
	cout << name << " " << phone << " " << email << " " << salary << " " << managerName << " " << managerPhone << " " << date << " " << endl;
}

void ELEMENT::PrintFile(fstream * out)
{
	*out << name << " " << phone << " " << email << " " << salary << " " << managerName << " " << managerPhone << " " << date << " " << endl;
}

bool ELEMENT::operator==(ELEMENT second)
{
	if (name != second.name || email != second.email || phone != second.phone || salary != second.salary || managerName != second.managerName || managerPhone != second.managerPhone || date != second.date)
		return false;
	return true;
}

TABLE::TABLE(vector<ELEMENT*> _elements)
{
	for (int i = 0; i < _elements.size(); ++i)
		elements.push_back(_elements[i]);
	size = elements.size();
	maxsize = elements.max_size();
}

TABLE::TABLE(string filename)
{
	vector<string>* Data = ParseFile(filename);
	for (int i = 0; i < Data->size(); ++i)
	{
		ELEMENT* test = new ELEMENT((*Data)[i] , i);
		elements.push_back(test);
	}
}

ELEMENT* TABLE::FindElementByName(string name)
{
	for (int i = 0; i < elements.size(); ++i)
		if ( (elements[i])->GetName() == name)
			return elements[i];
	return NULL;
}

ELEMENT* TABLE::FindElementById(unsigned int ID)
{
	for (int i = 0; i < elements.size(); ++i)
		if ((elements[i])->GetId() == ID)
			return elements[i];
	return NULL;
}

ELEMENT* TABLE::FindElementByPhone(string phone)
{
	for (int i = 0; i < elements.size(); ++i)
		if ((elements[i])->GetPhone() == phone)
			return elements[i];
	return NULL;
}

void TABLE::ChangePhoneById(unsigned int id, string newPhone)
{
	ELEMENT* tmp = FindElementById(id);
	tmp->ChangePhone(newPhone);
}

void TABLE::ChangeEmailById(unsigned int id, string newEmail)
{
	ELEMENT* tmp = FindElementById(id);
	tmp->ChangeEmail(newEmail);
}

void TABLE::ChangeSalaryById(unsigned int id, int newSalary)
{
	ELEMENT* tmp = FindElementById(id);
	tmp->ChangeSalary(newSalary);
}

void TABLE::ChangeManagerById(unsigned int id, string newManager)
{
	ELEMENT* tmp = FindElementById(id);
	tmp->ChangeManager(newManager);
}

void TABLE::ChangeManagerPhoneById(unsigned int id, string newManagerPhone)
{
	ELEMENT* tmp = FindElementById(id);
	tmp->ChangeManagerPhone(newManagerPhone);
}



void TABLE::AddElement()
{
	string inp;
	cout << "Enter the data about element" << endl;
	cin.get();
	getline(cin, inp);
	// isCorrect();
	ELEMENT* p = new ELEMENT(inp , elements.size());
	elements.push_back(p);
}

void TABLE::DeleteElementByName(string name)
{
	int i = 0;
	for (i = 0; i < elements.size(); ++i)
		if ((elements[i])->GetName() == name)
			break;
	elements.erase(elements.begin() + i);
}

void TABLE::DeleteElementByPhone(string phone)
{
	int i = 0;
	for (i = 0; i < elements.size(); ++i)
		if ((elements[i])->GetPhone() == phone)
			break;
	elements.erase(elements.begin() + i);
}

void TABLE::DeleteElementById(unsigned int ID)
{
	int i = 0;
	for (i = 0; i < elements.size(); ++i)
		if ((elements[i])->GetId() == ID)
		{
			elements.erase(elements.begin() + i);
			break;
		}
}

void TABLE::DeleteAllCopies(ELEMENT element)
{
	for (int i = 0; i < elements.size(); ++i)
	{
		if ( *(elements[i]) == element)
		{
			elements.erase(elements.begin() + i);
			--i;
		}
	}
}

void TABLE::ChangeElement(unsigned int id, ELEMENT* newElement)
{
	ELEMENT* tmp = FindElementById(id);
	tmp = newElement;
}

void TABLE::Sort(int byType)
{
	switch (byType)
	{
	case 1:
		sort(elements.begin(), elements.end(), SortByName);
		break;
	case 2:
		sort(elements.begin(), elements.end(), SortByEmail);
		break;
	case 4:
		sort(elements.begin(), elements.end(), SortByMName);
		break;
	default:
		sort(elements.begin(), elements.end(), SortById);
		break;
	}
}

void TABLE::PrintIntoFile(string filename)
{
	fstream out(filename);
	for (int i = 0; i < elements.size(); ++i)
	{
		ELEMENT* element = elements[i];
		element->PrintFile(&out);
	}
}

void TABLE::PrintIntoConsole()
{
	for (int i = 0; i < elements.size(); ++i)
	{
		ELEMENT* element = elements[i];
		element->PrintConsole();
	}
}

bool SortByName(ELEMENT* a, ELEMENT* b)
{
	return a->GetName() < b->GetName();
}

bool SortById(ELEMENT* a, ELEMENT* b)
{
	return a->GetId() < b->GetId();
}

bool SortByEmail(ELEMENT* a, ELEMENT* b)
{
	return a->GetEmail() < b->GetEmail();
}

bool SortByMName(ELEMENT* a, ELEMENT* b)
{
	return a->GetManagerName() < b->GetManagerName();
}
