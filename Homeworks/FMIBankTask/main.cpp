// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Structs.h"
#include "fmiBank.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
	fmiBank bank;

	char command[30];
	do {
		std::cin >> command;

		if (strcmp(command, "readDataFromTheFiles") == 0) {
			bank.readDataFromTheFiles();
		}
		else if (strcmp(command,"add_wallet") == 0) {
			double fiatMoney;
			char owner[256];
			std::cout << "Enter fiat money:" << std::endl;
			std::cin >> fiatMoney;
			std::cout << "Enter name:" << std::endl;
			std::cin >> owner;
			bank.add_wallet(fiatMoney, owner);
		}
		else if (strcmp(command,"wallet_info") == 0) {
			unsigned id;
			std::cout << "Enter Id:" << std::endl;
			std::cin >> id;
			bank.wallet_info(id);
		}
		else if (strcmp(command,"make_order") == 0) {
			int type;
			double fmiCoins;
			unsigned walletId;
			std::cout << "Enter '0' for selling or '1' for buying: " << std::endl;
			std::cin >> type;
			std::cout << "Enter number of Fmi-Coins: " << std::endl;
			std::cin >> fmiCoins;
			std::cout << "Enter wallet Id" << std::endl;
			std::cin >> walletId;
			bank.make_order(Order::Type(type),fmiCoins,walletId);
		}
		else if (strcmp(command,"transfer") == 0) {
			unsigned senderId, receiverId;
			double fmiCoins;
			std::cout << "Enter sender Id: " << std::endl;
			std::cin >> senderId;
			std::cout << "Enter receiver Id: " << std::endl;
			std::cin >> receiverId;
			std::cout << "Enter number of Fmi-Coins: " << std::endl;
			std::cin >> fmiCoins;
			bank.transfer(senderId,receiverId,fmiCoins);
		}
		else if (strcmp(command,"attract_investors") == 0) {
			bank.attract_investors();
		}
		std::cout << std::endl;
	} while (strcmp(command,"quit") != 0);

	bank.quit();


	return 0;
}

