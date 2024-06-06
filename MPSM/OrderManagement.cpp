#include "OrderManagement.h"
#include "DBConn.h"
#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <sstream>
#include <string>

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

const int columnWidth = 20;
const int columnWidth1 = 25;
const int columnWidth2 = 15;

const double MAX_CHOICES = 100;
int* choices = new int[MAX_CHOICES];
int* quantities = new int[MAX_CHOICES];
double* ItemPrice = new double[MAX_CHOICES];

#pragma region Staff
void OrderManagement::viewOrder(int id){
	int ans, itemCount = 0;
	
	system("cls");

	cout << "List of order " << endl; 
	DBConn::Order* OrderList = DBConn().ViewOrder(id); 
	cout << left << setw(columnWidth) << "Item ID"
		<< setw(columnWidth) << "Product Name" 
		<< setw(columnWidth) << "Quantity" 
		<< setw(columnWidth) << "Staff Name" 
		<< setw(columnWidth) << "Total Price" << endl; 

	for (int i = 0; i < sizeof(OrderList); i++) {
		while (OrderList[itemCount].OrderId != 0) { 
			cout << left << setw(columnWidth) << OrderList[itemCount].OrderItemId
				<< setw(columnWidth) << OrderList[itemCount].ProductName 
				<< setw(columnWidth) << OrderList[itemCount].Quantity 
				<< setw(columnWidth) << OrderList[itemCount].StaffName 
				<< setw(columnWidth) << OrderList[itemCount].totalPrice << endl; 
			itemCount++; 
		}
	}

	cout << "\n0. Back to main page " << endl;
	cout << "Choice : ";
	cin >> ans;

	if (ans == 0) {
		Menu().StaffMainMenu(id);
	}
	else {
		cout << "You enter invalid number" << endl;
		system("pause");
		viewOrder(id);
	}
}

void OrderManagement::listOfSupplier(int id) {
	int selectID, ans, itemCount = 0, supID;

	system("cls");
	DBConn::Supplier* OrderList = DBConn().ListoFSupplier(); 
	cout << left << setw(columnWidth1) << "Supplier ID"
		<< setw(columnWidth1) << "Supplier Name"
		<< setw(columnWidth1) << "Address" << endl;

	//for (int i = 0; i < sizeof(OrderList); i++) {
		while (OrderList[itemCount].SupplierID != 0) {
			cout << left << setw(columnWidth1) << OrderList[itemCount].SupplierID
				<< setw(columnWidth1) << OrderList[itemCount].SupplierName
				<< setw(columnWidth1) << OrderList[itemCount].SupplierAddress << endl;
			itemCount++;
		}
	//}

	cout << "\n1. Continue make order" << endl;
	cout << "0. Back to main page " << endl;
	cout << "\nYour Choice : ";
	cin >> ans;

	if (ans == 0) {
		Menu().StaffMainMenu(id); 
	}
	else if (ans == 1){
		cout << "Select Supplier ID : "; 
		cin >> supID; 
		AddOrder(id, supID); 
	} 
	else { 
		cout << "You enter the wrong input " ; 
		system("pause"); 
		listOfSupplier(id);  
	}
}

