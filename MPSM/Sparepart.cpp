#include "Sparepart.h"
#include "DBConn.h"
#include "Menu.h"
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

const int columnWidth = 19;
int numChoices = 0;

#pragma region Staff
void Sparepart::StaffViewStock(int id) {
	int ans, itemCount = 0; 

	system("cls");
	cout << "View Stock of Motocycle Spare Part" << endl;
	DBConn::Sparepart* Sparepart = DBConn().ViewSparepart(id); 

	cout << setw(columnWidth) << "Spare Part ID"  
		<< setw(columnWidth) << "Item Name"
		<< setw(columnWidth) << "Item Type"
		<< setw(columnWidth) << "Item Brand"
		<< setw(columnWidth) << "Item Price"
		<< setw(columnWidth) << "Stock Balance" << endl;

	for (int i = 0; i < sizeof(Sparepart); i++) {
		while (Sparepart[itemCount].SparepartId != 0) { 
			cout << setw(columnWidth) << Sparepart[itemCount].SparepartId
				<< setw(columnWidth) << Sparepart[itemCount].Name
				<< setw(columnWidth) << Sparepart[itemCount].Type
				<< setw(columnWidth) << Sparepart[itemCount].Brand
				<< setw(columnWidth) << Sparepart[itemCount].price
				<< setw(columnWidth) << Sparepart[itemCount].stockBalance << endl;
			itemCount++;
		}
	}

	cout << "0. Back to main page " << endl;
	cin >> ans;

	ans == 0 ? Menu().StaffMainMenu(id) : StaffViewStock(id);
}

void Sparepart::ViewMonthlyReport(int id) {
	system("cls");
	cout << "View Monthly Report for Motorcycle Spare Part" << endl;

	cout << "Staff Name : " + DBConn().getStaffUserName(id) << endl;
	cout << "hello";
}
#pragma endregion