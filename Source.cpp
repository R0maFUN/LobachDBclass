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
	string filename = "testDB.txt";
	//cin >> filename;
	vector<string>* Data = ParseFile(filename);

	vector<ELEMENT*> Elements;
	for (int i = 0; i < Data->size(); ++i)
	{
		ELEMENT* test = new ELEMENT((*Data)[i] , i);
		Elements.push_back(test);
	}


	TABLE table(Elements);
	
	system("cls");
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	//system("cls");
	table.AddElement();
	table.PrintIntoConsole();
	cout << endl;
	cout << endl << "New element was added" << endl;
	cin >> pause;

	table.DeleteElementById(1);
	system("cls");
	cout << endl << "Element with id(1) was deleted" << endl;
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	system("cls");
	cout << "Sort by name: " << endl;
	table.Sort(1);
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	system("cls");
	cout << "Sort by id: " << endl;
	table.Sort(0);
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	system("cls");
	cout << "found element id(2): ";
	ELEMENT* element = table.FindElementById(2);
	element->PrintConsole();
	cout << endl;
	cin >> pause;

	table.ChangePhoneById(2, string("70000000000"));
	system("cls");
	cout << "Element id(2) changed phone:" << endl;
	table.PrintIntoConsole();
	cout << endl;
	cin >> pause;

	return 0;
}