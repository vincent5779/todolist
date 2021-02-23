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
string choseCata,update;
char str [100],stri[200];
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

void taskMenu(MYSQL* conn,string user, string list_no){
    queryOption queryReq(conn);
    queryReq.accessID(user);

    int choice;

    while(choice!=4){
        cout<<"1.ADD more task\n2.Update task\n3.Delete task\n4. Go back.\n";
        cin>>choice;
        switch(choice){
            case 1:
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
                break;
            case 2:
                cout<<"Which task you want to update: ";
                cin>>choseCata;
                cout<<"Change to: ";
                //scanf(" %[^\n]s",stri);
                //string ToS(stri);
                //update=ToS;
                cin>>update;
                queryReq.updateItem(update, choseCata);
                break;
            case 3:
                cout<<"Which task you want to delete: ";
                cin>>choseCata;
                queryReq.delList(choseCata);
                break;
            case 4:
                break;
            }
    }
}
void personalMenu(MYSQL* conn, string user){
    queryOption queryReq(conn);
    queryReq.accessID(user);
    queryReq.getLists();
    int choice;
while(choice!=4){
    cout<<"what do you want with the catalog: \n";
    cout<<"1. Display all the tasks in a the list.\n";
    cout<<"2. Change an existing task name in this list.\n";
    cout<<"3. Delete an existing task in this list.\n";
    cout<<"4. Back to previous menu.\n";
    cin>>choice;
    switch(choice){
        case 1:
            //1. Display all the tasks in catalog
            cout<<"Enter the list_no want to display:\n";
            cin>>choseCata;
            queryReq.getItems(choseCata);
            //taskMenu
            cout<<"what do you want with those list: \n";
            taskMenu(conn,user,choseCata);

            break;
        case 2:
            //2. Change an existing catalog name
            //cout<<"Change an existing catalog name";
            cout<<"Enter the list_on to update it\n";
            cin>>choseCata;
            cout<<"Change name of list 0.\n";
            cout<<"Change date of list 1.\n";
                int option;
                cin>>option;
            cout<<"Change to: ";
            //scanf(" %[^\n]s",str);
            //string ToS(str);
            //update=ToS;
            cin>>update;
            queryReq.updateList(update, choseCata,option);
            cout<<"Go back to CatalogMenu(y)\n or Log out(n) y/n: ";
            cin>>YorN;
            if(YorN=='y'){break;}
            else{
                //cout<<"You log out!!!";
                nutrualN=5;
                break;}
        case 3:
            //3. Delete an existing catalog
            cout<<"Enter the list_on to delete: ";
            cin>>choseCata;
            queryReq.delList(choseCata);
            break;

}
}
}
void catalogMenu(MYSQL* conn, string user){
    queryOption queryReq(conn);
    queryReq.accessID(user);
    while(nutrualN!=3){
        nutrualN=0;
        cout<<"User CatalogMenu:\n\t 1. Create new to-do list.\n";
        cout<<"\t 2. Display all personal to-do list.\n";
        cout<<"\t 3. Go back to loginMenu.\n";
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
                personalMenu(conn,user);
                break;
            case 3:
                break;
            }
    }
        cout<<"You have been log out.\n";
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
       catalogMenu(conn,user);
    }
    else if(number == 2) {
        createNewAccount(conn);
    }else
        {
        cout<<"You exit the program!!\n";
         return 0;
    }

}