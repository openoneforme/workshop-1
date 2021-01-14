#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#include "Account.h"
#include "AccountManager.h"
#include "Customer.h"
#include "CustomerManager.h"
#include "Transaction.h"
#include "TransactionManager.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
	Account* account = new Account();
	AccountManager accountManager;
	Customer* customer = new Customer();
	CustomerManager customerManager;
	Transaction* transaction = new Transaction();
	TransactionManager transactionManager;

	string username, password, welcomeOption, secureWordConfirmation, accountID, receiverAccount, secureWord, admin;

	double transactionAmount, receiverBalance, giverBalance, transactionLimit, accountAmount;

	int status,homeOption,settingOption,adminOption,customerTel;

	int Set[] = { 7,7,7,7 };
	int counter = 2;
	char key, deleteOptionAdmin;

	bool check;

	bool intEntered = false;
	char input[255];

welcome:

	system("cls");

	cout << "Welcome to Login Menu!" << endl;

	for(int i = 0;;)
	{

		gotoxy(2, 2);
		color(Set[0]);
		cout << "login";

		gotoxy(2, 3);
		color(Set[1]);
		cout << "signup";

		gotoxy(2, 4);
		color(Set[2]);
		cout << "exit";

		key = _getch();
		if (key == 8)
		{
			goto AdminLogin;
		}
		if (key == 72 && (counter >= 2 && counter <= 3))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 2))
		{
			counter++;
		}
		if (key == '\r')
		{
			if (counter == 1)
				goto login;
			if (counter == 2)
				goto signup;
			if (counter == 3)
				return 0;
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		if (counter == 1)
		{
			Set[0] = 10;
		}
		if (counter == 2)
		{
			Set[1] = 10;
		}
		if (counter == 3)
		{
			Set[2] = 10;
		}
	}

login:

	system("cls");

	cout << "Username : ";
	cin >> username;
	//check exist
	goto usernameAttempt;

signup:

	system("cls");

	account->AccountID = accountManager.RandomAccountIDGenerator();
	accountID = account->AccountID;
	check = accountManager.checkAccountID(account->AccountID);
	if (check == true) {
		goto signup;
	}

	cout << "\nUsername : ";
	cin >> account->AccountUsername;
	check = accountManager.checkAccountUsername(account->AccountUsername);
	if (check == true) {
		cout << "This Username is already existed." << endl;
		system("pause");
		goto signup;
	}

	cout << "\nPassword : ";
	cin >> account->AccountPassword;

	do {
		cout << "Current Account Amount : ";
		cin >> input;
		string s = input;
		accountAmount = atoi(s.c_str());
		if (accountAmount == 0)
			cout << "\nOnly Number!";
		else
		{
			account->AccountAmount = accountAmount;
			intEntered = true;
		}

	} while (!intEntered);

	account->TransactionLimit = 1000.00;

	cout << "\nSecure Word : ";
	cin >> account->SecureWord;

	status = accountManager.insertAccount(account);

	goto updateCustomerProfile;

updateCustomerProfile:
	
	system("pause");

	system("cls");

	cout << "\nCustomerName : ";
	cin >> customer->CustomerName;

	cout << "\nCustomerAddress : ";
	cin >> customer->CustomerAddress;

	do {
		cout << "\nCustomerTel : ";
		cin >> input;
		string s = input;
		customerTel = atoi(s.c_str());
		if (customerTel == 0)
			cout << "\nOnly Number!";
		else
		{
			customer->CustomerTel = customerTel;
			intEntered = true;
		}

	} while (!intEntered);

	cout << "\nM = 0, F = 1\nGender : ";
	cin >> customer->Gender;

	cout << "\nNRIC (ex. 010101010101) : ";
	cin >> customer->NRIC;

	cout << "\nCustomerEmail : ";
	cin >> customer->CustomerEmail;

	customer->AccountID = accountID;

	cout << endl << endl;

	status = customerManager.insertCustomer(customer);

	if (status != 0)
		cout << "Successfully added a new account." << endl;
	else
		cout << "Unable to add a new account." << endl;

	system("pause");

	goto welcome;

