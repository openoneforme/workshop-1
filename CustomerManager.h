#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

class CustomerManager
{
public:
	int insertCustomer(Customer* customer);
	int updateCustomer(Customer* customer);
	Customer* selectCustomer(string customer);
	int deleteCustomerAccountAdmin(string accountID);
};

#endif
