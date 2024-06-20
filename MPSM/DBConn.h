#include <string>
#include <mysql/jdbc.h>
#include <ctime>

using namespace std;

class DBConn
{
private:
    sql::Connection* con;

public:
    sql::PreparedStatement* stmt;
    sql::ResultSet* rs;

#pragma region declaration
    int id, Stockbalance, ProductQtt;
    string name;

    struct Item {
        int ItemID;
        int SupplierID;
        string ItemName;
        string SupplierName;
        string ItemType;
        string ItemBrand;
        string ItemPrice;
        int quantity;
    };

    struct Supplier {
        int SupplierID;
        string SupplierName;
        string SupplierAddress;
    };

    struct SparepartList { 
        Item* items;
        int count;
    };

    struct Order {
        int OrderId;
        int StaffId;
        int OrderItemId;
        int ProductId;
        int Quantity;
        double totalPrice;
        double Price;
        string ProductName;
        string StaffName;
    };

    struct Sparepart {
        int SparepartId;
        int StaffId;
        string StaffName;
        string Name;
        string Type;
        string Brand;
        double price;
        double stockBalance;
    };

    struct MonthlyReport {
        int TotalCount;
        int SumTtlPrice;
        int month;
    };
#pragma endregion

#pragma region Basic Connection
    DBConn() {
        try {
            sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();

            con = driver->connect("tcp://127.0.0.1:3306", "root", "");

            con->setSchema("workshop1");
            stmt = nullptr;
            rs = nullptr;

        }
        catch (sql::SQLException& e) {
            if (e.getErrorCode() == 0) {
                system("cls");
                cout << "tak connect db";
                _getwch();
                exit(0);
                return;
            }
            cout << "Error in " << __FILE__;
            cout << "FUNCTION on line" << __LINE__ << endl;
            cout << "Punca : " << e.what();
            cout << "Mysql Error code: " << e.getErrorCode();
            cout << ", sqlstate: " << e.getSQLState() << endl;
            _getwch();
        }
    }

    ~DBConn() {
        try {
            if (con) {
                con->close();
            }
            if (stmt) {
                stmt->close();
            }
            if (rs) {
                rs->close();
            }
        }
        catch (sql::SQLException& e) {
            if (e.getErrorCode() == 0) {
                system("cls");
                cout << "unable to connect db";
                _getwch();
                exit(0);
                return;
            }
            cout << "Error in " << __FILE__;
            cout << "FUNCTION on line" << __LINE__ << endl;
            cout << "Punca : " << e.what();
            cout << "Mysql Error code: " << e.getErrorCode();
            cout << ", sqlstate: " << e.getSQLState() << endl;
            _getwch();
        }
    }

    void preparedStatement(string query) {
        stmt = con->prepareStatement(query);
    }

    void QueryStatement() {
        try {
            stmt->executeUpdate();
        }
        catch (sql::SQLException& e) {
            if (e.getErrorCode() == 0) {
                system("cls");
                cout << "eghor db";
                _getwch();
                exit(0);
                return;
            }
            cout << "Error in " << __FILE__;
            cout << "FUNCTION on line" << __LINE__ << endl;
            cout << "Punca : " << e.what();
            cout << "Mysql Error code: " << e.getErrorCode();
            cout << ", sqlstate: " << e.getSQLState() << endl;
            _getwch();
        }
    }

    int getLastInsertId() { 
        try { 
            sql::Statement* tempStmt = con->createStatement(); 
            rs = tempStmt->executeQuery("SELECT LAST_INSERT_ID()"); 
            if (rs->next()) { 
                int id = rs->getInt(1); 
                tempStmt->close(); 
                delete tempStmt; 
                return id; 
            } 
            tempStmt->close(); 
            delete tempStmt; 
        }
        catch (sql::SQLException& e) {
            if (e.getErrorCode() == 0) { 
                system("cls"); 
                cout << "eghor db"; 
                _getwch(); 
                exit(0); 
                return -1; 
            } 
            cout << "Error in " << __FILE__;  
            cout << "FUNCTION on line" << __LINE__ << endl; 
            cout << "Punca : " << e.what(); 
            cout << "Mysql Error code: " << e.getErrorCode(); 
            cout << ", sqlstate: " << e.getSQLState() << endl; 
            _getwch(); 
        }
        return -1; // In case of error
    }

