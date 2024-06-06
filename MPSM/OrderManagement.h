#pragma once
class OrderManagement
{
public:
	void viewOrder(int id);
	void listOfSupplier(int id);
	void AddOrder(int id, int idSupplier);
	void editOrder(int id);
	void removeOrder(int id);
	void MakePayment(int id);
};

