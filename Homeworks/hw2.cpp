
#include "stdafx.h"
#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
#include <fstream>
#include <stdexcept>

std::string readFromFile(const char* fileName)
{
	std::ifstream compressed(fileName);
	if (!compressed) throw std::runtime_error("Error reading from the file!!");

	std::string content((std::istreambuf_iterator<char>(compressed)), (std::istreambuf_iterator<char>()));

	compressed.close();

	return content;
}

bool checkBraces(const std::string& comp)
{
	std::stack<char> braces;

	for (size_t i = 0, sz = comp.size(); i < sz; i++) {
		if (comp[i] == '\\' && (comp[i + 1] == ')' || comp[i + 1] == '('))
		{
			//��� ���� ������� ���� ��������� ����� �� ��������
			i++; 
			continue;
		}

		if (comp[i] == '\"') //��� ����� ������� �� ����������� ��������� � ���
		{
			i++;
			while (comp[i] != '\"')
			{
				if (comp[i] == '\\')
				{
					i++;
					i++;
				}
				i++;
			}
			continue;
		}

		if (comp[i] == '(') 
		{
			braces.push(comp[i]);
		}

		if (comp[i] == ')') 
		{
			//� ��� ����� � ������, ����� ���������� � ������
			if (braces.empty()) 
			{
				return false;
			}
			braces.pop();
		}
	}
	return (braces.empty());
}


bool checkNumbers(const std::string& comp)
{

	for (size_t i = 0, sz = comp.size(); i < sz; i++) {
		if (comp[i] == '\"') //��� ����� ������� �� ����������� ��������� � ���
		{
			i++;
			while (comp[i] != '\"')
			{
				if (comp[i] == '\\')
				{
					i++;
					i++;
				}
				i++;
			}
			continue;
		}

		if (comp[i] == '\\' && (comp[i+1] >= '0' && comp[i+1] <= '9')) 
		{
			//��� ����� ��������� ����� ����� ������� �� ����������
			i++;
			continue;
		}

		if (comp[i] >= '0' && comp[i] <= '9')
		{
			//��� ����� �����, �� ���� ���� ������ �������� ����� - ������� � ����������
			if ((comp[i + 1] < '0' || comp[i + 1] > '9') && comp[i + 1] != '(')
			{
				return false;
			}
		}
	}
	return true;

}

bool checkQuotes(const std::string& comp)
{
	//����������� ���� ��������� �� ����� ����
	//�.�. ���� ����� �������� ��� ���������
	int counter = 0;
	for (size_t i = 0, sz = comp.size(); i < sz; i++) {
		//��� � ���� ��������� ����� � ����������
		if (comp[i] == '\\' && comp[i + 1] == '\"') 
		{
			i++;
			continue;
		}

		if (comp[i] == '\"')
		{
			counter++;
		}
	}

	if (counter % 2 == 0)
	{
		return true;
	}
	return false;
}

bool checkSlashes(const std::string& comp)
{
	//������� � ������� ��� ���� ����������� ����� ��� ������
	bool nextCharacter = true;
	size_t index = comp.size();
	for (size_t i = 0, sz = comp.size(); i < sz; i++) {

		if (comp[i] == '\\' && i == index-1)
		{
			nextCharacter = false;
		}

	}
	return nextCharacter;
}

bool checkTheCompressedString(const std::string& comp) 
{
	if (checkSlashes(comp) && checkQuotes(comp) && checkNumbers(comp) && checkBraces(comp))
	{
		//�������� �� �������� ���������� �� �������
		for (size_t i = 0, sz = comp.size(); i < sz; i++) {
			if (comp[i] == '\"')
			{
				i++;
				while (comp[i] != '\"')
				{
					if (comp[i] == '\\')
					{
						i++;
						i++;
					}
					i++;
				}
				continue;
			}
			if (comp[i] >= 'A' && comp[i] <= 'Z')
			{
				continue;
			}
			if (comp[i] >= 'a' && comp[i] <= 'z')
			{
				continue;
			}
			if (comp[i] >= '0' && comp[i] <= '9')
			{
				continue;
			}
			if (comp[i] == '\\' || comp[i] == '(' || comp[i] == ')')
			{
				continue;
			}
			if (i > 0)
			{
				//��� �������� � ��������, �� �� � ����� � � ���������, ������������
				if (comp[i - 1] == '\\')  
			    {
					continue;
				}
			}
			return false;
			
		}
	}

	return true;
}

//�������� ���� ����� ������ ��� ��������� �����
bool checkForSlash(std::stack<char> &s) 
{
	char temp = s.top();
	s.pop();

	if (s.empty() || s.top() != '\\')
	{
		s.push(temp);
		return false;
	}

	s.push(temp);
	return true;
}

