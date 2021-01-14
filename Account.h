#include <string>
using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
	string AccountID, AccountUsername, AccountPassword, SecureWord;
	double AccountAmount, TransactionLimit;
};

#endif
