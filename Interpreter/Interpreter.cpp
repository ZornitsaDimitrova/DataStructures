#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>
#include <regex>
#include <string>


Interpreter::Interpreter(TakeLine& _input) :input(_input)
{}

void Interpreter::evaluate()
{
	TakeLine::Line tokenLine = input.getNextLine();
	while (input.hasMoreTokens())
	{
		if (tokenLine.type == TakeLine::Line::assignment)
		{
			executeAssignment(tokenLine);
		}
		else if (tokenLine.type == TakeLine::Line::fun)
		{
			executeFunctionDefinition(tokenLine);
		}
		else if (tokenLine.type == TakeLine::Line::print)
		{
			executePrinting(tokenLine);
		}
		else if (tokenLine.type == TakeLine::Line::read)
		{
			executeReading(tokenLine);
		}
		else
		{
			std::cout << "Syntax Error at line " <<TakeLine::getCountLines() << "!" << std::endl;
			assert(false);
		}
		tokenLine = input.getNextLine();
	}
}

std::string Interpreter::executeExpression(int startPos, TakeLine::Line::LineType type, std::string token)
{
	std::string result;

	for (int i = startPos; i < token.length(); i++)
	{
		 if (isUpperCaseLetter(token[i]))
		{
			std::string funName = getWholeFunName(token, i);
			std::string funDef = findFunDefOrVarVal(funName, funMap);
			if (token[i] != '[')
			{
				std::cout << "Missing \"[\" at line " << TakeLine::getCountLines() << std::endl;
				assert(false);
			}
			//��������� ��������, ����� ���� �� ������� ���������� ����� ������, ��������� ����� �������
			std::string generalArgument = getArgument(token, i);
			i--;

			//�������� �������� �� �������� ������� ���� ���������� �� ���������� ������� (��� ��� ������) ��� ����������� ��������� 
			//������ ������� �� ��������
			std::string finalArgument = evaluateFunctionsInTheArgument(generalArgument);

			//���������, ������ ������ ���������� �� �������� � ���������� ������� ��������
			replaceParameterWithArgument(funDef, finalArgument, result); 
		}
		//����� ������ ������ ���������.�������(����� �� ����� �� ����������) � ����� � ���������
		//��� ���� ��������� ������ ��� ������������ ����������, �� ��������, ����� �� ����������, �� ������� �� ����
		else
		{
			result.push_back(token[i]);
		}
	}
	//��� ����� �� � ���������� �� ������� ������ ������� ������ ���������� ��� ����������� ��.
	//��� ���� ���������� �� ������� �� ������� ������� �� ������������ ��� ����������� ��, �� �� ����
	//��� ������������� �� ������ ���������� ������� �������� �� ���� ��������� � � ����������� �� ���������!
	if (type != TakeLine::Line::fun)
    {
    	replaceVariablesWithValues(result);
	}

	return result;
}

void Interpreter::replaceParameterWithArgument(std::string funDef, std::string argument, std::string& result)
{
	int i = 0;
	std::string parameter = getWholeVarName(funDef, i);
	//��������� ����������� '@' ���� ���� ��� ����� ����������
	i += 1;
	//��������� ����������� � �����, �� �� ��� �������, �� ���������� � ��� �� �� �������� �������������, ��� �� �� ������
	//�� ���� ����� ��������� ��� ����� ���(*,/,%)
	std::string var;
	result.push_back('(');
	for (int j = i; j < funDef.length(); j++)
	{
		//��� ��� �������� ����� ����� ����, �� ������ ��� �� ����������/���������
		if (isLowerCaseLetter(funDef[j]))
		{
			//��������� ����� j �� �������, � ����� ����� ������ �������� �� ����� �����
			var = getWholeVarName(funDef, j);
			//������ �� �� ���������� ����� �����, � ��� �� ���������� �������� �� �� �������� ������� �� ���
			j--;
		}
		//��� ���������� ���������� ������� � ���������� => ������� � ���������
		if (parameter.compare(var) == 0)
		{
			//��������� ���� ��������� � �����, ������ ���� �� �� � ������ �����, � �����
			result.push_back('(');
			result.append(argument);
			result.push_back(')');
		}
		//��� ������� �� var � >0 => �������� ��� ����������, ����� �� � ���������� => ������ � ������� � ���������
		else if (var.length() > 0)
		{
			result.append(var);
		}
		//����� ������ ������� ��������� ������
		else
		{
			result.push_back(funDef[j]);
		}
		//��������� ������������ var, �� �� ���� ������ � ��� �� ����� ���������� ����������
		var = "";
	}
	result.push_back(')');
}

//�������� �� ����� ����� � ������ �����
bool Interpreter::isLowerCaseLetter(char letter)
{
	return letter >= 'a' && letter <= 'z';
}

bool Interpreter::isUpperCaseLetter(char letter)
{
	return letter >= 'A' && letter <= 'Z';
}

//�������, ����� ������ ������ ����� �� ���������� � �������
std::string Interpreter::getWholeVarName(std::string& token, int& i)
{
	std::string varName;
	while (isLowerCaseLetter(token[i]))
	{
		varName.push_back(token[i]);
		i++;
	}
	return varName;
}

std::string Interpreter::getWholeFunName(std::string& token, int& i)
{
	std::string funName;
	while (isUpperCaseLetter(token[i]))
	{
		funName.push_back(token[i]);
		i++;
	}
	return funName;
}