    void QuerySelectResult() {
        try {
            rs = stmt->executeQuery();
        }
        catch (sql::SQLException& e) {
            if (e.getErrorCode() == 0) {
                system("cls");
                cout << "ha salah ni kt db";
                _getwch();
                exit(0);
                return;
            }
            cout << "Error in " << __FILE__;
            cout << "FUNCTION on line" << __LINE__ << endl;
            cout << "Punca : " << e.what();
            cout << "Mysql Error code: " << e.getErrorCode();
            cout << ", sqlstate: " << e.getSQLState() << endl;
            _getwch();
        }
    }

#pragma endregion

#pragma region Login && Register
    int authenticateStaff(const std::string& username, const std::string& password) {
        DBConn db;
        db.preparedStatement("SELECT * FROM staff WHERE Username = ? && Password = ?");
        db.stmt->setString(1, username);
        db.stmt->setString(2, password);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                id = db.rs->getInt("StaffID");
            }
            return id;
        }
        else 
        {
            return 0;
        }
    }
    int authenticateSupplier(const std::string& username, const std::string& password) {
        DBConn db;
        db.preparedStatement("SELECT * FROM supplier WHERE Username = ? && Password = ?");
        db.stmt->setString(1, username);
        db.stmt->setString(2, password);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                id = db.rs->getInt("SupplierID");
            }
            return id;
        }
        else
        {
            return 0;
        }
    }

    void Staffregisteration(const string& Name, const int& Gender, const string& username, const string& pass) {
        DBConn db;
        db.preparedStatement("INSERT INTO `staff`(`Name`, `Gender`, `Username`, `Password`, `isStaff`) VALUES (?,?,?,?,?)");
        db.stmt->setString(1, Name);
        db.stmt->setInt(2, Gender);
        db.stmt->setString(3, username);
        db.stmt->setString(4, pass);
        db.stmt->setInt(5, 1);
        db.QueryStatement();
    }

    void SupplierRegisteration(const string& Name, const string& Address, const string& username, const string& pass) {
        DBConn db;
        db.preparedStatement("INSERT INTO `supplier`(`Name`, `Address`, `Username`, `Password`, `isSupplier`) VALUES (?,?,?,?,?)");
        db.stmt->setString(1, Name);
        db.stmt->setString(2, Address);
        db.stmt->setString(3, username);
        db.stmt->setString(4, pass);
        db.stmt->setInt(5, 1);
        db.QueryStatement();
    }

#pragma endregion

#pragma region Supplier Main Page
    bool isSupplier(const int& id) {
        DBConn db;
        db.preparedStatement("SELECT * FROM supplier WHERE SupplierID = ?");
        db.stmt->setInt(1, id);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                return true;
            }
        }
        else {
            return false;
        }
    }

    string getSupplierUserName(const int& id) {
        DBConn db;
        db.preparedStatement("SELECT * FROM supplier WHERE SupplierID = ?");
        db.stmt->setInt(1, id);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                name = db.rs->getString("Name");
            }
            return name;
        }
        else {
            return "";
        }

    }
#pragma endregion

#pragma region Staff Main Page
    bool isStaff(const int& id) {
        DBConn db;
        db.preparedStatement("SELECT * FROM staff WHERE StaffID = ?");
        db.stmt->setInt(1, id);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                return true;
            }
        }
        else {
            return false;
        }
    }

    string getStaffUserName(const int& id) {
        DBConn db;
        db.preparedStatement("SELECT * FROM staff WHERE StaffID = ?");
        db.stmt->setInt(1, id);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                name = db.rs->getString("Name");
            }
            return name;
        }
        else {
            return "";
        }
    }
#pragma endregion

