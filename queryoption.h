/*
#ifndef QUERYOPTION_H
#define QUERYOPTION_H
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;


// This class as database management system contains several functions to send the query to the mysql database
// these function allows the system creating tables, creating todo list and task items, update names, and delete todo list or task items
// developers need to create an object to use the function in other files
// and connect to the database before make an instance of this class
// @note the current version will cause error running on MAC OS environment
// @note accessID function needs to be called before call other functions to avoid error happens

class queryOption
{
    private:
        string sqlQuery;
        const char* q = "";
        string currentID;
        int qstate = 1;
        MYSQL* con;
        MYSQL_ROW row;
        MYSQL_RES* res;
    public:

//         the constructor for the queryOption, this will set the initial value for the query
//         @param *conn the real connection from database
//         @note con the real connection from database and used in the queryOption to connect the database
//         @note row the row fetch from database table, the default set as NULL
//         @note res the query result get from the database table, the default set as NULL
//         @note currentID the current user id that used in the queryOption, the default set as ""

//        queryOption(MYSQL *conn) {
//            con = conn;
//            row = NULL;
//            res = NULL;
//            currentID = "";
//        }
        //headers
        void createCatalog();
        void createListTable();
        void newList(string user_id, string list_name, string dd, string mm, string yyyy);
        void newItem(string list_no, string item_name);
        string genListNo();
        string genItemNo();
        void accessID(string user_id);
        string getID();
        void getLists();
        void getItems(string listNo);
        void delItem(string itemNo);
        void delList(string listNo);
        void updateItem(string newUpdate, string itemNo);
        void updateList(string newUpdate, string listNo, int option);
        string getNewestListNo();
        void createUser();
        int checkIfExist(string location, string option);
};



#endif // QUERYOPTION_H

*/