std::string repeats(std::stack<char> &forRepeating)
{
	std::string str;         //��������, ����� �� ������� ���������
	std::stack <char> rep;   //������� ����, ����� ��������� �� ���������� �� ���������������� ������������
	                       
	//������� ���������� �� ���������� �� ����������, ����� �� �� ������� � ���������� ������
	//(��� ���������� ��������)
	bool firstrepeat = true; 
	while (!forRepeating.empty())
	{
		
		while ((forRepeating.top() >= 'A' && forRepeating.top() <= 'Z') || 
			   (forRepeating.top() >= 'a' && forRepeating.top() <= 'z'))
		{
			rep.push(forRepeating.top());
			forRepeating.pop();
		}
		if (forRepeating.top() == '\"')
		{
			if (checkForSlash(forRepeating)) 
			{
				//��� ����� ��������� ����� ����� ��������� � �������� � �����,
				//������ �� �� �� ����� �� ������� � �� ��������� ������

				rep.push(forRepeating.top());
				forRepeating.pop();
				rep.push(forRepeating.top());
				forRepeating.pop();
				continue;
			}
			//����� �������� ��������� ������ ��� ������������ ���� ��� �� ������� �� ����������� � � �������� ����
			do 
			{
				rep.push(forRepeating.top());
				forRepeating.pop();

			} while (forRepeating.top() != '\"');


			rep.push(forRepeating.top()); //�������� � �����������
			forRepeating.pop();
			continue;
		}

		if (forRepeating.top() >= '0'&&forRepeating.top() <= '9')
		{
			std::string helper = "";  //������� ������ � ����� �� �������� ������ ���������
			int repeat = 0;
			int count = 0;
			int temp = 0;

			//����������� �� ��������� ����� � ��� ��� � �������� �
			//�������� ���� ������ � �������, ����� �� ����� �� ��������� ������
			if (checkForSlash(forRepeating)) 
			{
				rep.push(forRepeating.top());
				forRepeating.pop();
				rep.push(forRepeating.top());
				forRepeating.pop();
				continue;
			}

			//��� ������� �� ������ �� 1, ���������� �������, ����� �� � ����� �� ���� ����������
			while (forRepeating.top() >= '0' && forRepeating.top() <= '9')
			{
				repeat = temp + ((int)forRepeating.top() - '0')*pow(10, count);
				temp = repeat;
				count++;
				forRepeating.pop();
				if (forRepeating.empty()) break;
			}

			int counter = 0; //������� �� ��������, �� �� ���� ���� ��������� �� �������� ���� �� �� 
							 //������ ���� �� �������� ������� ���� ���� ������������ ����� ����������

			while (!rep.empty())
			{
				//��������� �� ��������� � �������� �� ������� ��� ���� ������� ���������� ����������
				if (!firstrepeat)   
				{
					str.insert(counter, 1, rep.top());
					counter++;
				}
				else if (rep.top() == '\"')
				{
					rep.pop();
					while (rep.top() != '\"')
					{
						str.push_back(rep.top());
						rep.pop();
					}
				}
				else if (rep.top() == '\\')
				{
					rep.pop();
					str.push_back(rep.top());
				}
				else
				{
					str.push_back(rep.top());
				}
				rep.pop();
			}

			while (repeat) //���������� ������������;
			{
				helper = str + helper;
				repeat--;
			}

			str = helper;
			firstrepeat = false; //������� ���������� � ����������
		}

	}
	return str;

}


void decompression(const char* compressed, const char* decompressed)
{
	std::string comp = readFromFile(compressed);
	if (!checkTheCompressedString(comp)) throw std::runtime_error("Incorrect input!!");

	std::stack <char> forRepeating;

	std::ofstream decomp(decompressed, std::ios::trunc);
	if (!decomp) throw std::runtime_error("Error writing to the file!!"); 

	for (size_t i = 0, sz = comp.size(); i < sz; i++) {
		if ((comp[i] >= 'A' && comp[i] <= 'Z') || (comp[i] >= 'a' && comp[i] <= 'z'))
		{
			decomp << comp[i];
		}
		else if (comp[i] >= '0' && comp[i] <= '9')
		{
			//�� ��������� �� ��������� ����� ������� � ����� ������, 
			//����� �� � ����� �� ��������������� ���� ��������� �������
			//o���� ��� �� �� � ������� ��� ���� ��������� �����(����������)
			while (comp[i] != ')')
			{
				if (comp[i] == '(')
				{
					i++;
					continue;
				}
				if (comp[i] == '\"')
				{
					do {
						forRepeating.push(comp[i]);
						i++;
						if (comp[i] == '\\')
						{
							forRepeating.push(comp[i]);
							i++;
							forRepeating.push(comp[i]);
							i++;
						}
					
					} while (comp[i] != '\"');

					forRepeating.push(comp[i]);
					i++;
					continue;
				}
				if (comp[i] == '\\')
				{
					forRepeating.push(comp[i]);
					i++;
					forRepeating.push(comp[i]);
					i++;
					continue;
				}

				forRepeating.push(comp[i]);
				i++;
			}

			std::string rep = repeats(forRepeating); //�������� ������������ ���������� ��� �����
			for (size_t i = 0, sz = rep.size(); i < sz; i++){
				decomp << rep[i];
			}
			continue;
		}
		else if (comp[i] == '\\')
		{
			i++;
			decomp << comp[i];
		}
		else if (comp[i] == '"')
		{
			i++;
			while (comp[i] != '"')
			{
				if (comp[i] == '\\')
				{
					i++;
					decomp << comp[i];
					i++;
					continue;
				}
				decomp << comp[i];
				i++;
			}
		}
	}
	decomp.close();
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Not enough arguments!" << std::endl;
	}
	else if (argc > 3)
	{
		std::cerr << "Too many arguments!" << std::endl;
	}
	else
	{
		decompression(argv[1], argv[2]);
		std::cout << "Decompression done!!" << std::endl;
	}
	
	return 0;
}



