#include "Sparepart.h"
#include "DBConn.h"

using namespace std;

#pragma region Staff
void Sparepart::StaffViewStock(int id) {
	system("cls");
	cout << "View Stock of Motocycle Spare Part" << endl;
}

void Sparepart::ViewMonthlyReport(int id) {
	system("cls");
	cout << "View Monthly Report for Motorcycle Spare Part" << endl;

	cout << "Staff Name : " + DBConn().getStaffUserName(id) << endl;
	cout << "hello";
}
#pragma endregion