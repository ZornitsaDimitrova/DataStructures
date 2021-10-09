// stackExcercisez.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
/*
Задача 1:

От текстов файл прочита низ, състоящ се от следните видове скоби “{“, “}”, “(“, “)”, “[“, “]”, 
проверява дали те са балансирани и извежда съответното съобщение на екрана.

Пример:
Входящ низ: {([)]}              Входящ низ: [()]{}{[()({})]()}
Резултат: Not balanced          Резултат: Balanced
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
Задача 2:

От текстов файл прочита низ, представляващ израз, който трябва да се пресметне. Приоритета на операциите е обозначен със скобите “(”, “)”. 
Полученият резултат трябва да бъде записан с разделител “=” след първоначалния низ в същия файл.

Пример:
Входящ низ: (((2*4)-(1*2))/(9-7))
Резултат:  3
Резултат, записан във файла: (((2*4)-(1*2))/(9-7)) = 3
*/
/*
Задача 3:

От текстов файл прочита символен низ, който представлява математически израз в инфиксен вид, след това го преобразува в обратен полски запис - постфиксен вид и пресмята получения низ. В нов текстов файл на отделни редове записва израза в инфиксен и постфиксен вид заедно с получения резултат. (в израза се допуска използването на скобите “(”, “)”)

Примери:
Infix: (3+5)*2        Infix: 6+7*2-1*3
Postfix: 35+2*        Postfix: 672*+13*-
Резултат, записан във файла:
(3+5)*2               6+7*2-1*3
35+2*                 672*+13*-
16                    17
*/
int main()
{
	std::string fileName; // Примерно имe: brackets.txt
	std::cin >> fileName;

	checkExpression(fileName);
    return 0;
}

