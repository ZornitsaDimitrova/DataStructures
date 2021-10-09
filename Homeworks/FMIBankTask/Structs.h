#pragma once

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <ctime>


struct Wallet {

	char owner[256];
	unsigned id;
	double fiatMoney;

	Wallet(const char* owner, double fiatMoney);
	Wallet();

	void setOwner(const char* owner);
	void setFiatMoney(double fiatMoney);

	bool operator ==(const Wallet& other) const;

};

struct Transaction {

	time_t _time;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;

	Transaction(Wallet &w1, unsigned senderId);
	Transaction(unsigned senderId, unsigned receiverId, double fmiCoins);
	Transaction();

	void setTime();
	void setSenderId(unsigned senderId);
	void setReceiverId(unsigned receiverId);
	void setFmiCoins(double fmiCoins);

};

struct Order {

	enum Type { SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;

	Order(Type type, unsigned int id, double fmiCoins);
	Order();

	void setType(Type type);
	void setWalletId(unsigned walletId);
	void setFmiCoins(double fmiCoins);

	bool operator ==(const Order& other) const;
};

#endif // !STRUCTS_H_INCLUDED
