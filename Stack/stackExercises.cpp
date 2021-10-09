// stackExcercisez.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
/*
������ 1:

�� ������� ���� ������� ���, ������� �� �� �������� ������ ����� �{�, �}�, �(�, �)�, �[�, �]�, 
��������� ���� �� �� ����������� � ������� ����������� ��������� �� ������.

������:
������ ���: {([)]}              ������ ���: [()]{}{[()({})]()}
��������: Not balanced          ��������: Balanced
*/

bool matchingBrackets(char br1, char br2) {
	return (br1 == '[' && br2 == ']' ||
		br1 == '(' && br2 == ')' ||
		br1 == '{' && br2 == '}');
}

bool isBalanced(std::string str) {
	std::stack<char> s;
	for (int i = 0; i < str.length(); ++i) {

		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			s.push(str[i]);

		}
		if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if (!matchingBrackets(s.top(), str[i]) || s.empty()) return false;
			s.pop();

		}

	}
	return s.empty();
}

void checkExpression(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cout << "Unable to open " << fileName << " file.\n";
		return;
	}

	std::string expression;
	file >> expression;

	file.close();

	isBalanced(expression) ? std::cout << "Balanced\n" : std::cout << "Not balanced\n";
}

/*
������ 2:

�� ������� ���� ������� ���, ������������� �����, ����� ������ �� �� ���������. ���������� �� ���������� � ��������� ��� ������� �(�, �)�. 
���������� �������� ������ �� ���� ������� � ���������� �=� ���� ������������� ��� � ����� ����.

������:
������ ���: (((2*4)-(1*2))/(9-7))
��������:  3
��������, ������� ��� �����: (((2*4)-(1*2))/(9-7)) = 3
*/
/*
������ 3:

�� ������� ���� ������� �������� ���, ����� ������������ ������������� ����� � �������� ���, ���� ���� �� ����������� � ������� ������ ����� - ���������� ��� � �������� ��������� ���. � ��� ������� ���� �� ������� ������ ������� ������ � �������� � ���������� ��� ������ � ��������� ��������. (� ������ �� ������� ������������ �� ������� �(�, �)�)

�������:
Infix: (3+5)*2        Infix: 6+7*2-1*3
Postfix: 35+2*        Postfix: 672*+13*-
��������, ������� ��� �����:
(3+5)*2               6+7*2-1*3
35+2*                 672*+13*-
16                    17
*/
int main()
{
	std::string fileName; // �������� ��e: brackets.txt
	std::cin >> fileName;

	checkExpression(fileName);
    return 0;
}

