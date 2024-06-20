#include "Menu.h"
#include "Login.h"
#include "DBConn.h"
#include "Sparepart.h"
#include "OrderManagement.h"

#include <iostream>
#include <conio.h>

using namespace std;

string getPassword() {
	string password;
	char ch;

	// Read each character entered by the user
	while ((ch = _getch()) != '\r') { // '\r' is the carriage return character (Enter key)
		if (ch == '\b') { // Handle backspace
			if (!password.empty()) {
				cout << "\b \b"; // Erase the last asterisk
				password.pop_back(); // Remove last character from the password
			}
		}
		else {
			password += ch;
			cout << '*'; // Print an asterisk
		}
	}

	cout << endl;
	return password;
}

void Menu::MainPage()
{
	int ans, role;
	string username, password, test;
	system("cls");
	cout << "WELCOME TO MOTORCYCLE SPAPE PART MANAGEMENT SYSTEM" << endl;

	cout << "1.	Login" << endl;
	cout << "2.	Register" << endl;
	cout << "3.	Exit" << endl;

	cout << "\nyour choice : ";
	cin >> ans;

	if (ans == 1) {
		system("cls");
		cout << "Username : "; 
		getline(cin >> ws, username);  
		cout << "Password : ";
		//cin >> password;
		password = getPassword(); 

		int Staffid = DBConn().authenticateStaff(username, password);
		int Supplierid = DBConn().authenticateSupplier(username, password);

		if (Staffid != NULL) {
			cout << "\nLogin successful!" << endl;
			system("pause");

			if (DBConn().isStaff(Staffid) == true)
				StaffMainMenu(Staffid);
		}
		else if (Supplierid != NULL) {
			cout << "\nLogin successful!" << endl;
			system("pause");

			if (DBConn().isSupplier(Supplierid == true))
				SupplierMainMenu(Supplierid);
		}
		else {
			cout << "\nLogin failed. Invalid username or password." << endl;
 			system("pause");
			MainPage();
		}
	}
	else if (ans == 2) {
		system("cls");
		cout << "Are you want to continue?" << endl;
		//cout << "1.	Supplier" << endl;
		cout << "1.	Staff" << endl;
		cout << "0.	Back" << endl;
		cout << "\nYour Choice : ";
		cin >> role;

		/*if (role == 1)
			Login().SupplierRegisteration();
		else */if (role == 1)
			Login().StaffRegisteration();
		else
			MainPage();
	}
	else {
		exit(1);
	}
}

#pragma region Supplier
void Menu::SupplierMainMenu(int id) {
	system("cls");
	int ans;
	
	cout << "Welcome to Supplier Main Menu" << endl;
	cout << "Supplier Name : " + DBConn().getSupplierUserName(id) << endl;

	cout << "\n1. View Stock" << endl;
	cout << "2. Add Stock" << endl;
	cout << "3. Remove Spare Part" << endl;
	cout << "4. Edit Spare Part" << endl;
	cout << "5. View Order" << endl;
	cout << "6. View Monthly Report" << endl;
	cout << "0. Logout" << endl;

	cout << "\nChoose your option : ";
	cin >> ans;

	if (ans == 6) {
		MainPage();
	}
}

#pragma endregion

#pragma region Staff
void Menu::StaffMainMenu(int id) {
	system("cls");
	string ans;

	cout << "Welcome to Staff Main Menu" << endl;
	cout << "\nStaff Name : " + DBConn().getStaffUserName(id) << endl;

	cout << "\n1. View Stock" << endl;
	cout << "2. Make Order" << endl;
	cout << "3. Remove Spare Part" << endl;
	cout << "4. Edit Spare Part" << endl;
	cout << "5. View Order" << endl;
	cout << "6. View Monthly Report" << endl;
	cout << "7. Item Did Not Pay Yet" << endl;
	cout << "0. Logout" << endl;

	cout << "\nChoose your option : ";
	cin >> ans;

	if (ans == "1") {
		Sparepart().StaffViewStock(id);
	}
	else if (ans == "2") {
		OrderManagement().listOfSupplier(id);
	}
	else if (ans == "3") {
		Sparepart().DeleteStock(id);
		//OrderManagement().removeOrder(id);
	}
	else if (ans == "4") {
		Sparepart().UpdateStock(id);
		//OrderManagement().editOrder(id);
	}
	else if (ans == "5") {
		OrderManagement().viewOrder(id);
	}
	else if(ans == "6") {
		Sparepart().ViewMonthlyReport(id);
	}
	else if (ans == "7") {
		OrderManagement().MakePayment(id);
	}
	else if (ans == "0") {
		MainPage();
	}
	else {
		cout << "You enter invalid number . Please Choose the correct one" << endl;
		system("pause");
		StaffMainMenu(id);
	}
}
#pragma endregion