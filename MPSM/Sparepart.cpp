#include "Sparepart.h"
#include "DBConn.h"
#include "Menu.h"

using namespace std;

#pragma region Staff
void Sparepart::StaffViewStock(int id) {
	int ans;

	system("cls");
	cout << "View Stock of Motocycle Spare Part" << endl;

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