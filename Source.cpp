#include "database.h"
#include "IO.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	system("title DATABASE");
	int pause;
	cout << "Enter the file name" << endl;
	string filename;
	cin >> filename;
	vector<string>* Data = ParseFile(filename);

	vector<STUDENT*> Students;
	for (int i = 0; i < Data->size(); ++i)
	{
		STUDENT* test = new STUDENT((*Data)[i] , i);
		Students.push_back(test);
	}

	TABLE table(Students);
	
	system("cls");
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	system("cls");
	table.AddStudent();
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	table.DeleteStudentById(1);
	system("cls");
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	system("cls");
	table.Sort(1);
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	system("cls");
	table.Sort(5);
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	system("cls");
	STUDENT* student = table.FindStudentById(2);
	student->PrintConsole();
	cout << endl;
	cin >> pause;

	table.ChangeMarkById(0, 3);
	system("cls");
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	return 0;
}