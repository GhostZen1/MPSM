#include "Login.h"
#include "Menu.h"
#include "DBConn.h"

#include <iostream>

using namespace std;

#pragma region Supplier
void Login::SupplierRegisteration() {
	string supplierName, supplierAddress, supplierUsername, supplierPassword;
	system("cls");
	cout << "Supplier Registeration Menu" << endl;
	cout << "Please enter your details below" << endl;
	cout << "Enter your shop name : ";
	getline(cin >> ws, supplierName);
	cout << "Enter your address : ";
	getline(cin >> ws, supplierAddress);
	cout << "Enter your Username : ";
	cin >> supplierUsername;
	cout << "Enter your Password : ";
	cin >> supplierPassword;

	DBConn().SupplierRegisteration(supplierName, supplierAddress, supplierUsername, supplierPassword);
	cout << "Register Successfully" << endl;
	system("pause");
	Menu().MainPage();
}
#pragma endregion

#pragma region Staff
void Login::StaffRegisteration() {
	string staffName, staffUsername, staffPassword;
	int staffGender;
	system("cls");
	cout << "Staff Registeration Menu" << endl;
	cout << "Please enter your details below" << endl;
	cout << "Enter your name : ";
	getline(cin >> ws, staffName);
	cout << "Enter Your gender by choosing the number :" << endl;
	cout << "0.Female" << endl;
	cout << "1.Male" << endl;
	cout << "\nYour Choice : ";
	cin >> staffGender;
	cout << "Enter your Username : ";
	cin >> staffUsername;
	cout << "Enter your Password : ";
	cin >> staffPassword;

	DBConn().Staffregisteration(staffName, staffGender, staffUsername, staffPassword);
	cout << "Register Successfully" << endl;
	system("pause");
	Menu().MainPage();
}
#pragma endregion