#include "OrderManagement.h"
#include "DBConn.h"
#include "Menu.h"
#include <iostream>

using namespace std;

#pragma region Staff
void OrderManagement::viewOrder(int id){
	int ans;
	
	system("cls");
	cout << "View Order" << endl;

	cout << "0. Back to main page " << endl;
	cin >> ans;

	ans == 0 ? Menu().StaffMainMenu(id) : viewOrder(id);
}
void OrderManagement::AddOrder(int id){
	system("cls");
	cout << "Make Order" << endl;
}
void OrderManagement::editOrder(int id){
	int ans, enterId, confirmation;

	system("cls");
	cout << "Edit Order" << endl;

	cout << "List of order " << endl;
	cout << "Please choose the order ID that need to be change? " << endl;
	cin >> ans;

	cout << "Which part that you want to change ? " << endl;
	cout << "1. 2. 3. 4." << endl;
	cin >> enterId;

	cout << "List of the new item" << endl;
	cout << "Are you sure want to change this order? " << endl;
	cin >> confirmation;

	if (confirmation == 1) {
		cout << "The order have been successfully updated." << endl;
		system("pause");
		Menu().StaffMainMenu(id);
	}
	else {
		removeOrder(id);
	}
}
void OrderManagement::removeOrder(int id){
	int ans, confirmation;
	
	system("cls");
	cout << "Delete Order" << endl;

	cout << "List of order : " << endl;
	cout << "Please choose which ID that you want to delete? " << endl;
	cin >> ans;

	cout << "The List of order " << endl;
	cout << "Are you sure want to delete this order? " << endl;
	cout << "1. Confirm " << endl << "2. Cancel" << endl;
	cin >> confirmation;

	if (confirmation == 1) {
		cout << "The order have been successfully deleted." << endl;
		system("pause");
		Menu().StaffMainMenu(id);
	}
	else {
		removeOrder(id);
	}
}
#pragma endregion