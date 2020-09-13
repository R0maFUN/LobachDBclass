#include "IO.h"
#include <fstream>

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

vector<string> keys = {
	"name",
	"group",
	"phone",
	"lessonName",
	"teachername",
	"teacherEmail",
	"date",
	"mark"
};

int StringToInt(string str) // conversation string to integer
{
	int i = str.length() - 1;
	int result = 0;
	int exp = 0;
	while (i >= 0)
	{
		result += (str[i] - '0') * pow(10, exp);
		exp++;
		--i;
	}
	return result;
}

bool isDay(string str)
{
	int num = StringToInt(str);
	if (str.size() > 2)
		return false;
	if (num >= 1 && num <= 31)
		return true;
	return false;
}

bool isMonth(string str)
{
	int num = StringToInt(str);
	if (str.size() > 2)
		return false;
	if (num >= 1 && num <= 12)
		return true;
	return false;
}

bool isYear(string str)
{
	int num = StringToInt(str);
	if (str.size() > 4)
		return false;
	if (num >= 1 && num <= 2030)
		return true;
	return false;
}

bool isCorrect(string str, int type)
{
	int i = 0;
	string buf;
	switch (type) {
	case name:
	case lessonName:
	case teacherName:
		while (str[i] != '\0')
		{
			if (!isalpha(str[i]))
				return false;
			++i;
		}
		break;
	case group:
	case phone:
	case mark:
		while (str[i] != '\0')
		{
			if (!isdigit(str[i]))
				return false;
			++i;
		}
		break;
	case teacherEmail:
		while (str[i] != '@' && str[i] != '\0')
		{
			if (!isalpha(str[i]) && !isdigit(str[i]) && str[i] != '.')
				return false;
			++i;
		}
		if (str[i] != '@')
			return false;
		++i;
		while (str[i] != '.' && str[i] != '\0')
		{
			if (!isalpha(str[i]))
				return false;
			++i;
		}
		if (str[i] != '.')
			return false;
		++i;
		while (str[i] != '\0')
		{
			if (!isalpha(str[i]))
				return false;
			++i;
		}
		break;
	case date:
		while (str[i] != '.')
		{
			buf.push_back(str[i]);
			++i;
		}
		if (!isDay(buf))
			return false;
		buf.clear();
		++i;
		while (str[i] != '.')
		{
			buf.push_back(str[i]);
			++i;
		}
		if (!isMonth(buf))
			return false;
		buf.clear();
		++i;
		while (str[i] != '\0')
		{
			buf.push_back(str[i]);
			++i;
		}
		if (!isYear(buf))
			return false;
		break;
	default:
		return false;
	}
	return true;
}

vector<string>* ParseString(string str)
{
	vector<string>* result = new vector<string>;
	int i = 0;
	string buf;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] != ' ')
			buf.push_back(str[i]);
		else
		{
			result->push_back(buf);
			buf.clear();
		}

		++i;
	}
	if (buf.length() > 0)
	{
		result->push_back(buf);
		buf.clear();
	}
	return result;
}

bool isCorrectString(string str)
{
	vector<string>* parsed = ParseString(str);
	for (int i = 0; i < parsed->size(); ++i)
		if (!isCorrect((*parsed)[i], i))
			return false;
	return true;
}

vector<string>* ParseFile(string filename)
{
	fstream in(filename);
	string line;
	vector<string>* result = new vector<string>;
	while (getline(in, line))
	{
		if (isCorrectString(line))
			result->push_back(line);
	}
	return result;
}

/*
void PrintStudent(STUDENT* student)
{
	cout << student->name << " " << student->group << " " << student->phone << " " << student->lessonName << " " << student->teacherName << " " << student->teacherEmail << " " << student->date << " " << student->mark << endl;

}

void PrintIntoFile(string filename, vector<STUDENT*>* students)
{
	fstream out(filename);
	for (int i = 0; i < students->size(); ++i)
	{
		STUDENT* student = (*students)[i];
		out << student->name << " " << student->group << " " << student->phone << " " << student->lessonName << " " << student->teacherName << " " << student->teacherEmail << " " << student->date << " " << student->mark << endl;
	}
}
*/