void Interpreter::executeAssignment(TakeLine::Line assignment)
{
	std::string var;
	int i = 0;
	var = getWholeVarName(assignment.token, i);
	//��������� �������
	i += 1;
	//�������� �� ������� �� expression ���� �������
	if (assignment.token.size() < i + 1)
	{
		std::cout << "There is no value for the variable " << var << " at line " << TakeLine::getCountLines() << "!" << std::endl;
		assert(false);
	}
	
	std::string expr = executeExpression(i, assignment.type, assignment.token);
	EvaluateExpression final(expr);
	unsigned long int expressionResult = final.evaluate();
	defineOrRedefine(varMap, var, expressionResult);
}

void Interpreter::executeFunctionDefinition(TakeLine::Line fun)
{
	int i = 0;
	
	std::string name = getWholeFunName(fun.token, i);
	//��������� �������
	i++;
	std::string parameter = getWholeVarName(fun.token, i);
	
	//��������� ������� � �������, �� �� ������ �������� �� �����������
	i += 2;
	//�������� �� ������� �� expression ���� �������
	if (fun.token.size() < i + 1)
	{
		std::cout << "There is no definition to the function " << name << " at line " << TakeLine::getCountLines() << "!" << std::endl;
		assert(false);
	}
	//������ �������� ������ � ���� �� ����������, �� �� ���� ���� ������� ����� ��
	parameter.push_back('@');
	std::string definition = executeExpression(i, fun.type, fun.token);
	//������� ���������� �� ��������� � �������� �� ����������� �.
	definition.insert(0, parameter);
	//��� ���� ���� ���������� ������� � ���� ���, �������� ����������� �, ��� ��-�������� ���� �������
	defineOrRedefine(funMap, name, definition);
}

void Interpreter::executePrinting(TakeLine::Line toPrint)
{
	std::string print = executeExpression(0, toPrint.type, toPrint.token);
	EvaluateExpression final(print);
	int expressionResult = final.evaluate();

	std::cout << expressionResult << std::endl;
}

void Interpreter::executeReading(TakeLine::Line read)
{
	int i = 0;
	std::string var = getWholeVarName(read.token, i);
	unsigned long int value;
	std::cout << "Enter value(positive integer) for variable " << var << std::endl;
	std::cin >> value;
	if ((int)value < 0)
	{
		std::cout << "Values can be only POSITIVE integers!" << std::endl;
		assert(false);
	}
	defineOrRedefine(varMap, var, value);
}

std::string Interpreter::evaluateFunctionsInTheArgument(std::string argument)
{
	std::string result;
	int startInserting;
	for (int i = 0; i < argument.length(); i++)
	{
		if (isUpperCaseLetter(argument[i]))
		{
			startInserting = i;
			std::string funName = getWholeFunName(argument, i);
			std::string innerFunDef = findFunDefOrVarVal(funName, funMap);
			//���� ����� �� ���������, ������ �� ������ ����� �� ����� ����������� �, � ����� ����� ���� ������� ���������� ��� ���������� ��������
			argument.erase(startInserting, funName.length());
			//getArgument ���� ���������� � ����������� �����, � ����� � ���������� �� ����������� �������� �������
			std::string innerArgument = getArgument(argument, startInserting);
			replaceParameterWithArgument(innerFunDef, innerArgument, result);
			argument.insert(startInserting, result);
			result = "";
			//�������� ������ �� �������� �� �������, ������ ���� �� ��� ����� ������� ������� � ���������, ����� ������ �������������� �� �� ���������
			i = 0;
		}
	}
	return argument;
}

void Interpreter::replaceVariablesWithValues(std::string& expression)
{
	for (int i = 0; i < expression.length(); i++)
	{
		if (isLowerCaseLetter(expression[i]))
		{
			int startingVarName = i;
			std::string var = getWholeVarName(expression, i);
			//������� ���������, �.�. ���� ���� ��� �������� ���� �� ����� �� ������������ ��������� � ���� �� ��������� ������
			//� ��� ���������� �������� ���� ������ �� ���� ���������
			i--;

			std::string value = std::to_string(findFunDefOrVarVal(var, varMap));
			expression.erase(startingVarName, var.length());
			expression.insert(startingVarName, value);

			//i = startingVarName;
			//������� ������� ���� � ������� �� ��� �� ����� ����� �� �� ������ ������� ��������, �.�. ��� ���������� � ��-����� �����
			//�� ��������� �� ���� �� ������� ����� �� ���� � ������� �� ������� � ������ ��������.
			//�.�. �������� ����� �� ������������� � �� ������ ����� ������ ���������� �, 
			//������ ��������� ����� ������ ��������� ����� ��������� �� ����� �� ������������ � ������� ��������.
			int moveBackIterator = var.length() - value.length();
			i -= moveBackIterator;
		}
	}
}

std::string Interpreter::getArgument(std::string& token, int i)
{
	int count = 0;
	int j;
	for (j = i; j < token.length(); j++) {
		if (token[j] == '[') {
			count++;
		}
		else if (token[j] == ']') {
			count--;
		}

		if (count == 0) {
			break;
		}
	}
	//������ ����� �������� � ������ ���������� ������� � ����(��� ��� ������)
	if (count != 0) {
		std::cout << "Mismatched brackets at line " <<TakeLine::getCountLines() << "!" << std::endl;
		assert(false);
	}

	std::string argument;

	//����� ������� �������� �����
	if (token[i] != '[') {
		std::cout << "Mismatched brackets at line " << TakeLine::getCountLines() << "!" << std::endl;
		assert(false);
	}
	token.erase(i, 1);
	while (j - i) {
		argument.push_back(token[i]);
		token.erase(i, 1);
		j--;
	}
	//����� ���������� ��������� �����
	if (argument.back() != ']') {
		std::cout << "Mismatched brackets at line " << TakeLine::getCountLines() << "!" << std::endl;
		assert(false);
	}
	argument.pop_back();

	return argument;
}
