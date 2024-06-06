#include "Sparepart.h"
#include "DBConn.h"
#include "Menu.h"
#include <iomanip>
#include <ctime>
#include <chrono>
#include <sstream>
#include <string>

using namespace std;

const int columnWidth = 19;
int numChoices = 0;

string numberOnly(const std::string& input) { 
	std::string result;
	for (char c : input) {
		if (std::isdigit(c)) {
			result += c;
		}
	}
	return result;
}

#pragma region Staff
void Sparepart::StaffViewStock(int id) {
	int ans, itemCount = 0; 

	system("cls");
	cout << "View Stock of Motocycle Spare Part" << endl << endl;
	DBConn::Sparepart* Sparepart = DBConn().ViewSparepart(id); 

	cout << left << setw(columnWidth) << "Spare Part ID"
		<< setw(columnWidth) << "Item Name"
		<< setw(columnWidth) << "Item Type"
		<< setw(columnWidth) << "Item Brand"
		<< setw(columnWidth) << "Item Price"
		<< setw(columnWidth) << "Stock Balance" << endl;

	for (int i = 0; i < sizeof(Sparepart); i++) {
		while (Sparepart[itemCount].SparepartId != 0) { 
			cout << left << setw(columnWidth) << Sparepart[itemCount].SparepartId
				<< setw(columnWidth) << Sparepart[itemCount].Name
				<< setw(columnWidth) << Sparepart[itemCount].Type
				<< setw(columnWidth) << Sparepart[itemCount].Brand
				<< setw(columnWidth) << Sparepart[itemCount].price
				<< setw(columnWidth) << Sparepart[itemCount].stockBalance << endl;
			itemCount++;
		}
	}

	cout << "\n0. Back to main page " << endl;
	cin >> ans;

	if (ans == 0) {
		Menu().StaffMainMenu(id);
	}
	else if (ans == 1) {
		StaffViewStock(id); 
	}
	else {
		cout << "You have enter invalid number" << endl;
		system("pause");
		StaffViewStock(id); 
	}
	ans == 0 ? Menu().StaffMainMenu(id) : StaffViewStock(id); 
}

void Sparepart::UpdateStock(int id) {
	int ans, itemCount = 0, UpdAns, enterId, enterPart;
	string confirmation, confirmInsert; 
	double newPrice, newBal;

	system("cls"); 
	cout << "List of Sparepart" << endl; 
	DBConn::Sparepart* Sparepart = DBConn().ViewSparepart(id); 

	cout << left << setw(columnWidth) << "Spare Part ID"
		<< setw(columnWidth) << "Item Name" 
		<< setw(columnWidth) << "Item Type" 
		<< setw(columnWidth) << "Item Brand" 
		<< setw(columnWidth) << "Item Price" 
		<< setw(columnWidth) << "Stock Balance" << endl; 
	 
	for (int i = 0; i < sizeof(Sparepart); i++) { 
		while (Sparepart[itemCount].SparepartId != 0) { 
			cout << left << setw(columnWidth) << Sparepart[itemCount].SparepartId
				<< setw(columnWidth) << Sparepart[itemCount].Name 
				<< setw(columnWidth) << Sparepart[itemCount].Type 
				<< setw(columnWidth) << Sparepart[itemCount].Brand 
				<< setw(columnWidth) << Sparepart[itemCount].price 
				<< setw(columnWidth) << Sparepart[itemCount].stockBalance << endl; 
			itemCount++; 
		} 
	}

	cout << "1. Continue Update" << endl; 
	cout << "0. Back to main page " << endl; 
	cin >> UpdAns;
	
	if (UpdAns == 1) {
		do {
			cout << "\nWhich item that you want to change ? (Enter ID)" << endl;
			cin >> enterId;

			cout << "\nWhich part that you want to change ? \n1. Stock Balance\n2. Item Price" << endl;
			cin >> enterPart;

			
			if (enterPart == 1) {
				cout << "Stock Current Balance : " << endl; //display old
				cout << "New Balance : ";
				cin >> newBal; 

				int sccs = DBConn().UpdateBal(newBal, id);

				if (sccs == 1) {
					cout << "Update Successfully" << endl;
					system("pause");
					return;
				}
			}
			else if (enterPart == 2) {
				cout << "Item Current Price : " << endl; //display old
				cout << "New Item Price : ";
				cin >> newPrice;
			}
			else {
				cout << "You have enter invalid number" << endl;
				system("pause");
				UpdateStock(id);
			}

			cout << "Are you sure want to change other part that have been order? (y/n)" << endl;
			cin >> confirmation; 

		} while (confirmation == "y" || confirmation == "Y"); 

		cout << "Are you sure want to change this order? (y/n)" << endl;
		cin >> confirmInsert;

		if (confirmInsert == "Y" || confirmInsert == "y") { 

			cout << "The order have been successfully updated." << endl;
			system("pause");
			Menu().StaffMainMenu(id);
		}
		else {
			UpdateStock(id);
		}
	}
	else if (UpdAns == 0) { 
		Menu().StaffMainMenu(id); 
	}
	else {
		cout << "You enter invalid number" << endl;
		UpdateStock(id); 
	}
}

