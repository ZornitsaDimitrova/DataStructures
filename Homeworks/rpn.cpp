#include "stdafx.h"
#include <iostream>
#include <stack>
#include <cstring>
#include <cassert>

int precedence(char c)
{
	if (c == '*' || c == '/') {
		return 2;
	}
	else if (c == '+' || c == '-') {
		return 1;
	}
	return  0;
}


std::string infixToPostfix(const std::string& expr)
{
	std::string postfixNotation;
	std::stack<char> s;
	for (size_t i = 0, sz = expr.size(); i < sz; i++) {
		if (expr[i] == '(') {
			s.push(expr[i]);
		}
		else if (expr[i] == ')') {
			while (s.size() && s.top() != '(') {
				postfixNotation.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
		else if ((expr[i] >= 'a' &&  expr[i] <= 'z') ||
			(expr[i] >= '0' && expr[i] <= '9')) {
			postfixNotation.push_back(expr[i]);
		}
		else {
			while (s.size() && precedence(s.top()) >= precedence(expr[i])) {
				postfixNotation.push_back(s.top());
				s.pop();
			}
			s.push(expr[i]);
		}
	}
	while (s.size()) {
		postfixNotation.push_back(s.top());
		s.pop();
	}
	return postfixNotation;
}
//vajno
int calculateRPN(const std::string& expr)
{
	std::string toRPN = infixToPostfix(expr);
	std::stack<int> s;
	for (size_t i = 0, sz = toRPN.size(); i < sz; i++) {
		if (toRPN[i] >= '0' && toRPN[i] <= '9') {
			s.push(toRPN[i] - '0');
		}
		else {
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			switch (toRPN[i]) {
			case '+': s.push(left + right); break;
			case '-': s.push(left - right); break;
			case '*': s.push(left * right); break;
			case '/': s.push(left / right); break;
			}
		}
	}
	return s.top();
}
std::ostream& operator << (std::ostream& os, const std::string& str)
{
	for (size_t i = 0, sz = str.size(); i < sz; i++)
	{
		os << str[i];
	}
	return os;
}
int main()
{

	std::cout << infixToPostfix("a+b*c-d*e") << "\n";
	std::cout << infixToPostfix("(a+b)*c") << "\n";
	std::cout << calculateRPN("2*3+4*(5-6)") << "\n";

    return 0;
}

