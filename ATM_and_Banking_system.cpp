#include<iostream>
#include<string>
#include<fstream>
#include<istream>
#include<vector>
#include<cstdio>
#include <Windows.h>
#include <cstdlib>

using namespace std;

//predefining all the functions being used in program
void search(string);
void accountopening(int);
void file_creating(string, string, string);
void pin_code(string, string);
void account_check(int, int, string, string, string);
void update_balance(string, int);
void delete_account(string, string);

int main()
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "\n\n\n\t\t\t\t ______________\n\n\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	cout << "\t\t\t\t\tWelcome to National Bank!\n";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "\n\t\t\t\t ______________\n\n";
	// Change console text color to red
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

	// Change console background color to blue
	/*HWND console = GetConsoleWindow();
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
	HDC hdc = GetDC(console);
	RECT r;
	GetClientRect(console, &r);
	FillRect(hdc, &r, brush);*/

	// Rest of your code
	string CNIC;
	cout << endl << "Please Enter your CNIC to proceed: ";
	cin >> CNIC;
	int len = CNIC.length();
	if (len == 13)
	{
		search(CNIC);
	}
	else
	{
		cout << "entered cnic is wrong you cannot register\n";
	}
	

	system("pause");
	return 0;
}

// seraching for account
void search(string CNIC)
{
	fstream file;
	int choose;

	file.open(CNIC.c_str(), ios::in);
	// checking if file exists or not 
	if (!file)
	{
		//file does not exist
		cout << "Your account doesnot exist!\nDo you want to creat New Account?\nPress 1 for YES and 0 for NO: " << endl;
		cin >> choose;
		accountopening(choose);

	}

	else
	{
		//if account exists
		string data;

		while (1)
		{
			file >> data;
			if (file.eof())
				break;
			cout << "Account Holder: " << data << endl;         // printing account holder name from the file 

		}
		file.close();
		pin_code(data, CNIC);
	}
}

//creating account for a new user
void accountopening(int choose)
{

	string CNIC, PIN, name;
	int r = 0;

	//getting credentials from user

	switch (choose)
	{
	case 1:
	{
		cout << "Please Enter your 13-digit CNIC: \n";
		cin >> CNIC;


		while (r < 2)
		{
			int length = CNIC.length();
			if (length == 13)
			{
				//taking first and last name separately for convience
				cout << "Please Enter your Full Name: \n";
				cin >> name;

				cout << "Set 4-digit PIN to secure your account: ";
				// settng pin
				cin >> PIN;

				//creating files for above data
				file_creating(CNIC, name, PIN);

				break;//quitiing from while loop
			}
			else
			{
				cout << "Entered CNIC is wrong. Please enter CNIC again: ";
				cin >> CNIC;
				r++;
			}

		}
		//if user entered wrong cnic for more than 3 times then the program will end and will take a reload to start over again
		if (r == 2)
		{
			cout << "You have tried wrong CNIC multiple times, so the connection has been suspeded. Please try again later!\n";
		}

		break;
	}

	case 0:
	{
		cout << "THANK YOU for choosing National Bank,\nYour account will be craeted shortly!" << endl;
		break;
	}
	default:
	{
		cout << "INVALID INPUT!";
		break;
	}
	}
}

// craeting file for the new account credentials entered
void file_creating(string CNIC, string name, string PIN)
{
	//creating a new account
	ofstream file5, file6, file7;
	int acc_blnc = 1000;

	file5.open(CNIC.c_str(), ios::out);

	if (!file5.is_open()) // if file does not open
	{
		cout << "File not created.\n";
	}
	else // when file opens write account holder name into it
	{
		file5 << name << "\n";
	}
	file5.close();

	//PIN setting
	file6.open(name.c_str(), ios::out);
	if (file6.is_open())
	{
		file6 << PIN << "\n";
	}
	file6.close();

	//setting account balance to 1000 at start 
	//it will be updated if user wants to deposit more amount in bank
	file7.open(PIN.c_str(), ios::out);
	if (file7.is_open())
	{
		file7 << acc_blnc;
	}
	file7.close();


	cout << "Account created successfully! \n";
	cout << "We will take care of you, THANK YOU!";

}

