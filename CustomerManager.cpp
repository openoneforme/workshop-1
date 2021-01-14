#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Customer.h"
#include "CustomerManager.h"

int CustomerManager::insertCustomer(Customer* customer)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO customer(CustomerName, CustomerAddress, CustomerTel, Gender, NRIC, CustomerEmail, AccountID) VALUES (?, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, customer->CustomerName);
	ps->setString(2, customer->CustomerAddress);
	ps->setString(3, customer->CustomerTel);
	ps->setBoolean(4, customer->Gender);
	ps->setString(5, customer->NRIC);
	ps->setString(6, customer->CustomerEmail);
	ps->setString(7, customer->AccountID);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}


Customer* CustomerManager::selectCustomer(string customerID)
{
	Customer* customer = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM account WHERE AccountUsername = ?");

	ps->setString(1, customerID);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		customer = new Customer();
		customer->CustomerID = rs->getInt(1);
		customer->CustomerName = rs->getString(2);
		customer->CustomerAddress = rs->getString(3);
		customer->CustomerTel = rs->getString(4);
		customer->Gender = rs->getBoolean(5);
		customer->NRIC = rs->getString(6);
		customer->CustomerEmail = rs->getString(7);
		customer->AccountID = rs->getString(8);
	}

	delete rs;
	delete ps;

	return customer;
}

int CustomerManager::deleteCustomerAccountAdmin(string accountID)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM customer WHERE AccountID=?");

	ps->setString(1, accountID);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}
