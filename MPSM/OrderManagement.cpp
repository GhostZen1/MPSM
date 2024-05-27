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

const int columnWidth = 19;

const double MAX_CHOICES = 100;
int* choices = new int[MAX_CHOICES];
int* quantities = new int[MAX_CHOICES];
double* ItemPrice = new double[MAX_CHOICES];
//int numChoices = 0;

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
	int ans, choose, qtt, numChoices = 0;
	string addMore;
	double price = 0;

	system("cls");

	cout << "Make Order" << endl;

	DBConn::SparepartList sparepartList = DBConn().ListOfSparepart();
	DBConn::Item* Sparepart = sparepartList.items;
	int itemCount = sparepartList.count;

	cout << "\nList of all spare parts " << endl << endl;

	cout << setw(columnWidth) << "Item ID"
		<< setw(columnWidth) << "Item Name"
		<< setw(columnWidth) << "Supplier Name"
		<< setw(columnWidth) << "Item Type"
		<< setw(columnWidth) << "Item Brand"
		<< setw(columnWidth) << "Item Price"
		<< setw(columnWidth) << "Quantity" << endl;

	for (int i = 0; i < itemCount; ++i) {
		cout << setw(columnWidth) << Sparepart[i].ItemID
			<< setw(columnWidth) << Sparepart[i].ItemName
			<< setw(columnWidth) << Sparepart[i].SupplierName
			<< setw(columnWidth) << Sparepart[i].ItemType
			<< setw(columnWidth) << Sparepart[i].ItemBrand
			<< setw(columnWidth) << Sparepart[i].ItemPrice
			<< setw(columnWidth) << Sparepart[i].quantity << endl;
	}

	cout << "\n1. Continue" << endl;
	cout << "0. Back to Main Page" << endl;
	cin >> ans;

	if (ans == 0) {
		Menu().StaffMainMenu(id);
	}
	else if (ans == 1) {
		do {
			cout << "Please choose an item ID to select: ";
			cin >> choose;

			cout << "Please enter the amount that you want: ";
			cin >> qtt;

			bool found = false;
			for (int i = 0; i < itemCount; ++i) {
				if (Sparepart[i].ItemID == choose) {
					if (qtt <= Sparepart[i].quantity) {
						choices[numChoices] = choose; 
						quantities[numChoices] = qtt;  
						ItemPrice[numChoices] = qtt * stod(Sparepart[i].ItemPrice); 
						numChoices++;
						found = true;
					}
					else {
						cout << "The amount is more than the available quantity" << endl;
						AddOrder(id);
					}
				}
			}
			if (!found) {
				cout << "Item ID not found" << endl;
			}

			cout << "Do you want to add more? (Y/N): ";
			cin >> addMore;
		} while (addMore == "y" || addMore == "Y");

		system("cls");

		cout << setw(columnWidth) << "Item ID" 
			<< setw(columnWidth) << "Item Name" 
			<< setw(columnWidth) << "Supplier Name" 
			<< setw(columnWidth) << "Item Type" 
			<< setw(columnWidth) << "Item Brand" 
			<< setw(columnWidth) << "Item Price" 
			<< setw(columnWidth) << "Quantities" 
			<< setw(columnWidth) << "Total Price" << endl; 

		for (int i = 0; i < numChoices; i++) { 
			int itemId = choices[i];  
			for (int j = 0; j < itemCount; j++) { 
				if (Sparepart[j].ItemID == itemId) { 
					cout << setw(columnWidth) << itemId 
						<< setw(columnWidth) << Sparepart[j].ItemName  
						<< setw(columnWidth) << Sparepart[j].SupplierName 
						<< setw(columnWidth) << Sparepart[j].ItemType 
						<< setw(columnWidth) << Sparepart[j].ItemBrand 
						<< setw(columnWidth) << Sparepart[j].ItemPrice 
						<< setw(columnWidth) << quantities[i]  
						<< setw(columnWidth) << ItemPrice[i] << endl;

					price += quantities[i] * stod(Sparepart[j].ItemPrice); 
					break;
				}
			}
		}

		DBConn().MakeOrder(id, price); 
		int orderID = DBConn().getOrderID(price); 
		for (int i = 0; i < numChoices; i++) {  
			int itemId = choices[i];
			for (int j = 0; j < itemCount; j++) {
				if (Sparepart[j].ItemID == itemId) {
					DBConn().MakeOrderItem(orderID, Sparepart[i].ItemID, quantities[i], ItemPrice[i]);
					int SparepartID = DBConn().CheckSparepart(Sparepart[j].ItemName); 
					if (SparepartID != 0) {
						/*int balance = DBConn().CheckSparepartBalance(SparepartID);
						int newStockBalance = balance + quantities[i];*/
						DBConn().UpdateSparepart(SparepartID, quantities[i]);
					}
					else {
                        DBConn().InsertSparepart(id, Sparepart[j].ItemName, Sparepart[j].ItemType, Sparepart[j].ItemBrand, stod(Sparepart[j].ItemPrice), quantities[i]);
                    }
					DBConn().UpdateProduct(itemId, quantities[i]); 
				}
			}
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
	int ansProName, enterId, enterPart, itemCount = 0, ansQuantity, oldId, OrderId;
	double newPrice, Price;
	string confirmationChange, confirmation;

	do {
		system("cls");
		cout << "Edit Order" << endl;

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
					<< setw(columnWidth) << OrderList[itemCount].Price << endl;
				itemCount++;
			}
		}

		cout << "\nWhich order that you want to change ? " << endl;
		cin >> enterId;

		cout << "\nWhich part that you want to change ? \n1. Product Name\n2. Quantity" << endl;
		cin >> enterPart; 

		DBConn::SparepartList SparepartList = DBConn().ListOfSparepart();
		DBConn::Item* Sparepart = SparepartList.items;

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
					<< setw(columnWidth) << Sparepart[itemCount].ItemPrice << endl;
				itemCount++;
			}
		}
		if (enterPart == 1) {
			cout << "\nYour Product Name : " + OrderList[enterId].ProductName << endl;
			cout << "\nNew Product Name (Insert ID) : ";
			cin >> ansProName;
		}
		else if (enterPart == 2) {
			cout << "\nQuantity : " + OrderList[enterId].Quantity << endl; 
			cout << "\nNew Quantity : ";
			cin >> ansQuantity; 

			oldId = OrderList[enterId].ProductId;
			OrderId = OrderList[enterId].OrderId;

			Price = stod(Sparepart[oldId].ItemPrice) * ansQuantity;
			newPrice = OrderList[oldId].Price * ansQuantity; 

			cout << "New Price :" << newPrice << ". Price :" << Price << endl;
		}
		else {
			cout << "You enter invalid number" << endl;
			editOrder(id); 
		}

		cout << "Are you sure want to change other part that have been order? (y/n)" << endl;
		cin >> confirmationChange; 

	} while (confirmationChange == "y" || confirmationChange == "Y");

	cout << "Are you sure want to change this order? (y/n)" << endl;
	cin >> confirmation;

	if (confirmation == "Y" || confirmation == "y") {
		DBConn().UpdateOrder(enterId, Price);   
		DBConn().UpdateOrderItem(enterId, ansProName, ansQuantity);  

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

	cout << "Are you sure want to delete this order? (y/n)" << endl;
	cin >> confirmation;

	if (confirmation == 'y' || confirmation == 'Y') {
		DBConn().DeleteOrderItem(ans);
		cout << "The order have been successfully deleted." << endl;
		system("pause");
		Menu().StaffMainMenu(id);
	}
	else {
		removeOrder(id);
	}
}
#pragma endregion