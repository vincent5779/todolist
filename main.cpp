#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <string>
#include "queryOption.h"

using namespace std;

const char*hostname="127.0.0.1";
const char*username="root";
const char*password="";
const char*database="todo";
unsigned int port =3306;
const char* unixsocket=NULL;
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
                    string user_id= row[3];
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
    cout << "Wellcome to todo list: \n member login click 1.\n New user click 0.\n  ";

    cin >> number;
    if (number == 1) {
           
        string user = login(conn);
        //either can use id or username from the input
        cout << "return user: " << user<<endl;
        
//menu login
int choseMain;
while(choseMain!=3){
        choseMain=0;
    cout<<"User option:\n\t 1.Create new catalog enter 1.\n";
    cout<<"\t 2.See catalog enter 2.\n";
    cout<<"\t 3.logout enter 3.\n";
    cin>>choseMain;
    char YorN=NULL;

    switch(choseMain){
        case 1:
            while(YorN!='n'){
                cout<<"Wellcome to create new datalog\n";
                cout<<"Catalog name: ";
                string catalogName,listname,dd,mm,yyyy;
                cin>>catalogName;
                //cout<<"enter number for day: ";
                //cin>>dd;
                //cout<<"month:"; cin>>mm;
                //cout<<"year:"; cin>>yyyy;
                //queryReq.newList(user, catalogName, dd, mm, yyyy);
                queryReq.newList(user,catalogName,"10","10","2020");
                //add item or create new catalog
                cout<<"Do you want to add task in: "+catalogName+"\ny/n";
                string list_no=queryReq.getNewestListNo();
                cin>>YorN;
                //or you want to create another catalog
                while(YorN=='y'){
                    cout<<"Enter the task: ";
                    cin>>listname;
                    queryReq.newItem(list_no,listname);
                    cout<<"Add more..:y/n";
                    cin>>YorN;
                }
                cout<<"Do you want to add more catalog(y) or go back to main(n) y/n";
                cin>>YorN;
            }
            if(YorN=='n'){
                break;
            }
        case 2:
            cout<<"There are all the catalog you have...\n";
            queryReq.getLists();
            string choseB;
            cout<<"Which catalog you want to see the task:\n";
            cout<<"Enter the number of list_no: ";
            cin>>choseB;
            queryReq.getItems(choseB);
            //update or delete task
            cout<<"Do you want to add more item/update/delete or go back to main(n) y/n\n";
            cout<<"Just the option No for now";
            cin>>YorN;
            if(YorN=='n'){
                break;
            }
        }
}
//create catalog
//see catalog


    }
    else {
        createNewAccount(conn);
    }


    //testing
/*
    queryReq.createCatalog();
    queryReq.newList("25", "shopping list", "01", "12", "1999");
    queryReq.newItem("3", "egg1");
    queryReq.newItem("2", "bread1");
    queryReq.newItem("2", "milk1");
    queryReq.newItem("2", "beer1");
*/
//queryReq.newList("23", "shopping list", "01", "12", "1999");
    

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