void pin_code(string data, string CNIC)
{
	fstream file2;
	string pin, pin_check;
	int acc_check;
	int money, run = 0;

	file2.open(data.c_str(), ios::in);
	if (file2)
	{
		cout << "Enter PIN to confirm: ";
		cin >> pin;

		while (1)
		{
			file2 >> pin_check;     //getting the data presnt in file to pin_check variable for pin checking
			if (file2.eof())
				break;
			file2.close();
		}
		// checking pin to access account
		while (run < 2)
		{
			if (pin == pin_check)
			{
				fstream file8;
				file8.open(pin_check.c_str(), ios::in);
				while (1)
				{
					file8 >> money;              //getting the account balance in variable from file
					if (file8.eof())
						break;
					file8.close();
				}

				//giving user a set of functions he can perform while using this ATM
				cout << "Enter 1 to Debit, \nEnter 2 to Credit,  \nEnter 3 to check balance, \nEnter 4 to delete account: ";
				cin >> acc_check;

				account_check(acc_check, money, data, CNIC, pin_check);

				break;    //quitting from while loop
			}
			else
			{
				cout << "INCORRECT PIN! \nPlease Enter PIN again: ";
				cin >> pin;
				run++;

			}
		}
		if (run == 2)        //if wrong attempt inc 3 times the account should get suspended
		{
			cout << "YOUR ACOOUNT HAS BEEN SUSPENDED FOR ENTERING WRONG PIN MULTIPLE TIMES...\nPlease visit your nearest branch.\n";
		}


	}

}

void account_check(int acc_check, int money, string data, string CNIC, string pin_check)
{

	int amount;

	switch (acc_check)
	{
	case 1:
	{
		// withdrawl of cash
		cout << "Enter amount to be withdrawn: ";
		cin >> amount;

		//setting condition the withdrwal will only be possible when the amount to be withdrawn is less than account balance
		if (amount > money)
		{
			cout << "Low account balance\nPlease withdraw within the limits of your balance\n";
		}
		else if (amount == money)
		{
			money = money - amount;
			cout << "your account has been blocked because your remaining balance is zero\n";
		}
		else
		{
			money = money - amount;
			cout << "Your account has been debitted by given amount...\n";

		}
		//updating the account balance data after every transaction
		update_balance(pin_check, money);

		break;
	}
	case 2:
	{
		cout << "Enter amount to be creditted: "; // submission of ammount
		cin >> amount;
		money = money + amount;

		//updating the account balance data after every transaction
		update_balance(pin_check, money);

		cout << "The amount has been creditted to your account\n";
		break;
	}
	case 3:
	{
		//displaying the account balance to user
		cout << "Your Account Balance is = " << money << endl;
		cout << "THANK YOU for using National Bank!\n";
		break;
	}
	case 4:
	{
		//calling function to delete account on user assistance
		delete_account(CNIC, data);
		break;

	}
	default:
	{
		cout << "INVALID INPUT!\n";
		break;
	}

	}
}
void delete_account(string CNIC, string data)
{
	// deleting an account credentials
	int result = remove(CNIC.c_str());
	int result1 = remove(data.c_str());

	cout << "Account deleted successfully\n";

	cout << "THANK YOU for using National Bank!\nWe hope you leave with a smile\n";
}

void update_balance(string pin_check, int money)
{
	//updating the balnce data in file
	fstream read_file;

	//setting the line on which the update is to happen
	//int line_number = 1;

	read_file.open(pin_check.c_str(), ios::out);

	if (read_file.fail())
	{
		cout << "not found\n";  // file not found
	}

	read_file.close();

	ofstream write_file;
	write_file.open(pin_check.c_str(), ios::out);

	// writing updated data i.e account balance
	write_file << money << endl;


	write_file.close();


}
