#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "fmiBank.h"


static int uniqueId = 0;


bool fmiBank::exist(unsigned id)
{
	for (size_t i = 0; i < wallets.getSize(); i++)
	{
		if (wallets[i].id == id)
		{
			return true;
		}
	}
	return false;
}


bool fmiBank::canSell(unsigned walletId, double fmiCoins)
{
	//Проверяваме дали съществува, дали сумата е по-голяма от 0, дали това е първата му заявка и дали разполага с достатъчно Fmi-Coin-и
	bool firstOrder = true;
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (orders[i].walletId == walletId) firstOrder = false;
	}
	if (exist(walletId) && fmiCoins > 0 && countFmiCoins(walletId) >= fmiCoins && firstOrder)
	{
		return true;
	}
	return false;
}

bool fmiBank::canBuy(unsigned walletId, double fmiCoins)
{
	//Проверяваме дали съществува, дали сумата е по-голяма от 0, дали това е първата му заявка и дали и дали разполага с достатъчно реални пари
	bool firstOrder = true;
	double fc = 0;
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (orders[i].walletId == walletId) firstOrder = false;
	}
	for (size_t i = 0; i < wallets.getSize(); i++)
	{
		if (wallets[i].id == walletId) fc = wallets[i].fiatMoney;
	}
	if (exist(walletId) && fmiCoins > 0 && (fmiCoins * 375) <= fc && firstOrder)
	{
		return true;
	}
	return false;
}

void fmiBank::attract_investors()
{
	//Сортираме и извеждаме нужната информация за първите 10 портфейла
	sortWallets();
	if (wallets.getSize() < 10) std::cout << "Not enough registered wallets in the bank!" << std::endl;
	else {
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << "Owner: " << wallets[i].owner << std::endl;
			std::cout << "FmiCoins: " << countFmiCoins(wallets[i].id) << std::endl;
			for (size_t j = 0; j < transactions.getSize(); j++)
			{
				if (transactions[j].receiverId == wallets[i].id || transactions[j].senderId == wallets[i].id)
				{
					std::cout << "Time of first transaction:" << transactions[j]._time << std::endl;
					break;
				}
			}
			int counter = 0;
			long long time = 0;
			//в променливата counter ще се запази броят на трансакциите, в които портфейла участва, а в time
			//времето на последната трансакция
			for (size_t j = 0; j < transactions.getSize(); j++)
			{
				if (transactions[j].receiverId == wallets[i].id || transactions[j].senderId == wallets[i].id)
				{
					counter++;
					time = transactions[j]._time;
				}
			}
			std::cout << "Number of transaction: " << counter << std::endl;
			std::cout << "Time of last transaction: " << time << std::endl;
			std::cout << std::endl;
		}
	}
}

//записва всичко във файловете
void fmiBank::quit()
{
	std::fstream otfile;

	otfile.open("transactions.dat", std::ios::binary | std::ios::out | std::ios::trunc);
	if (!otfile)
	{
		throw std::runtime_error("Can't open the file");
	}
	for (size_t i = 0; i < transactions.getSize(); i++)
	{
		otfile.write((const char*)(&(transactions[i])), sizeof(Transaction));
	}
	otfile.close();

	std::fstream oofile;
	oofile.open("orders.dat", std::ios::binary | std::ios::out | std::ios::trunc);
	if (!oofile)
	{
		throw std::runtime_error("Can't open the file");
	}

	for (size_t i = 0; i < orders.getSize(); i++)
	{
		oofile.write((const char*)(&(orders[i])), sizeof(Order));
	}

	oofile.close();

	std::fstream owfile;
	owfile.open("wallets.dat", std::ios::binary | std::ios::out | std::ios::trunc);
	if (!owfile)
	{
		throw std::runtime_error("Can't open the file");
	}
	for (size_t i = 0; i < wallets.getSize(); i++)
	{
		owfile.write((const char*)(&(wallets[i])), sizeof(Wallet));
	}
	owfile.close();

}

//чете всичко от файловете
void fmiBank::readDataFromTheFiles()
{
	std::fstream itfile;
	itfile.open("transactions.dat", std::ios::in);
	if (!itfile)
	{
		throw std::runtime_error("Can not open!");
	}
	while (!itfile.eof())
	{
		Transaction t1;
		itfile.read((char*)&t1, sizeof(Transaction));
		if (itfile.eof()) break;
		transactions.push_back(t1);
	}
	itfile.close();
	

	std::fstream iwfile;
	iwfile.open("wallets.dat", std::ios::in);
	if (!iwfile)
	{
		throw std::runtime_error("Can not open!");
	}
	while (!iwfile.eof())
	{
		Wallet w1;
		iwfile.read((char*)&w1, sizeof(Wallet));
		if (iwfile.eof()) break;
		wallets.push_back(w1);
	}
	iwfile.close();
	

	std::fstream iofile;
	iofile.open("orders.dat", std::ios::in);
	if (!iofile)
	{
		throw std::runtime_error("Can not open!");
	}


	while (!iofile.eof())
	{
		Order o1;
		iofile.read((char*)&o1, sizeof(Order));
		if (iofile.eof()) break;
		orders.push_back(o1);
	}
	iofile.close();

	std::fstream countfile;
	countfile.open("wallets.dat", std::ios::binary | std::ios::in);

	countfile.seekp(0, std::ios::end);
	std::streampos fileSize = countfile.tellp();
	countfile.seekp(0, std::ios::beg);

	int countWalletsInFile = (int)fileSize / sizeof(Wallet);
	countfile.close();
	//Запазваме броя на портфейлите, за да може номерацията на Id-тата да започне от него
	uniqueId = countWalletsInFile;
}

