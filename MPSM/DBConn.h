#include <string>
#include <mysql/jdbc.h>

using namespace std;

class DBConn
{
private:
    sql::Connection* con;

public:
    sql::PreparedStatement* stmt;
    sql::ResultSet* rs;

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
};