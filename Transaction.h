#include <string>
using namespace std;

#ifndef TRANSACTION_H
#define TRANSACTION_H

class Transaction
{
public:
	string ReceiverAccount, ReceiverName, AccountID, TransactionDate;
	int TransactionID, TransactionType;
	double TransactionAmount;
};

#endif
