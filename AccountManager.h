#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

class AccountManager
{
public:
	int insertAccount(Account* account);
	int updateAccountPassword(string accountPassword, string accountID);
	int updateAccountTransaction(double balance, string accountID);
	int updateAccountSecureWord(string secureWord, string username);
	int updateAccountTransactionLimit(double transactionLimit, string username);
	Account* selectAccountID(string AccountID);
	Account* selectAccountUsername(string AccountUsername);
	Account* selectAccountPassword(string AccountPassword);
	bool checkAccountID(string accountID);
	bool checkAccountUsername(string accountUsername);
	bool checkAccountPassword(string password, string username);
	bool checkAccountSecureWord(string secureWord, string username);
	string RandomAccountIDGenerator();
	int updateAccountUsernameAdmin(string username, string accountID);
	int deleteAccountAdmin(string accountID);
};

#endif
