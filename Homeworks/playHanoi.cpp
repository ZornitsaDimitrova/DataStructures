// playHanoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>


struct Pole
{
	std::vector<int> disks;
	char name;
};

void movedisk(Pole &source, Pole &dest)
{
	dest.disks.push_back(source.disks[source.disks.size() - 1]);
	source.disks.erase(source.disks.begin() + (source.disks.size() - 1), source.disks.end());
}

void playHanoi(int k, Pole &source, Pole &dest, Pole &temp)
{
	if (k == 0)
		return;

	if (k == 1)
	{
		std::cout << "Move one disk from " << source.name << " to " << dest.name << std::endl;
		movedisk(source, dest);
		//drawTowers(source,dest,temp);
		return;

	}

	playHanoi(k - 1, source, temp, dest);
	playHanoi(1, source, dest, temp);
	playHanoi(k - 1, temp, dest, source);


}

struct gameGoal
{
	int k;
	char source, dest, temp;
};


void hanoiIter(int k, char source, char dest, char temp)
{
	std::stack<gameGoal> s;
	s.push({ k,source,dest,temp });

	while (!s.empty())
	{
		gameGoal current = s.top(); s.pop();

		if (current.k == 1)
		{
			std::cout << "Move one disk from "
				<< current.source
				<< " to "
				<< current.dest << std::endl;
		}
		else
		{
			s.push({ current.k - 1,current.temp, current.dest,current.source });
			s.push({ 1,current.source, current.dest, current.temp });
			s.push({ current.k - 1,current.source, current.temp, current.dest });

		}
	}
}


int main()
{
	Pole A{ { 5,4,3,2,1 },'A' }, B{ {},'B' }, C{ {},'C' };

	playHanoi(3, A, C, B);
	std::cout << "===============\n";
	hanoiIter(3, 'A', 'C', 'B');


}