void OrderManagement::AddOrder(int id, int idSupplier){
	int ans, choose, qtt, numChoices = 0, isActive; 
	string addMore, payment;
	double price = 0;

	system("cls");

	cout << "Make Order" << endl;

	DBConn::SparepartList sparepartList = DBConn().ListOfSparepart(idSupplier);
	DBConn::Item* Sparepart = sparepartList.items;
	int itemCount = sparepartList.count;

	cout << "\nList of all spare parts " << endl << endl;

	cout << left << setw(columnWidth2) << "Item ID"  
		<< setw(columnWidth1) << "Item Name"
		<< setw(columnWidth) << "Supplier Name"
		<< setw(columnWidth2) << "Item Type"
		<< setw(columnWidth2) << "Item Brand"
		<< setw(columnWidth2) << "Item Price"
		<< setw(columnWidth2) << "Quantity" << endl;

	for (int i = 0; i < itemCount; ++i) {
		cout << left << setw(columnWidth2) << Sparepart[i].ItemID 
			<< setw(columnWidth1) << Sparepart[i].ItemName
			<< setw(columnWidth) << Sparepart[i].SupplierName
			<< setw(columnWidth2) << Sparepart[i].ItemType
			<< setw(columnWidth2) << Sparepart[i].ItemBrand
			<< setw(columnWidth2) << Sparepart[i].ItemPrice
			<< setw(columnWidth2) << Sparepart[i].quantity << endl;
	}

	cout << "\n1. Continue make order" << endl;
	cout << "0. Back to Main Page" << endl;
	cout << "\nYour Choice : ";
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
					if (qtt < Sparepart[i].quantity || qtt == Sparepart[i].quantity) {
						choices[numChoices] = choose; 
						quantities[numChoices] = qtt;  
						ItemPrice[numChoices] = qtt * stod(Sparepart[i].ItemPrice); 
						numChoices++;
						found = true;
					}
					else {
						cout << "The amount is more than the available quantity" << endl;
						system("pause");
						AddOrder(id, idSupplier);
					}
				}
				else if (Sparepart[i].ItemID == choose && found == false){
					cout << "You enter the wrong input. Please Retry."; 
					system("pause"); 
					AddOrder(id, idSupplier);
				}
			}
			if (!found) {
				cout << "Item ID not found" << endl;
				system("pause");
				AddOrder(id, idSupplier);
			}

			cout << "Do you want to add more? (y/n) : " ;
			cin >> addMore;
		} while (addMore == "y" || addMore == "Y");

		system("cls");

		cout << left << setw(columnWidth2) << "Item ID"
			<< setw(columnWidth) << "Item Name" 
			<< setw(columnWidth) << "Supplier Name" 
			<< setw(columnWidth) << "Item Type" 
			<< setw(columnWidth) << "Item Brand" 
			<< setw(columnWidth2) << "Item Price"
			<< setw(columnWidth2) << "Quantities"
			<< setw(columnWidth2) << "Total Price" << endl;

		for (int i = 0; i < numChoices; i++) { 
			int itemId = choices[i];  
			for (int j = 0; j < itemCount; j++) { 
				if (Sparepart[j].ItemID == itemId) { 
					cout << left << setw(columnWidth2) << itemId
						<< setw(columnWidth) << Sparepart[j].ItemName
						<< setw(columnWidth) << Sparepart[j].SupplierName
						<< setw(columnWidth) << Sparepart[j].ItemType
						<< setw(columnWidth) << Sparepart[j].ItemBrand
						<< setw(columnWidth2) << Sparepart[j].ItemPrice
						<< setw(columnWidth2) << quantities[i]
						<< setw(columnWidth2) << ItemPrice[i] << endl;

					price += quantities[i] * stod(Sparepart[j].ItemPrice); 
					break;
				}
			}
		}

		cout << "Do you want to make payment? (y/n) : ";
		cin >> payment;

		payment == "Y" || payment == "y" ? isActive = 1 : isActive = 0;

		DBConn().MakeOrder(id, price, isActive);
		int orderID = DBConn().getOrderID(price); 
		for (int i = 0; i < numChoices; i++) {  
			int itemId = choices[i];
			for (int j = 0; j < itemCount; j++) {
				if (Sparepart[j].ItemID == itemId) {
					DBConn().MakeOrderItem(orderID, itemId, quantities[i], ItemPrice[i]); 
					int SparepartID = DBConn().CheckSparepart(Sparepart[j].ItemName); 
					if (SparepartID != 0) {
						int balance = DBConn().CheckSparepartBalance(SparepartID); 
						int newStockBalance = balance + quantities[i]; 
						int success = DBConn().UpdateSparepart(SparepartID, newStockBalance); 
					}
					else {
                        DBConn().InsertSparepart(id, Sparepart[j].ItemName, Sparepart[j].ItemType, Sparepart[j].ItemBrand, stod(Sparepart[j].ItemPrice), quantities[i]);
                    }
					int ProductQtt = DBConn().CheckProductQuantity(itemId);
					ProductQtt -= quantities[i];
					DBConn().UpdateProduct(itemId, ProductQtt); 
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
		AddOrder(id, idSupplier);
	}
}

void OrderManagement::MakePayment(int id) {
	int ans, payID;
	string pay;
	system("cls");

	cout << "Make Order" << endl;

	DBConn::SparepartList paymentList = DBConn().ListOfPayment(id); 
	DBConn::Item* Sparepart = paymentList.items; 
	int itemCount = paymentList.count; 

	cout << "\nList of all spare parts didnt pay yet " << endl << endl;

	cout << left << setw(columnWidth2) << "Item ID"
		<< setw(columnWidth1) << "Item Name"
		<< setw(columnWidth) << "Supplier Name"
		<< setw(columnWidth2) << "Item Type"
		<< setw(columnWidth2) << "Item Brand"
		<< setw(columnWidth2) << "Item Price"
		<< setw(columnWidth2) << "Quantity" << endl;

	for (int i = 0; i < itemCount; ++i) {  
		cout << left << setw(columnWidth2) << Sparepart[i].ItemID 
			<< setw(columnWidth1) << Sparepart[i].ItemName 
			<< setw(columnWidth) << Sparepart[i].SupplierName 
			<< setw(columnWidth2) << Sparepart[i].ItemType 
			<< setw(columnWidth2) << Sparepart[i].ItemBrand 
			<< setw(columnWidth2) << Sparepart[i].ItemPrice 
			<< setw(columnWidth2) << Sparepart[i].quantity << endl; 
	} 

	cout << "\n1. Continue make payment" << endl;
	cout << "0. Back to Main Page" << endl;
	cout << "\nYour Choice : ";
	cin >> ans;

	if (ans == 0) {
		Menu().StaffMainMenu(id);
	}
	else if (ans == 1) {
		cout << "Choose your item ID :";
		cin >> payID;
		int Itemid = DBConn().ReturnPaymentID(payID, id);
		if (Itemid == 0) {
			cout << "You enter invalid number" << endl; 
			system("pause"); 
			MakePayment(id);  
		}
		else {
			cout << "\nDo you want to make the payment ? (y/n) :";
			cin >> pay;
			if (pay == "Y" || pay == "y") {
				DBConn().UpdatePaymentID(Itemid);
				cout << "Successfully Pay " << endl;
				system("pause");
				Menu().StaffMainMenu(id);  
			}
			else {
				MakePayment(id); 
			}
		}
		
	}
	else {
		cout << "You enter invalid number" << endl;
		system("pause");
		MakePayment(id);
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
		cout << left << setw(columnWidth) << "Item ID"
			<< setw(columnWidth) << "Product Name"
			<< setw(columnWidth) << "Quantity"
			<< setw(columnWidth1) << "Staff Name"
			<< setw(columnWidth1) << "Total Price" << endl;

		for (int i = 0; i < sizeof(OrderList); i++) {
			while (OrderList[itemCount].OrderId != 0) {
				cout << left << setw(columnWidth) << OrderList[itemCount].OrderItemId
					<< setw(columnWidth) << OrderList[itemCount].ProductName
					<< setw(columnWidth) << OrderList[itemCount].Quantity
					<< setw(columnWidth1) << OrderList[itemCount].StaffName
					<< setw(columnWidth1) << OrderList[itemCount].Price << endl;
				itemCount++;
			}
		}

		cout << "\nWhich order that you want to change ? " << endl;
		cout << "Enter ID : ";
		cin >> enterId;

		cout << "\nWhich part that you want to change ? \n1. Product Name\n2. Quantity" << endl;
		cout << "Your Choice : ";
		cin >> enterPart; 

		DBConn::SparepartList SparepartList = DBConn().ListOfSparepart(id);
		DBConn::Item* Sparepart = SparepartList.items;

		cout << left << setw(columnWidth) << "Item ID"
			<< setw(columnWidth) << "Item Name"
			<< setw(columnWidth) << "Supplier Name"
			<< setw(columnWidth) << "Item Type"
			<< setw(columnWidth) << "Item Brand"
			<< setw(columnWidth) << "Item Price" << endl;

		for (int i = 0; i < sizeof(Sparepart); i++) {
			while (Sparepart[itemCount].ItemID != 0) {
				cout << left << setw(columnWidth) << Sparepart[itemCount].ItemID
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

		cout << "Are you sure want to change other part that have been order?" << endl;
		cout << "Enter (y/n) : ";
		cin >> confirmationChange; 

	} while (confirmationChange == "y" || confirmationChange == "Y");

	cout << "Are you sure want to change this order? " << endl;
	cout << "Enter (y/n) : ";
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
	cout << left << setw(columnWidth) << "Item ID"
		<< setw(columnWidth) << "Product Name" 
		<< setw(columnWidth) << "Quantity" 
		<< setw(columnWidth) << "Staff Name" 
		<< setw(columnWidth) << "Total Price" << endl; 

	for (int i = 0; i < sizeof(OrderList); i++) { 
		while (OrderList[itemCount].OrderId != 0) { 

			cout << left << setw(columnWidth) << OrderList[itemCount].OrderItemId
				<< setw(columnWidth) << OrderList[itemCount].ProductName 
				<< setw(columnWidth) << OrderList[itemCount].Quantity 
				<< setw(columnWidth) << OrderList[itemCount].StaffName 
				<< setw(columnWidth) << OrderList[itemCount].totalPrice << endl; 
			itemCount++; 
		}
	}
	cout << "\nPlease choose which ID that you want to delete? " << endl;
	cout << "Enter ID : ";
	cin >> ans;

	cout << "Are you sure want to delete this order? " << endl;
	cout << "Enter (y/n) : ";
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