void Sparepart::DeleteStock(int id) {
	int ans, itemCount = 0, Delans;
	char confirmation;

	system("cls"); 
	cout << "List of Sparepart" << endl;
	DBConn::Sparepart* Sparepart = DBConn().ViewSparepart(id);

	cout << left << setw(columnWidth) << "Spare Part ID"
		<< setw(columnWidth) << "Item Name"
		<< setw(columnWidth) << "Item Type"
		<< setw(columnWidth) << "Item Brand"
		<< setw(columnWidth) << "Item Price"
		<< setw(columnWidth) << "Stock Balance" << endl;

	for (int i = 0; i < sizeof(Sparepart); i++) {
		while (Sparepart[itemCount].SparepartId != 0) {
			cout << left << setw(columnWidth) << Sparepart[itemCount].SparepartId
				<< setw(columnWidth) << Sparepart[itemCount].Name
				<< setw(columnWidth) << Sparepart[itemCount].Type
				<< setw(columnWidth) << Sparepart[itemCount].Brand
				<< setw(columnWidth) << Sparepart[itemCount].price
				<< setw(columnWidth) << Sparepart[itemCount].stockBalance << endl;
			itemCount++;
		}
	}

	cout << "1. Continue Delete" << endl; 
	cout << "0. Back to main page " << endl; 
	cout << "\nYour Choice : ";
	cin >> ans; 

	if (ans == 0) {
		Menu().StaffMainMenu(id);
	}
	else if (ans == 1) {
		cout << "\nPlease choose which ID that you want to delete? " << endl;
		cin >> Delans; 

		cout << "Are you sure want to delete this order? (y/n)" << endl;
		cin >> confirmation;

		if (confirmation == 'y' || confirmation == 'Y') {
			int success = DBConn().DeleteSparepart(Delans);
			if (success == 1) {
				cout << "The order have been successfully deleted." << endl;
				system("pause");
				Menu().StaffMainMenu(id);
			}
			else {
				cout << "The order have not been deleted." << endl;
				system("pause"); 
				DeleteStock(id);  
			}
		}
		else {
			DeleteStock(id); 
		}
	}
	else {
		cout << "You enter invalid number" << endl;
		DeleteStock(id);
	}
}

string GetMonthName(int month) {
	string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October","November", "December" }; 

	if (month != -1) {
		return months[month - 1];
	}
	else {
		return "";
	}
	
}

void Sparepart::ViewMonthlyReport(int id) {
	system("cls");
	cout << "View Monthly Report for Motorcycle Spare Part" << endl;

	int ans,itemCount = 0;
	ostringstream oss;

	DBConn::MonthlyReport* data = DBConn().ListOfMonthlyData(id); 
	cout << "Staff Name : " + DBConn().getStaffUserName(id) << endl;

	cout << left << setw(columnWidth) << "Month"
		<< setw(columnWidth) << "Total Item"
		<< setw(columnWidth) << "Sum of Total Item" << endl;

	//for (int i = 0; i < sizeof(data); i++) {
		while (data[itemCount].month != 0) {
			string monthName = GetMonthName(data[itemCount].month);
			//oss << "RM " << std::fixed << std::setprecision(2) << data[itemCount].SumTtlPrice;  

			cout << left << setw(columnWidth) << monthName
				<< setw(columnWidth) << data[itemCount].TotalCount
				<< setw(columnWidth) << data[itemCount].SumTtlPrice << endl;
			itemCount++;
		}
	//}
	
	cout << "\n0. Back to main page " << endl; 
	cin >> ans; 

	ans == 0 ? Menu().StaffMainMenu(id) : ViewMonthlyReport(id); 
}
#pragma endregion