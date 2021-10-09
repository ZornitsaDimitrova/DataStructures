
#pragma once

#ifndef FMIBANK_H_INCLUDED
#define FMIBANK_H_INCLUDED

#include "Structs.h"
#include "Vector.h"

#include <exception>
#include <cstring>
#include <iostream>


class fmiBank
{
public:
	fmiBank();

	void add_wallet(double fiatMoney, const char* name);
	void make_order(Order::Type type, double fmiCoins, unsigned int walletId);
	void transfer(unsigned senderId, unsigned receiverId, double fmiCoins);
	void wallet_info(unsigned walletId);
	void attract_investors();
	void quit();
	void readDataFromTheFiles();

private:
	Vector <Wallet> wallets;
	Vector <Transaction> transactions;
	Vector<Order> orders;

	//помощни функции
	bool exist(unsigned id);

	bool canSell(unsigned walletId, double fmiCoins);
	bool canBuy(unsigned walletId, double fmiCoins);

	void Sell(unsigned walletId, double fmiCoins);
	void Buy(unsigned walletId, double fmiCoins);

	double countFmiCoins(unsigned walletId);

	void add_order(Order::Type type, unsigned walletId, double fmiCoins);
	void add_transaction(unsigned senderId, unsigned receiverId, double fmiCoins);

	void sortWallets();
};

#endif // !FMIBANK_H_INCLUDED