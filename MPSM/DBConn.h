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

    struct Item {
        int ItemID;
        int SupplierID;
        string ItemName;
        string SupplierName;
        string ItemType;
        string ItemBrand;
        string ItemPrice;
    };

    struct Order {
        int OrderId;
        int StaffId;
        int OrderItemId;
        int ProductId;
        int Quantity;
        double totalPrice;
        string ProductName;
        string StaffName;
    };

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
    int id;
    string name;

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
    Item* ListOfSparepart() {
        Item* items = new Item[100000];

        DBConn db;
        db.preparedStatement("SELECT p.ProductID,p.SupplierID,p.Name,p.Type,p.Brand,p.Price,s.Name SupplierName FROM product p INNER JOIN supplier s ON p.SupplierID = s.SupplierID;");
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
            itemCount++;
        }
        return items;
    }

    Order* ViewOrder(const int& Staffid) {
        Order* order = new Order[100000];

        DBConn db;
        db.preparedStatement("SELECT o.OrderID,o.StaffID,o.TotalPrice,oi.ItemID,oi.ProductID, oi.Quantity, s.Name,p.Name PName FROM `order` o join `orderitem` oi on o.OrderID = oi.OrderID JOIN staff s ON s.StaffID = o.StaffID JOIN product p ON p.ProductID = oi.ProductID WHERE o.StaffID = ?");
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
            OrderCount++;
        }
        return order;
    }

    int MakeOrder(const int& StaffId, const double& price) {
        time_t now = std::time(nullptr);

        // Convert to local time
        tm local_time; 
        localtime_s(&local_time, &now); 

        // Print local time
        char buffer[26];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time); 
        string datetime_str(buffer);

        DBConn db;
        db.preparedStatement("INSERT INTO `order`(`StaffID`, `isActive`, `TotalPrice`, `DateTime`) VALUES (?,?,?,?)");
        db.stmt->setInt(1, StaffId); 
        db.stmt->setInt(2, 1); 
        db.stmt->setDouble(3, price); 
        db.stmt->setDateTime(4, datetime_str);
        db.QueryStatement(); 
    }

    void MakeOrderItem(const int& OrderID, const int& ProductId, const int& qtt) {
        time_t now = std::time(nullptr);

        tm local_time;
        localtime_s(&local_time, &now);

        char buffer[26];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
        string datetime_str(buffer);

        DBConn db;
        db.preparedStatement("INSERT INTO `orderitem`(`OrderID`, `ProductID`, `Quantity`, `DateTime`) VALUES (?,?,?,?)"); 
        db.stmt->setInt(1, OrderID);
        db.stmt->setInt(2, ProductId);
        db.stmt->setInt(3, qtt);
        db.stmt->setDateTime(4, datetime_str); 
        db.QueryStatement(); 
    } 

    void UpdateOrder(const int& ItemID, const int& Orderid) {

    }
     
    void UpdateOrderItem(const int& ItemID, const int& Orderid) {

    }

    void DeleteOrder(const int& ItemID) {
        DBConn db;
        db.preparedStatement("DELETE FROM `orderitem` WHERE ItemID = ?");
        db.stmt->setInt(1, ItemID);
        db.QueryStatement();
    }

    int getOrderID(double& price) {
        DBConn db;
        db.preparedStatement("SELECT * FROM `order` WHERE TotalPrice = ?"); 
        db.stmt->setDouble(1, price); 
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
    
#pragma endregion
};