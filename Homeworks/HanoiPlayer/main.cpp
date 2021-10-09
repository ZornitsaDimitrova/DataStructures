// hanoiPlayer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hanoyPlayer.h"
#include <iostream>


int main()
{
	HanoiPlayer player(3);

	while (player.hasMoreMoves())
	{
		HanoiPlayer::HanoiMove move = player.getNextMove();

		std::cout << "Move one disk from "
			<< move.from
			<< " to "
			<< move.to << std::endl;
	}
    return 0;
}

