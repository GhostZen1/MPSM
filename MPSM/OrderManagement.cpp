#include "OrderManagement.h"
#include "DBConn.h"
#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

struct Items {
	int ItemID;
	int SupplierID;
	char ItemName[100];
	char SupplierName[100];
	char ItemType[100];
	char ItemBrand[100];
	char ItemPrice[100];
};

const int columnWidth = 17;

const int MAX_CHOICES = 100;
int* choices = new int[MAX_CHOICES];
int* quantities = new int[MAX_CHOICES];
int numChoices = 0;

#pragma region Staff
void OrderManagement::viewOrder(int id){
	int ans, itemCount = 0;
	
	system("cls");

	cout << "List of order " << endl; 
	DBConn::Order* OrderList = DBConn().ViewOrder(id); 
	cout << setw(columnWidth) << "Item ID"  
		<< setw(columnWidth) << "Product Name" 
		<< setw(columnWidth) << "Quantity" 
		<< setw(columnWidth) << "Staff Name" 
		<< setw(columnWidth) << "Total Price" << endl; 

	for (int i = 0; i < sizeof(OrderList); i++) {
		while (OrderList[itemCount].OrderId != 0) { 
			cout << setw(columnWidth) << OrderList[itemCount].OrderItemId  
				<< setw(columnWidth) << OrderList[itemCount].ProductName 
				<< setw(columnWidth) << OrderList[itemCount].Quantity 
				<< setw(columnWidth) << OrderList[itemCount].StaffName 
				<< setw(columnWidth) << OrderList[itemCount].totalPrice << endl; 
			itemCount++; 
		}
	}

	cout << "\n0. Back to main page " << endl;
	cin >> ans;

	ans == 0 ? Menu().StaffMainMenu(id) : viewOrder(id);
}
void OrderManagement::AddOrder(int id){
	int itemCount = 0, ans, choose, qtt;
	string addMore, confirm;
	double price = 0;

	system("cls");
	
	cout << "Make Order" << endl;
	DBConn::Item* Sparepart = DBConn().ListOfSparepart();
	cout << "\nList of all sparepart " << endl << endl;

	cout << setw(columnWidth) << "Item ID"
     << setw(columnWidth) << "Item Name"
     << setw(columnWidth) << "Supplier Name"
     << setw(columnWidth) << "Item Type"
     << setw(columnWidth) << "Item Brand"
     << setw(columnWidth) << "Item Price" << endl;

	for (int i = 0; i < sizeof(Sparepart); i++) {
		while (Sparepart[itemCount].ItemID != 0) { 
			cout << setw(columnWidth) << Sparepart[itemCount].ItemID  
				 << setw(columnWidth) << Sparepart[itemCount].ItemName  
				 << setw(columnWidth) << Sparepart[itemCount].SupplierName  
				 << setw(columnWidth) << Sparepart[itemCount].ItemType   
				 << setw(columnWidth) << Sparepart[itemCount].ItemBrand  
				 << setw(columnWidth) << Sparepart[itemCount].ItemPrice  << endl;
			itemCount++;
		} 
	}

	cout << "\n1. Continue" << endl;
	cout << "0. Back to Main Page" << endl;
	cin >> ans;

	if (ans == 0) {
		Menu().StaffMainMenu(id);
	}
	else if (ans == 1) {
		do {
			cout << "Pleease choose an item id to select :";
			cin >> choose;

			cout << "Please enter the amount that you want : ";
			cin >> qtt;

			choices[numChoices] = choose;
			quantities[numChoices] = choose;
			numChoices++;

			cout << "Do you want to add more ? (Y/N)" << endl;
			cin >> addMore;
		} while (addMore == "y" || addMore == "Y");

		system("cls");

		cout << setw(columnWidth) << "Item ID"  
			<< setw(columnWidth) << "Item Name" 
			<< setw(columnWidth) << "Supplier Name" 
			<< setw(columnWidth) << "Item Type" 
			<< setw(columnWidth) << "Item Brand" 
			<< setw(columnWidth) << "Item Price" 
			<< setw(columnWidth) << "Quantities" << endl;

		for (int i = 0; i < numChoices; i++) {
			cout << setw(columnWidth) << choices[i] 
				<< setw(columnWidth) << Sparepart[i].ItemName  
				<< setw(columnWidth) << Sparepart[i].SupplierName  
				<< setw(columnWidth) << Sparepart[i].ItemType 
				<< setw(columnWidth) << Sparepart[i].ItemBrand 
				<< setw(columnWidth) << Sparepart[i].ItemPrice 
				<< setw(columnWidth) << quantities[i] << endl;

			price += quantities[i] * stod(Sparepart[i].ItemPrice);
		}

		DBConn().MakeOrder(id, price);
		int orderID = DBConn().getOrderID(price);
		for (int i = 0; i < numChoices; i++) {
			DBConn().MakeOrderItem(orderID, Sparepart[i].ItemID, quantities[i]);
		}

		delete[] choices;
		delete[] quantities; 
		delete[] Sparepart;

		cout << "You have been successfully make this order." << endl; 
		system("pause"); 
		Menu().StaffMainMenu(id); 
	}
	else {
		cout << "You enter the wrong number";
		system("pause");
		AddOrder(id);
	}
}
void OrderManagement::editOrder(int id){
	int ans, enterId, confirmation, itemCount = 0;

	system("cls");
	cout << "Edit Order" << endl;

	cout << "\nList of order " << endl;
	DBConn::Order* OrderList = DBConn().ViewOrder(id);
	cout << setw(columnWidth) << "Order ID"
		<< setw(columnWidth) << "Item ID"
		<< setw(columnWidth) << "Product Name"
		<< setw(columnWidth) << "Quantity"
		<< setw(columnWidth) << "Staff Name"
		<< setw(columnWidth) << "Total Price" << endl;

	for (int i = 0; i < sizeof(OrderList); i++) {
		while (OrderList[itemCount].OrderId != 0) {
			cout << setw(columnWidth) << OrderList[itemCount].OrderId
				<< setw(columnWidth) << OrderList[itemCount].OrderItemId
				<< setw(columnWidth) << OrderList[itemCount].ProductName
				<< setw(columnWidth) << OrderList[itemCount].Quantity
				<< setw(columnWidth) << OrderList[itemCount].StaffName
				<< setw(columnWidth) << OrderList[itemCount].totalPrice << endl;
			itemCount++;
		}
	}
	cout << "\nPlease choose the order ID that need to be change? " << endl;
	cin >> ans;

	cout << "Which part that you want to change ? " << endl;
	cout << "1. 2. 3. 4." << endl;
	cin >> enterId;

	cout << "List of the new item" << endl;
	cout << "Are you sure want to change this order? (y/n)" << endl;
	cin >> confirmation;

	if (confirmation == 'y' || confirmation == 'Y') {
		cout << "The order have been successfully updated." << endl;
		system("pause");
		Menu().StaffMainMenu(id);
	}
	else {
		removeOrder(id);
	}
}
void OrderManagement::removeOrder(int id){
	int ans, confirmation, itemCount = 0;
	
	system("cls");
	cout << "Delete Order" << endl;

	cout << "\nList of order " << endl;
	DBConn::Order* OrderList = DBConn().ViewOrder(id); 
	cout << setw(columnWidth) << "Item ID" 
		<< setw(columnWidth) << "Product Name" 
		<< setw(columnWidth) << "Quantity" 
		<< setw(columnWidth) << "Staff Name" 
		<< setw(columnWidth) << "Total Price" << endl; 

	for (int i = 0; i < sizeof(OrderList); i++) { 
		while (OrderList[itemCount].OrderId != 0) { 
			cout << setw(columnWidth) << OrderList[itemCount].OrderItemId 
				<< setw(columnWidth) << OrderList[itemCount].ProductName 
				<< setw(columnWidth) << OrderList[itemCount].Quantity 
				<< setw(columnWidth) << OrderList[itemCount].StaffName 
				<< setw(columnWidth) << OrderList[itemCount].totalPrice << endl; 
			itemCount++; 
		}
	}
	cout << "\nPlease choose which ID that you want to delete? " << endl;
	cin >> ans;

	cout << "The List of order " << endl;
	cout << "Are you sure want to delete this order? (y/n)" << endl;
	cin >> confirmation;

	if (confirmation == 'y' || confirmation == 'Y') {
		DBConn().DeleteOrder(ans);
		cout << "The order have been successfully deleted." << endl;
		system("pause");
		Menu().StaffMainMenu(id);
	}
	else {
		removeOrder(id);
	}
}
#pragma endregion