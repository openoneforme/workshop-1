#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Transaction.h"
#include "TransactionManager.h"

int TransactionManager::insertTransaction(Transaction* transaction)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO transaction(AccountID,ReceiverAccount,ReceiverName,TransactionAmount) VALUES (?, ?, ?, ?)");

	ps->setString(1, transaction->AccountID);
	ps->setString(2, transaction->ReceiverAccount);
	ps->setString(3, transaction->ReceiverName);
	ps->setDouble(4, transaction->TransactionAmount);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}


Transaction* TransactionManager::selectTransaction(string TransactionID)
{
	Transaction* transaction = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM transaction WHERE TransactionID = ?");

	ps->setString(1, TransactionID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		transaction = new Transaction();
		transaction->TransactionID = rs->getInt(1);
		transaction->AccountID = rs->getString(2);
		transaction->ReceiverAccount = rs->getString(3);
		transaction->ReceiverName = rs->getString(4);
		transaction->TransactionAmount = rs->getDouble(5);
		transaction->TransactionDate = rs->getString(6);	
	}

	delete rs;
	delete ps;

	return transaction;
}

Transaction* TransactionManager::latestTransaction()
{
	Transaction* transaction = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM transaction ORDER BY TransactionID DESC");

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		transaction = new Transaction();
		transaction->TransactionID = rs->getInt(1);
		transaction->AccountID = rs->getString(2);
		transaction->ReceiverAccount = rs->getString(3);
		transaction->ReceiverName = rs->getString(4);
		transaction->TransactionAmount = rs->getDouble(5);
		transaction->TransactionDate = rs->getString(6);
	}

	delete rs;
	delete ps;

	return transaction;
}
