#include "Menu.h"
#include "Login.h"
#include "DBConn.h"
#include "Sparepart.h"
#include "OrderManagement.h"

#include <iostream>

using namespace std;

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
		cin >> username;
		cout << "Password : ";
		cin >> password;

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
		cout << "What role are you?" << endl;
		cout << "1.	Supplier" << endl;
		cout << "2.	Staff" << endl;
		cout << "\nYour Choice : ";
		cin >> role;

		if (role == 1)
			Login().SupplierRegisteration();
		else
			Login().StaffRegisteration();
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
	cout << "3. Remove Stock" << endl;
	cout << "4. Edit Stock" << endl;
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
	int ans;

	cout << "Welcome to Staff Main Menu" << endl;
	cout << "\nStaff Name : " + DBConn().getStaffUserName(id) << endl;

	cout << "\n1. View Stock" << endl;
	cout << "2. Make Order" << endl;
	cout << "3. Remove Order" << endl;
	cout << "4. Edit Order" << endl;
	cout << "5. View Order" << endl;
	cout << "6. View Monthly Report" << endl;
	cout << "0. Logout" << endl;

	cout << "\nChoose your option : ";
	cin >> ans;

	if (ans == 1) {
		Sparepart().StaffViewStock(id);
	}
	else if (ans == 2) {
		OrderManagement().AddOrder(id);
	}
	else if (ans == 3) {
		OrderManagement().removeOrder(id);
	}
	else if (ans == 4) {
		OrderManagement().editOrder(id);
	}
	else if (ans == 5) {
		OrderManagement().viewOrder(id);
	}
	else if(ans == 6) {
		Sparepart().ViewMonthlyReport(id);
	}
	else if (ans == 0) {
		MainPage();
	}
	else {
		cout << "You enter invalid number . Please Choose the correct one" << endl;
		system("pause");
		StaffMainMenu(id);
	}
}
#pragma endregion