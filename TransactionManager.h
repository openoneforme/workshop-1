#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

class TransactionManager
{
public:
	int insertTransaction(Transaction* transaction);
	int updateTransaction(Transaction* transaction);
	Transaction* selectTransaction(string transaction);
	Transaction* latestTransaction();
};

#endif