usernameAttempt:

	system("cls");

	account = accountManager.selectAccountUsername(username);

	if (username == account->AccountUsername)
	{
		account = accountManager.selectAccountUsername(username);
		cout << "Is this your secure word?\n\n" << account->SecureWord << endl << endl;
	}
	Set[0] = 7;
	Set[1] = 7;
	Set[2] = 7;
	for (int i = 0;;)
	{

		gotoxy(2, 4);
		color(Set[0]);
		cout << "Yes";

		gotoxy(2, 5);
		color(Set[1]);
		cout << "No";

		gotoxy(2, 6);
		color(Set[2]);
		cout << "exit";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 3))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 2))
		{
			counter++;
		}
		if (key == '\r')
		{
			if (counter == 1)
				goto passwordAttempt;
			if (counter == 2)
				goto login;
			if (counter == 3)
				return 0;
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		if (counter == 1)
		{
			Set[0] = 10;
		}
		if (counter == 2)
		{
			Set[1] = 10;
		}
		if (counter == 3)
		{
			Set[2] = 10;
		}
	}

passwordAttempt:

	system("cls");

	cout << "Password : ";
	cin >> password;
	account = accountManager.selectAccountPassword(password);

	if (password == account->AccountPassword)
		goto home;
	else
		goto login;

home:

	system("cls");

	Set[0] = 7;
	Set[1] = 7;
	Set[2] = 7;
	Set[3] = 7;

	cout << "Welcome to Home!" << endl << endl;

	for (int i = 0;;)
	{

		gotoxy(2, 3);
		color(Set[0]);
		cout << "Account Summary";

		gotoxy(2, 4);
		color(Set[1]);
		cout << "Setting";

		gotoxy(2, 5);
		color(Set[2]);
		cout << "Transaction";

		gotoxy(2, 8);
		color(Set[3]);
		cout << "Log Out";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 3))
		{
			counter++;
		}
		if (key == '\r')
		{
			if (counter == 1)
				goto accountSummary;
			if (counter == 2)
				goto setting;
			if (counter == 3)
				goto Transaction;
			if (counter == 4)
				return 0;
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		if (counter == 1)
		{
			Set[0] = 10;
		}
		if (counter == 2)
		{
			Set[1] = 10;
		}
		if (counter == 3)
		{
			Set[2] = 10;
		}
		if (counter == 4)
		{
			Set[3] = 10;
		}
	}

accountSummary:

	system("cls");
	account = accountManager.selectAccountUsername(username);
	cout << "~~~~~~~~~~Account Summary~~~~~~~~~~" << endl << endl;
	cout << "Account ID        : " << account->AccountID << endl;
	cout << "Account Balance   : RM " << account->AccountAmount << endl;
	cout << "Transaction Limit : RM " << account->TransactionLimit << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	cout << "Enter '0' for back to home" << endl;
	cout << ">>";
	cin >> homeOption;
	if (homeOption == 0)
		goto home;

setting:

	system("cls");

	cout << "Setting" << endl << endl;

	cout << "[1] Change Password          | [2] Change Secure Word\n"
		 << "[3] Change Transaction Limit | [0] Back" << endl << endl;

	cout << ">>>";
	cin >> settingOption;

	switch (settingOption)
	{
	case 1:
		goto changePassword;
	case 2:
		goto changeSecureWord;
	case 3:
		goto changeTransactionLimit;
		//admin
	case 0:
		goto home;
	}

changePassword:

	system("cls");
	cout << "\nEnter Old Password : ";
	cin >> password;
	check = accountManager.checkAccountPassword(password,username);
	if (check == true) {
		cout << "\nEnter New Password : ";
		cin >> password;
		status = accountManager.updateAccountPassword(password, username);
	}
	else
	{
		cout << "\nWRONG PASSWORD!!!\n";
		system("pause");
	}
	goto setting;

changeSecureWord:

	system("cls");
	cout << "\nEnter Old Secure Word : ";
	cin >> secureWord;
	check = accountManager.checkAccountSecureWord(secureWord, username);
	if (check == true) {
		cout << "\nEnter New Secure Word : ";
		cin >> secureWord;
		status = accountManager.updateAccountSecureWord(secureWord, username);
	}
	else
	{
		cout << "\nWRONG SECURE WORD!!!\n";
		system("pause");
	}
	goto setting;

changeTransactionLimit:

	system("cls");
	cout << "\nEnter New Transaction Limit : ";
	cin >> transactionLimit;
	status = accountManager.updateAccountTransactionLimit(transactionLimit, username);
	goto setting;
	
