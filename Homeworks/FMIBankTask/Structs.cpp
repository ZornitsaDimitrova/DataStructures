#include "stdafx.h"
#include "Structs.h"
#include <exception>
#include <ctime>
#include <cstring>
#include <iostream>




Wallet::Wallet(const char * owner, double fiatMoney)
{
	setOwner(owner);
	setFiatMoney(fiatMoney);
}

Wallet::Wallet()
{}


void Wallet::setOwner(const char * owner)
{
	if (strlen(owner) >= 256) {
		throw std::runtime_error("Invalid name");
	}

	strcpy_s(this->owner, strlen(owner) + 1, owner);
}

void Wallet::setFiatMoney(double fiatMoney)
{
	this->fiatMoney = fiatMoney;
}


bool Wallet::operator==(const Wallet & other) const
{
	return id == other.id;
}


Transaction::Transaction(Wallet &w1, unsigned senderId)
{
	setTime();
	setReceiverId(w1.id);
	if (senderId == 4294967295) {
		setSenderId(4294967295);
		setFmiCoins(w1.fiatMoney / (double)375);
	}
	else {
		throw std::runtime_error("Invalid system id");
	}
}

Transaction::Transaction(unsigned senderId, unsigned receiverId, double fmiCoins)
{
	setTime();
	setSenderId(senderId);
	setReceiverId(receiverId);
	setFmiCoins(fmiCoins);
}

Transaction::Transaction()
{}


void Transaction::setTime()
{
	time(&_time);
}

void Transaction::setSenderId(unsigned senderId)
{
	this->senderId = senderId;
}

void Transaction::setReceiverId(unsigned receiverId)
{
	this->receiverId = receiverId;
}

void Transaction::setFmiCoins(double fmiCoins)
{
	this->fmiCoins = fmiCoins;
}

Order::Order(Type type, unsigned int id, double fmiCoins)
{
	setType(type);
	setWalletId(id);
	setFmiCoins(fmiCoins);
}

Order::Order()
{}


void Order::setType(Type type)
{
	this->type = type;
}

void Order::setWalletId(unsigned walletId)
{
	this->walletId = walletId;
}

void Order::setFmiCoins(double fmiCoins)
{
	this->fmiCoins = fmiCoins;
}


bool Order::operator==(const Order & other) const
{
	return walletId == other.walletId;
}
