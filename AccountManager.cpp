#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Account.h"
#include "AccountManager.h"

int AccountManager::insertAccount(Account* account)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO account VALUES (?, ?, ?, ?, ?, ?)");

	ps->setString(1, account->AccountID);
	ps->setString(2, account->AccountUsername);
	ps->setString(3, account->AccountPassword);
	ps->setDouble(4, account->AccountAmount);
	ps->setDouble(5, account->TransactionLimit);
	ps->setString(6, account->SecureWord);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int AccountManager::updateAccountPassword(string password, string username)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE account SET AccountPassword = ? WHERE AccountUsername = ?");

	ps->setString(1, password);
	ps->setString(2, username);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int AccountManager::updateAccountTransaction(double balance, string accountID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE account SET AccountAmount = ? WHERE AccountID = ?");

	ps->setDouble(1, balance);
	ps->setString(2, accountID);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int AccountManager::updateAccountSecureWord(string secureWord, string username)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE account SET SecureWord = ? WHERE AccountUsername = ?");

	ps->setString(1, secureWord);
	ps->setString(2, username);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int AccountManager::updateAccountTransactionLimit(double transactionLimit, string username)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE account SET TransactionLimit = ? WHERE AccountUsername = ?");

	ps->setDouble(1, transactionLimit);
	ps->setString(2, username);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}


Account* AccountManager::selectAccountUsername(string AccountUsername)
{
	Account* account = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE AccountUsername = ?");

	ps->setString(1, AccountUsername);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		account = new Account();
		account->AccountID = rs->getString(1);
		account->AccountUsername = rs->getString(2);
		account->AccountPassword = rs->getString(3);
		account->AccountAmount = rs->getDouble(4);
		account->TransactionLimit = rs->getDouble(5);
		account->SecureWord = rs->getString(6);
	}

	delete rs;
	delete ps;

	return account;
}

Account* AccountManager::selectAccountID(string AccountID)
{
	Account* account = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE AccountID = ?");

	ps->setString(1, AccountID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		account = new Account();
		account->AccountID = rs->getString(1);
		account->AccountUsername = rs->getString(2);
		account->AccountPassword = rs->getString(3);
		account->AccountAmount = rs->getDouble(4);
		account->TransactionLimit = rs->getDouble(5);
		account->SecureWord = rs->getString(6);
	}

	delete rs;
	delete ps;

	return account;
}

Account* AccountManager::selectAccountPassword(string AccountPassword)
{
	Account* account = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE AccountPassword = ?");

	ps->setString(1, AccountPassword);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		account = new Account();

		account->AccountPassword = rs->getString(3);
	}

	delete rs;
	delete ps;

	return account;
}

bool AccountManager::checkAccountID(string accountID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE AccountID=?");
	ps->setString(1, accountID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		return true;
	}
	else
	{
		return false;
	}

	delete rs;
	delete ps;
}

bool AccountManager::checkAccountUsername(string accountUsername)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE AccountUsername=?");
	ps->setString(1, accountUsername);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		return true;
	}
	else
	{
		return false;
	}

	delete rs;
	delete ps;
}

bool AccountManager::checkAccountPassword(string password, string username)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE (AccountPassword=? AND AccountUsername=?)");
	ps->setString(1, password);
	ps->setString(2, username);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		return true;
	}
	else
	{
		return false;
	}

	delete rs;
	delete ps;
}

bool AccountManager::checkAccountSecureWord(string secureWord, string username)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE (SecureWord=? AND AccountUsername=?)");
	ps->setString(1, secureWord);
	ps->setString(2, username);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		return true;
	}
	else
	{
		return false;
	}

	delete rs;
	delete ps;
}

string AccountManager::RandomAccountIDGenerator()
{
	int i, r;
	string final;
	long long t = 0;
	int c[10];
	vector<int> digits;   for (i = 0; i < 10; i++) digits.push_back(i);

	srand(time(0));
	for (i = 0; i < 10; i++)
	{
		r = rand() % (10 - i);
		c[i] = digits[r];
		digits.erase(digits.begin() + r);
	}

	for (i = 0; i < 10; i++) { 
		t += (c[i] * pow(10, i));
	}
	final = to_string(t);
	return final;
}

int AccountManager::updateAccountUsernameAdmin(string username, string accountID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE account SET AccountUsername = ? WHERE AccountID = ?");

	ps->setString(1, username);
	ps->setString(2, accountID);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int AccountManager::deleteAccountAdmin(string accountID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM account WHERE AccountID=?");

	ps->setString(1, accountID);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}
