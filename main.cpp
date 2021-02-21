#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <string>
#include "queryOption.h"

using namespace std;

const char* hostname = "localhost";
const char* username = "root";
const char* password = "nokia3310";
const char* database = "todolist";
unsigned int port = 3306;
const char* unixsocket = NULL;
unsigned long clinentflag = 0;
string usernamedb, emailbd, passdb;
MYSQL_ROW row;
MYSQL_RES* res;


MYSQL* connectdatabase() {
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, hostname, username, password, database, port, unixsocket, clinentflag);
    if (conn) {
        cout << "Database Connected!"<< endl;
    }
    else {
        cout << "Database Connection Fail!" << endl;
    }
    return conn;
}


//login site
string login(MYSQL* conn) {
    cout << "LOGIN:\n";
    int count = 0;
    while (count == 0) {
        cout << "Enter username: " << endl;
        cin >> usernamedb;
        cout << "Enter password: " << endl;
        cin >> passdb;

        int qstate = mysql_query(conn, "SELECT * FROM users");
        if (!qstate) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                //pass[1] username[2]
                if (row[1] == passdb && row[2] == usernamedb) {
                    // count=1;
                    cout << "Logined\n";
                    string user_id = row[3];
                    return user_id;
                }
            }
            if (count == 0) {
                cout << "Wrong username or pass..\n Please try again...\n";
            }
        }
    }
}

void createNewAccount(MYSQL* conn) {
    cout << "Create new account" << endl;
    int qstate = 0;
    stringstream ss;
    //user input create new account
    int exist = 0;
    //check if the exist user
    do {
        cout << "Enter username: ";
        cin >> usernamedb;
        if (conn) {
            int check = mysql_query(conn, "SELECT `username` FROM `users`");
            //exist=1;
            exist = 0;
            if (!check) {
                res = mysql_store_result(conn);
                int count = mysql_num_fields(res);
                while (row = mysql_fetch_row(res)) {
                    for (int i = 0;i < count;i++) {
                        if (usernamedb == row[i]) {
                            exist -= 1;
                            //cout<<exit;
                        }
                    }
                }
                if (exist < 0) {
                    cout << "This user already exist. Please Input new one...\n";
                }
            }
        }
        else {

            cout << "Failed to load";
        }
    } while (exist < 0);

    cout << "Enter email:" << endl;
    cin >> emailbd;
    cout << "Enter password:" << endl;
    cin >> passdb;
    ss << "INSERT INTO users (username, email, password) VALUES('" + usernamedb + "', '" + emailbd + "', '" + passdb + "')";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if (qstate == 0) {
        cout << "record inserted..";
        //login(conn);
        //either login or return username
    }
    else {
        cout << "failed to insert..";
    }

}

void tempDis() {
    
}


int main()
{
    //connect database
    MYSQL* conn = connectdatabase();
    queryOption queryReq(conn);
    int number;
    if (!conn) {
        cout << "Invalid Access" << endl;
        return 0;
    }
    /*
    cout << "Wellcome to todo list: \n member login click 1.\n New user click 0.\n  ";

    cin >> number;
    if (number == 1) {
        string user = login(conn);
        //either can use id or username from the input
        cout << "return user: " << user;
        //cout<<usernamedb;

    }
    else {
        createNewAccount(conn);
    }
    */

    //testing
    /*
    queryReq.createCatalog();
    queryReq.newList("34", "shopping list", 01, 12, 1999);
    queryReq.newItem("1", "egg");
    queryReq.newItem("1", "bread");
    queryReq.newItem("1", "milk");
    queryReq.newItem("1", "beer");
    */
    //test display
    cout << endl;
    cout << endl;
    queryReq.getLists();
    cout << endl;
    cout << endl;
    queryReq.getItems("1");
    /*
    string showTemp;
    showTemp = queryReq.getNewestListNo();
    cout << showTemp << endl;
    */

    //queryReq.updateList("walmart","2", 0);
    /*
    
    
    cout << endl;
    cout << endl;
    queryReq.getLists();
    cout << endl;
    cout << endl;
    queryReq.getItems("2");
    */

    cout << "test complete!" << endl;

    //Acceesed to the personal todo list
    /*
    cout << "enter the target user_id: ";
    cin >> number;
    stringstream sqlString;
    sqlString << "select * from users where id = " << number;
    int qstate = mysql_query(conn, sqlString.str().c_str());
    if (!qstate) {
        cout << "query approved..." << endl;
        res = mysql_use_result(conn);
        while (row = mysql_fetch_row(res)) {
            cout << row[0] << endl;
        }
    }
    else {
        cout << "query failed..." << endl;
    }
    */

    return 0;
}