#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include "queryOption.h"

using namespace std;

const char*hostname="127.0.0.1";
const char*username="root";
const char*password="";
const char*database="todo";
unsigned int port =3306;
const char* unixsocket=NULL;
unsigned long clinentflag = 0;
string usernamedb, emailbd, passdb,user_id;
string catalogName,listname,dd,mm,yyyy;
int nutrualN;
char YorN=NULL;
string choseB;
char str [100];
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

void createNewAccount(MYSQL* conn);
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
                    user_id= row[3];
                    return user_id;
                }
            }
            if (count == 0) {
                cout << "Wrong username or pass..\n Please try again 1...\n Create a new one 2.";
                int again;
                cin>>again;
                if(again==2){
                    createNewAccount(conn);
                }
            }
        }
    }
}

void createNewAccount(MYSQL* conn) {
    queryOption queryReq(conn);
    cout << "Create new account" << endl;
    int qstate = 0;
    stringstream ss;
    //user input create new account
    int exist = 0;
    //check if the exist user
    do {
        cout << "Enter username: ";
        cin >> usernamedb;
        exist=queryReq.checkIfExist("username",usernamedb);
        if (exist < 0) {
        cout << "This user already exist. Please Input new one...\n";}
    } while (exist < 0);

    exist = 0;
    do {
        cout << "Enter email:" << endl;
        cin >> emailbd;
        exist=queryReq.checkIfExist("email",emailbd);
        if (exist < 0) {
        cout << "This email already exist. Please Input new one...\n";}
    } while (exist < 0);

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
void UpdateDelecteOp(MYSQL* conn,string list_no){
    queryOption queryReq(conn);
    cout<<"catalog option: \n 1.del the catalog. \n 2. add more task to catalog \n 3.Del task in the catalog\n back main>>0 ";
    cin>>nutrualN;
    switch(nutrualN){
        //1.del the catalog
        case 1:
            queryReq.delList(list_no);
            break;
        case 2://2. add more task to catalog
            YorN='y';
            //or you want to create another catalog
            while(YorN=='y'){
                cout<<"Enter the task: ";
                scanf(" %[^\n]s",str);
                string ToS(str);
                listname=ToS;
                queryReq.newItem(list_no,listname);
                cout<<"Add more..: y/n";
                cin>>YorN;
            }
            //cout<<"Do you want to add more catalog(y) or go back to main(n) y/n :";
            //cin>>YorN;
            break;
        case 3://3.Del task in the catalog
            queryReq.getItems(list_no);
            cout<<"Which task do you want to del\n enter the item_no: ";
            cin>>choseB;
            queryReq.delItem(choseB);
            break;
        case 0:
            break;
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

    queryReq.createUser();
    cout << "Wellcome to todo list: \n member login click 1.\n New user click 0.\n  ";
    cin >> number;
    if (number == 1) {

        string user = login(conn);
        //either can use id or username from the input
        cout << "return user: " << user<<endl;
        queryReq.accessID(user);
//menu login
        while(nutrualN!=3){
            nutrualN=0;
            cout<<"User option:\n\t 1.Create new catalog enter 1.\n";
            cout<<"\t 2.See catalog enter 2.\n";
            cout<<"\t 3.logout enter 3.\n";
            cin>>nutrualN;

            switch(nutrualN){
                case 1:
                    while(YorN!='n'){
                        cout<<"Wellcome to create new datalog\n";
                        string catalogName,listname,dd,mm,yyyy;
                        int exist = 0;
                        do {
                            cout<<"Catalog name: ";
                            scanf(" %[^\n]s",str);
                            string CToS(str);
                            catalogName=CToS;
                            exist=queryReq.checkIfExist("checkcatalog",catalogName);
                            if (exist < 0) {
                            cout << "This catalog already exist. Please Input new one...\n";}
                        } while (exist < 0);
                        //cout<<"enter number for day: ";
                        //cin>>dd;
                        //cout<<"month:"; cin>>mm;
                        //cout<<"year:"; cin>>yyyy;
                        //queryReq.newList(user, catalogName, dd, mm, yyyy);
                        queryReq.newList(user,catalogName,"10","10","2020");
                        //add item or create new catalog
                        cout<<"Do you want to add task in: "+catalogName+"\n y/n: ";
                        string list_no=queryReq.getNewestListNo();
                        cin>>YorN;
                        //or you want to create another catalog
                        while(YorN=='y'){
                            cout<<"Enter the task: ";
                            scanf(" %[^\n]s",str);
                            string ToS(str);
                            listname=ToS;
                            queryReq.newItem(list_no,listname);
                            cout<<"Add more..: y/n";
                            cin>>YorN;
                        }
                        cout<<"Do you want to add more catalog(y) or go back to main(n) y/n :";
                        cin>>YorN;
                    }
                    if(YorN=='n'){
                        break;
                    }
                case 2:
                    cout<<"There are all the catalogs you have...\n";
                    queryReq.getLists();
                    cout<<"Which catalog you want to see the task:\n";
                    cout<<"Enter the number of list_no: ";
                    cin>>choseB;
                    queryReq.getItems(choseB);
                    //update or delete task
                    cout<<"Do you want to add more item/update/delete(y)or go back to main(n) y/n: \n";
                    //cout<<"Just the option No for now";
                    cin>>YorN;
                    if(YorN=='y'){
                        UpdateDelecteOp(conn, choseB);
                    }
                    if(YorN=='n'){
                        break;
                    }
                }
        }
        cout<<"You have been log out.\n";
//create catalog
//see catalog


    }
    else {
        createNewAccount(conn);
    }
    return 0;
}