void fmiBank::Sell(unsigned walletId, double fmiCoins)
{
	if (canSell(walletId, fmiCoins))
	{

		for (size_t i = 0; i < orders.getSize(); i++)
		{
			//ако има нареждане за покупка и е на стойност по-малка от съответната за продажба
			if (orders[i].type == 1 && orders[i].fmiCoins < fmiCoins)
			{
				//създаваме трансакция с изпращач продавача, получател копувача и съответното количество Fmi-Coin-и, които получателя иска да закупи
				add_transaction(walletId, orders[i].walletId, orders[i].fmiCoins);

				for (size_t j = 0; j < wallets.getSize(); j++)
				{
					if (wallets[j].id == orders[i].walletId)
					{
						//Променяме реалните пари на купувача спрямо съответния курс
						wallets[j].setFiatMoney(wallets[j].fiatMoney - (orders[i].fmiCoins * 375));
						//Променяме Fmi-Coin-ите за продажба
						fmiCoins -= orders[i].fmiCoins;
					}
					if (wallets[j].id == walletId)
					{
						//Променяме и реалните пари на продавача спрямо съответния курс 
						wallets[j].setFiatMoney(wallets[j].fiatMoney + orders[i].fmiCoins * 375);
					}
				}
				// Премахваме поръчката на купувача
				orders.remove(orders[i]);
			}
			//ако има нареждане за покупка и е на стойност по-голяма от съответната за продажба
			else if (orders[i].type == 1 && orders[i].fmiCoins >= fmiCoins)
			{
				//създаваме трансакция с изпращач продавача, получател копувача и съответното количество Fmi-Coin-и, които се продават
				add_transaction(walletId, orders[i].walletId, fmiCoins);
				for (size_t j = 0; j < wallets.getSize(); j++)
				{
					if (wallets[j].id == orders[i].walletId)
					{
						//Променяме реалните пари на купувача спрямо съответния курс и задаваме ново нареждане със
						//съответното променено количество Fmi-Coin-и за закупуване (ако е нужно)
						wallets[j].setFiatMoney(wallets[j].fiatMoney - (fmiCoins * 375));
						double fc = orders[i].fmiCoins - fmiCoins;
						orders.remove(orders[i]);
						if (fc)
						{
							add_order(Order::Type(1), wallets[j].id, fc);
						}

					}
					if (wallets[j].id == walletId)
					{
						//Променяме реалните пари на продавача
						wallets[j].setFiatMoney(wallets[j].fiatMoney + fmiCoins * 375);
					}
				}
				//зануляваме Fmi-Coin-ите за продажба
				fmiCoins = 0;
			}

		}
		//Ако има все още Fmi-Coin-и за продажба добавяме нареждането
		if (fmiCoins)
		{
			std::cout << "There are no more buyers! Your order has been added but you have to wait!" << std::endl;
			add_order(Order::Type(0), walletId, fmiCoins);
		}

	}
	else
	{
		std::cout << "You do not cover the terms for selling! " << std::endl;
	}
}