#pragma region Spare Part Management
    Supplier* ListoFSupplier() {
        Supplier* supplier = new Supplier[10000];

        DBConn db;
        db.preparedStatement("SELECT * FROM `supplier`;");
        db.QuerySelectResult();
        int itemCount = 0;
        while (db.rs->next()) {
            supplier[itemCount].SupplierID = db.rs->getInt("SupplierID");
            supplier[itemCount].SupplierAddress = db.rs->getString("Address");
            supplier[itemCount].SupplierName = db.rs->getString("Name");
            itemCount++; 
        }

        return supplier;
    }

    SparepartList ListOfSparepart(int idSupplier) {
        Item* items = new Item[100000];

        DBConn db;
        db.preparedStatement("SELECT p.ProductID,p.SupplierID,p.Name,p.Type,p.Brand,p.Price,s.Name SupplierName, p.Quantity FROM product p INNER JOIN supplier s ON p.SupplierID = s.SupplierID WHERE p.Quantity != 0 AND p.SupplierID = ?;");
        db.stmt->setInt(1, idSupplier);
        db.QuerySelectResult();
        int itemCount = 0;
        while (db.rs->next()) {
            items[itemCount].ItemID = db.rs->getInt("ProductID");
            items[itemCount].SupplierID = db.rs->getInt("SupplierID");
            items[itemCount].ItemName = db.rs->getString("Name"); 
            items[itemCount].SupplierName = db.rs->getString("SupplierName"); 
            items[itemCount].ItemType = db.rs->getString("Type"); 
            items[itemCount].ItemBrand = db.rs->getString("Brand"); 
            items[itemCount].ItemPrice = db.rs->getString("Price"); 
            items[itemCount].quantity = db.rs->getInt("Quantity"); 
            itemCount++;
        }
        SparepartList list;
        list.items = items;
        list.count = itemCount;
        return list;
        //return items; 
    }

    SparepartList ListOfPayment(int idStaff, int isPaid) {
        Item* items = new Item[100000];

        DBConn db;
        db.preparedStatement("SELECT oi.ItemID, p.SupplierID, p.Name, p.Type,p.Brand,p.Price,oi.Quantity, s.Name SupplierName FROM `order` o join orderitem oi on oi.OrderID = o.OrderID join product p on p.ProductID = oi.ProductID join supplier s on s.SupplierID = p.SupplierID WHERE oi.isPaid = ? AND o.StaffID = ?;");
        db.stmt->setInt(1, isPaid);
        db.stmt->setInt(2, idStaff);
        db.QuerySelectResult();
        int itemCount = 0;
        while (db.rs->next()) {
            items[itemCount].ItemID = db.rs->getInt("ItemID");
            items[itemCount].SupplierID = db.rs->getInt("SupplierID");
            items[itemCount].SupplierName = db.rs->getString("SupplierName"); 
            items[itemCount].ItemName = db.rs->getString("Name");
            items[itemCount].ItemType = db.rs->getString("Type");
            items[itemCount].ItemBrand = db.rs->getString("Brand");
            items[itemCount].ItemPrice = db.rs->getString("Price");
            items[itemCount].quantity = db.rs->getInt("Quantity");
            itemCount++;
        }
        SparepartList list;
        list.items = items;
        list.count = itemCount;
        return list;
        //return items; 
    }

    Order* ViewOrder(const int& Staffid) {
        Order* order = new Order[100000];

        DBConn db;
        db.preparedStatement("SELECT o.OrderID,o.StaffID,o.TotalPrice,oi.ItemID,oi.ProductID, oi.Quantity, s.Name,p.Name PName, oi.Price FROM `order` o join `orderitem` oi on o.OrderID = oi.OrderID JOIN staff s ON s.StaffID = o.StaffID JOIN product p ON p.ProductID = oi.ProductID WHERE o.StaffID = ? AND o.isPaid = 1");
        db.stmt->setInt(1, Staffid);
        db.QuerySelectResult();
        int OrderCount = 0;
        while (db.rs->next()) {
            order[OrderCount].OrderId = db.rs->getInt("OrderID");
            order[OrderCount].OrderItemId = db.rs->getInt("ItemID");
            order[OrderCount].ProductId = db.rs->getInt("ProductID");
            order[OrderCount].Quantity = db.rs->getInt("Quantity");
            order[OrderCount].StaffId = db.rs->getInt("StaffID");
            order[OrderCount].totalPrice = db.rs->getDouble("TotalPrice");
            order[OrderCount].StaffName = db.rs->getString("Name");
            order[OrderCount].ProductName = db.rs->getString("PName"); 
            order[OrderCount].Price = db.rs->getDouble("Price");
            OrderCount++;
        }
        return order;
    }

    Sparepart* ViewSparepart(const int& StaffId) {
        Sparepart* sparepart = new Sparepart[100000];

        DBConn db;
        db.preparedStatement("SELECT s.SparepartID, s.StaffID, s.Name, s.Type, s.Brand, s.Price, s.StockBalance, st.Name Fname FROM `sparepart` s JOIN staff st ON s.StaffID = st.StaffID where s.StaffID = ?");
        db.stmt->setInt(1, StaffId); 
        db.QuerySelectResult(); 
        int OrderCount = 0; 
        while (db.rs->next()) { 
            sparepart[OrderCount].SparepartId = db.rs->getInt("SparepartID");
            sparepart[OrderCount].StaffId = db.rs->getInt("StaffID");
            sparepart[OrderCount].StaffName = db.rs->getString("Fname");
            sparepart[OrderCount].Name = db.rs->getString("Name");
            sparepart[OrderCount].Type = db.rs->getString("Type"); 
            sparepart[OrderCount].Brand = db.rs->getString("Brand");
            sparepart[OrderCount].price = db.rs->getDouble("Price"); 
            sparepart[OrderCount].stockBalance= db.rs->getDouble("StockBalance");
            OrderCount++;
        }
        return sparepart;
    }

    int MakeOrder(const int& StaffId, const double& price, int isActive) {
        time_t now = std::time(nullptr);

        // Convert to local time
        tm local_time; 
        localtime_s(&local_time, &now); 

        // Print local time
        char buffer[26];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time); 
        string datetime_str(buffer);

        DBConn db;
        db.preparedStatement("INSERT INTO `order`(`StaffID`, `isPaid`, `TotalPrice`, `DateTime`) VALUES (?,?,?,?)");
        db.stmt->setInt(1, StaffId); 
        db.stmt->setInt(2, isActive); 
        db.stmt->setDouble(3, price); 
        db.stmt->setDateTime(4, datetime_str);
        db.QueryStatement(); 
    }

    void MakeOrderItem(const int& OrderID, const int& ProductId, const int& qtt, const double& price, int isActive) {
        time_t now = std::time(nullptr);

        tm local_time;
        localtime_s(&local_time, &now);

        char buffer[26];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
        string datetime_str(buffer);

        DBConn db;
        db.preparedStatement("INSERT INTO `orderitem`(`OrderID`, `ProductID`, `Quantity`, `DateTime`, `Price`, `isPaid`) VALUES (?,?,?,?,?,?)"); 
        db.stmt->setInt(1, OrderID);
        db.stmt->setInt(2, ProductId);
        db.stmt->setInt(3, qtt);
        db.stmt->setDateTime(4, datetime_str); 
        db.stmt->setDouble(5, price); 
        db.stmt->setInt(6, isActive);
        db.QueryStatement(); 
    }

    int CheckSparepart(const string& SparepartName) {
        DBConn db;
        db.preparedStatement("SELECT * FROM `sparepart` WHERE Name = ?");
        db.stmt->setString(1, SparepartName);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                id = db.rs->getInt("SparepartID");
            }
            return id;
        }
        else {
            return 0;
        }
    }

    void InsertSparepart(const int& StaffId, const string& Name, const string& Type, const string& Brand, const double& Price, const int& StockBalance){
        DBConn db;
        db.preparedStatement("INSERT INTO `sparepart`(`StaffID`, `Name`, `Type`, `Brand`, `Price`, `StockBalance`) VALUES (?,?,?,?,?,?);");
        db.stmt->setInt(1, StaffId);
        db.stmt->setString(2, Name);
        db.stmt->setString(3, Type); 
        db.stmt->setString(4, Brand);
        db.stmt->setDouble(5, Price);
        db.stmt->setDouble(6, StockBalance);
        db.QueryStatement();
    }

    int CheckSparepartBalance(const int& SparepartID ) {
        DBConn db;
        db.preparedStatement("SELECT * FROM `sparepart` WHERE SparepartID = ?");
        db.stmt->setInt(1, SparepartID);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                Stockbalance = db.rs->getInt("StockBalance"); 
            }
            return Stockbalance;
        }
        else {
            return 0;
        }
    }

    int CheckProductQuantity(const int& ProductID) {
        DBConn db;
        db.preparedStatement("SELECT * FROM `product` WHERE ProductID =  ?");
        db.stmt->setInt(1, ProductID);
        db.QuerySelectResult();
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                ProductQtt = db.rs->getInt("Quantity");
            }
            return ProductQtt;
        }
        else {
            return 0;
        }
    }

    int UpdateSparepart(const int& SparepartID, const int& StockBalance) { 
        try { 
            DBConn db;
            db.preparedStatement("UPDATE `sparepart` SET `StockBalance`=? WHERE `SparepartID` = ?");
            db.stmt->setInt(1, StockBalance);
            db.stmt->setInt(2, SparepartID);
            db.QueryStatement();
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "Error update: " << e.what() << std::endl;
            return 0;
        }
    }

    int UpdateProduct(const int& ProductID, const int& Quantity) {
        try {
            DBConn db;  
            db.preparedStatement("UPDATE `product` SET `Quantity`=? WHERE `ProductID`=?");  
            db.stmt->setInt(1, Quantity); 
            db.stmt->setInt(2, ProductID); 
            db.QueryStatement(); 
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "Error update: " << e.what() << std::endl; 
            return 0; // Failure
        }
        
    }

    int UpdateOrderItem(const int& ItemID, const int& ProductID, const int& Quantity) {
        try {
            DBConn db; 
            db.preparedStatement("UPDATE `orderitem` SET `ProductID`=?,`Quantity`=? WHERE ItemID = ?"); 
            db.stmt->setInt(1, ProductID); 
            db.stmt->setInt(2, Quantity); 
            db.stmt->setInt(3, ItemID); 
            db.QueryStatement(); 
        } 
        catch (const std::exception& e) {
            std::cerr << "Error update: " << e.what() << std::endl;
            return 0; // Failure
        }
    }

    void UpdateOrder(const int& OrderId, const double& TotalPrice) {
        DBConn db;
        db.preparedStatement("UPDATE `order` SET `TotalPrice`=? WHERE OrderID = ?");
        db.stmt->setDouble(1, TotalPrice);
        db.stmt->setInt(2, OrderId);
        db.QueryStatement();
    }

    void DeleteOrderItem(const int& ItemID) {
        DBConn db;
        db.preparedStatement("DELETE FROM `orderitem` WHERE ItemID = ?");
        db.stmt->setInt(1, ItemID);
        db.QueryStatement();
    }

    int DeleteSparepart(const int& SparepartID) {
        try {
            DBConn db; 
            db.preparedStatement("DELETE FROM `sparepart` WHERE SparepartID = ?"); 
            db.stmt->setInt(1, SparepartID); 
            db.QueryStatement(); 
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "Error delete: " << e.what() << std::endl;
            return 0; // Failure
        }
    }

    int getOrderID() {
        DBConn db;
        db.preparedStatement("SELECT * FROM `order` Order By OrderID DESC LIMIT 1;"); 
        db.QuerySelectResult(); 
        if (db.rs->rowsCount() == 1) { 
            while (db.rs->next()) { 
                id = db.rs->getInt("OrderID");
            } 
            return id;
        }
        else {
            return 0;
        }
    }
    
    MonthlyReport* ListOfMonthlyData(int& id) {
        MonthlyReport* report = new MonthlyReport[0];

        DBConn db; 
        db.preparedStatement("SELECT MONTH(DateTime) month,COUNT(*) as ttl, SUM(TotalPrice) as sum FROM `order` WHERE YEAR(DateTime) = '2024' AND StaffID = ? AND isPaid = 1 GROUP BY MONTH(DateTime);"); 
        db.stmt->setInt(1, id);
        db.QuerySelectResult(); 
        int counter = 0;
        if (db.rs->rowsCount() != 0) {  
            while (db.rs->next()) {  
                report[counter].TotalCount = db.rs->getInt("ttl");  
                report[counter].SumTtlPrice = db.rs->getInt("sum");
                report[counter].month = db.rs->getInt("month");
                counter++;
            } 
            return report;  
        } 
    }

    int ReturnPaymentID(int& id, int& StaffID) {
        DBConn db; 
        db.preparedStatement("SELECT oi.OrderID, p.SupplierID, p.Name, p.Type,p.Brand,p.Price,oi.Quantity, s.Name SupplierName FROM `order` o join orderitem oi on oi.OrderID = o.OrderID join product p on p.ProductID = oi.ProductID join supplier s on s.SupplierID = p.SupplierID WHERE oi.isPaid = 0 AND o.StaffID = ? AND oi.ItemID = ?;"); 
        db.stmt->setInt(1, StaffID); 
        db.stmt->setInt(2, id); 
        db.QuerySelectResult(); 
        if (db.rs->rowsCount() == 1) {  
            while (db.rs->next()) { 
                id = db.rs->getInt("OrderID"); 
            } 
            return id; 
        }  
        else {
            return 0; 
        }
    }

    int UpdatePaymentID(int& Orderid) {
        try {
            DBConn db;
            db.preparedStatement("UPDATE `order` SET `isPaid`='1' WHERE OrderID = ?");
            db.stmt->setInt(1, Orderid);
            db.QueryStatement();
            return 1;
        }
        catch (exception e) {
            return 0;
        }
   
    }

    int UpdatePaymentOrderItemID(int& Orderid) {
        try {
            DBConn db;
            db.preparedStatement("UPDATE `orderitem` SET `isPaid`='1' WHERE ItemID = ?");
            db.stmt->setInt(1, Orderid);
            db.QueryStatement();
            return 1;
        }
        catch (exception e) {
            return 0;
        }

    }

    int UpdateBal(double& balance, int& id, int& staffID) {
        try {
            DBConn db;
            db.preparedStatement("UPDATE `sparepart` SET `StockBalance`= ? WHERE SparepartID = ? AND StaffID = ?");
            db.stmt->setDouble(1, balance);
            db.stmt->setInt(2, id);
            db.stmt->setInt(3, staffID);
            int check = db.stmt->executeUpdate(); 
            if (check > 0) {
                return 1; 
            }
            else {
                return 0; 
            }
        }
        catch (exception e) {
            return 0;
        }
    }

    int UpdateCurrentPrice(double& price, int& id, int& staffID) {
        try {
            DBConn db;
            db.preparedStatement("UPDATE `sparepart` SET `Price`= ? WHERE SparepartID = ? AND StaffID = ?");
            db.stmt->setDouble(1, price);
            db.stmt->setInt(2, id);
            db.stmt->setInt(3, staffID);
            int check = db.stmt->executeUpdate(); 
            if (check > 0) { 
                return 1; 
            } 
            else {
                return 0;
            }
        }
        catch (exception e) {
            return 0;
        }
    }

    int getCurrentPrice(int& id) {
        int price;
        DBConn db;
        db.preparedStatement("SELECT * FROM `sparepart` WHERE SparepartID = ?");
        db.stmt->setInt(1, id);
        if (db.rs->rowsCount() == 1) {
            while (db.rs->next()) {
                price = db.rs->getInt("Price"); 
            }
            return price; 
        }
        else {
            return 0;
        }
        
    }

    int getBalance(int& id) {
        int bal;
        DBConn db;
        db.preparedStatement("SELECT * FROM `sparepart` WHERE SparepartID = ?");
        db.stmt->setInt(1, id);
        if (db.rs->rowsCount() == 1) { 
            while (db.rs->next()) { 
                bal = db.rs->getInt("OrderID"); 
            } 
            return bal; 
        } 
        else { 
            return 0; 
        }
        
    }

#pragma endregion
};