Transaction:

	system("cls");

	cout << "Press Backspace to go to Home Page" << endl;
	cout << "Press anykey to continue" << endl;

	key = _getch();
	if (key == 8)
	{
		goto home;
	}
	else
	{
		cout << "\nAccount ID : ";
		cin >> accountID;
		transaction->AccountID = accountID;

		cout << "\nReceiver Account : ";
		cin >> receiverAccount;
		transaction->ReceiverAccount = receiverAccount;

		cout << "\nReceiver Name : ";
		cin >> transaction->ReceiverName;

		cout << "\nTransaction Amount : ";
		cin >> transactionAmount;
		account = accountManager.selectAccountUsername(username);
		if ((transactionAmount <= account->TransactionLimit) && (transactionAmount > 0))
		{
			transaction->TransactionAmount = transactionAmount;

			cout << endl << endl;

			status = transactionManager.insertTransaction(transaction);

			account = accountManager.selectAccountID(accountID);
			giverBalance = account->AccountAmount - transactionAmount;
			status = accountManager.updateAccountTransaction(giverBalance, accountID);

			account = accountManager.selectAccountID(receiverAccount);
			receiverBalance = account->AccountAmount + transactionAmount;
			status = accountManager.updateAccountTransaction(receiverBalance, receiverAccount);

			transaction = transactionManager.latestTransaction();
			cout << "Transaction ID     : " << transaction->TransactionID << endl;
			cout << "Account ID         : " << transaction->AccountID << endl;
			cout << "Receiver Account   : " << transaction->ReceiverAccount << endl;
			cout << "Receiver Name      : " << transaction->ReceiverName << endl;
			cout << "Transaction Amount : " << transaction->TransactionAmount << endl;
			cout << "Transaction Date   : " << transaction->TransactionDate << endl;

			system("pause");
			goto home;
		}
		else
		{
			cout << "Invalid Amount :(" << endl;
			system("pause");
			goto home;
		}
	}

AdminLogin:

	system("cls");
	cin >> admin;
	if (admin == "admin")
	{
		system("cls");
		cin >> admin;
		if (admin == "admin12345")
		{
			goto AdminPage;
		}
	}

AdminPage:

	system("cls");
	cout << "Welcome To Admin Page!" << endl << endl;
	cout << "[1] Change Account Username" << endl;
	cout << "[2] Delete Account" << endl;
	cout << "[3] Exit" << endl;
	cin >> adminOption;
	switch (adminOption)
	{
	case 1:
		goto changeUsername;
	case 2:
		goto deleteAccount;
	case 0:
	{
		system("pause");
		return 0;
	}
	}

changeUsername:

	system("cls");

	cout << "\nAccount ID : ";
	cin >> accountID;

	account->AccountID = accountID;

	check = accountManager.checkAccountID(account->AccountID);
	if (check == true) {
		cout << "\nEnter Old Username : ";
		cin >> username;
		check = accountManager.checkAccountUsername(username);
		if (check == true) {
			cout << "\nEnter New Username : ";
			cin >> username;
			status = accountManager.updateAccountUsernameAdmin(username, accountID);
			cout << "You Already Change " << accountID << " username into " << username << endl;
			system("pause");
		}
		else
		{
			cout << "\nWRONG USERNAME!!!\n";
			system("pause");
		}
		goto AdminPage;
	}
	else
	{
		cout << "Invalid Account ID" << endl;
		system("pause");
		goto changeUsername;
	}
	goto AdminPage;

deleteAccount:

	system("cls");

	cout << "\nAccount ID : ";
	cin >> accountID;

	account->AccountID = accountID;

	check = accountManager.checkAccountID(account->AccountID);
	if (check == true) {
		cout << "Are you sure want to delete this account?" << endl;
		cout << "Press ENTER to delete!" << endl;
		deleteOptionAdmin = _getch();
		if (deleteOptionAdmin == '\r') {
			status = accountManager.deleteAccountAdmin(accountID);
			customerManager.deleteCustomerAccountAdmin(accountID);
			cout << "You Already Delete " << accountID << " account!" << endl;
			system("pause");
		}
		else
			goto deleteAccount;
	}
	else
	{
		cout << "Invalid Account ID" << endl;
		system("pause");
		goto deleteAccount;
	}
	goto AdminPage;

}