void fmiBank::Buy(unsigned walletId, double fmiCoins)
{
	if (canBuy(walletId, fmiCoins))
	{
		for (size_t i = 0; i < orders.getSize(); i++)
		{
			//ако има нареждане за продажба и е на стойност по-малка от съответната за покупка
			if (orders[i].type == 0 && orders[i].fmiCoins < fmiCoins)
			{
				//създаваме трансакция с изпращач продавача, получател копувача и съответното количество Fmi-Coin-и, които изпращача продава
				add_transaction(orders[i].walletId, walletId, orders[i].fmiCoins);
				for (size_t j = 0; j < wallets.getSize(); j++)
				{
					if (wallets[j].id == orders[i].walletId)
					{
						//Променяме реалните пари на продавача спрямо съответния курс
						wallets[j].setFiatMoney(wallets[j].fiatMoney + (orders[i].fmiCoins * 375));

					}
					if (wallets[j].id == walletId)
					{
						//Променяме реалните пари на купувача спрямо съответния курс 
						wallets[j].setFiatMoney(wallets[j].fiatMoney - (orders[i].fmiCoins * 375));
					}
				}
				// Промененяме Fmi-Coin-ите за покупка и премахваме поръчката на продавача 
				fmiCoins -= orders[i].fmiCoins;
				orders.remove(orders[i]);
			}
			//ако има нареждане за продажба и е на стойност по-голяма или равна на съответната за покупка
			if (orders[i].type == 0 && orders[i].fmiCoins >= fmiCoins)
			{
				add_transaction(orders[i].walletId, walletId, fmiCoins);
				for (size_t j = 0; j < wallets.getSize(); j++)
				{
					if (wallets[j].id == orders[i].walletId)
					{
						//Променяме реалните пари на продавача спрямо съответния курс, премахваме нареждането му
						//и задаваме ново нареждане със съответното променено количество Fmi-Coin-и за продажба (ако е нужно)
						wallets[j].setFiatMoney(wallets[j].fiatMoney + (fmiCoins * 375));
						double fc = orders[i].fmiCoins - fmiCoins;
						orders.remove(orders[i]);
						if (fc)
						{
							add_order(Order::Type(1), wallets[j].id, fc);
						}

					}
					if (wallets[j].id == walletId)
					{
						//Променяме реалните пари на купувача
						wallets[j].setFiatMoney(wallets[j].fiatMoney - fmiCoins * 375);
					}
				}
				//зануляваме Fmi-Coin-ите за покупка
				fmiCoins = 0;
			}

		}
		//Ако има все още Fmi-Coin-и за покупка добавяме нареждането
		if (fmiCoins)
		{
			std::cout << "There are no more sellers! Your order has been added but you have to wait!" << std::endl;
			add_order(Order::Type(1), walletId, fmiCoins);
		}
	}
	else {
		std::cout << "You do not cover the terms for buying! " << std::endl;
	}
}

double fmiBank::countFmiCoins(unsigned walletId)
{
	double money = 0;
	for (size_t i = 0; i < transactions.getSize(); i++)
	{
		if (transactions[i].senderId == walletId)
		{
			money -= transactions[i].fmiCoins;
		}
		if (transactions[i].receiverId == walletId)
		{
			money += transactions[i].fmiCoins;
		}
	}
	return money;
}

void fmiBank::add_transaction(unsigned senderId, unsigned receiverId, double fmiCoins)
{
	Transaction transaction(senderId, receiverId, fmiCoins);
	transactions.push_back(transaction);

}

//сортира по количество Fmi-Coin-и
void fmiBank::sortWallets()
{
	for (size_t i = 0; i < wallets.getSize() - 1; i++)
	{
		for (int j = 0; j < wallets.getSize() - 1; j++)
		{
			if (countFmiCoins(wallets[j].id) < countFmiCoins(wallets[j + 1].id))
			{
				Wallet tmp = wallets[j];
				wallets[j] = wallets[j + 1];
				wallets[j + 1] = tmp;
			}
		}
	}
}

void fmiBank::add_order(Order::Type type, unsigned walletId, double fmiCoins)
{
	Order order(type, walletId, fmiCoins);
	orders.push_back(order);
}

fmiBank::fmiBank()
	:wallets(),
	transactions(),
	orders()
{}

void fmiBank::add_wallet(double fiatMoney, const char * name)
{

	Wallet w(name, fiatMoney);
	w.id = uniqueId++;
	wallets.push_back(w);

	//добавя системната трансакция
	Transaction t(w, 4294967295);
	transactions.push_back(t);

	std::cout << "Id: " << w.id << std::endl;
}

void fmiBank::make_order(Order::Type type, double fmiCoins, unsigned int walletId)
{

	if (type == 0)
	{
		Sell(walletId, fmiCoins);
	}
	else if (type == 1)
	{
		Buy(walletId, fmiCoins);
	}
	else
	{
		std::cout << "Invalid type!" << std::endl;
	}
}

void fmiBank::transfer(unsigned senderId, unsigned receiverId, double fmiCoins)
{
	if (exist(senderId) && exist(receiverId) && countFmiCoins(senderId) >= fmiCoins)
	{
		add_transaction(senderId, receiverId, fmiCoins);
	}
	else
	{
		std::cout << "Wallets don't exist or don't have enough money" << std::endl;
	}
}

void fmiBank::wallet_info(unsigned walletId)
{
	if (exist(walletId))
	{
		for (size_t i = 0; i < wallets.getSize(); i++)
		{
			if (wallets[i].id == walletId)
			{
				std::cout << "Name: " << wallets[i].owner << std::endl
					<< "Fiat money: " << wallets[i].fiatMoney << std::endl
					<< "Fmi-Coins: " << countFmiCoins(walletId) << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Invalid Id" << std::endl;
	}
}
