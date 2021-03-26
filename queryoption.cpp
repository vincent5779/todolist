/*

#include "queryoption.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>

#include <iomanip>
using namespace std;


//* create users table in mysql database, it will also create catalog and list table
//* id is the primary key of this table
//* @param none
//* @return none

void queryOption::createUser() {
    sqlQuery = "CREATE TABLE IF NOT EXISTS users ("
        "email varchar(50) NOT NULL, password varchar(50) NOT NULL, username VARCHAR(50) NOT NULL, id int(11) NOT NULL AUTO_INCREMENT, "
        "PRIMARY KEY(id))";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    if (!qstate)
        cout << "Users table created!" << endl;
    else
        cout << "Users table failed to create!" << endl;
    createCatalog();
}


//* create catalog table for all the todo list, it will also create list table
//* list_no is the primary key of this table
//* @param none
//* @return none

void queryOption::createCatalog() {
    sqlQuery =	"CREATE TABLE IF NOT EXISTS Catalog ("
                "id INT NOT NULL, list_no INT NOT NULL, list_name VARCHAR(50) NOT NULL, time DATE NOT NULL,"
                "PRIMARY KEY(list_no));";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    if (!qstate)
        cout << "Users catalog table created!" << endl;
    else
        cout << "Users catalog table failed to create!" << endl;
    createListTable();
}


//* create list table for all the items inside todo lists
//* item_no is the primary key of this table
//* @param none
//* @return none

void queryOption::createListTable() {
    sqlQuery =	"CREATE TABLE IF NOT EXISTS List ("
                "list_no INT NOT NULL, item_no INT NOT NULL, item_name VARCHAR(50) NOT NULL,"
                "PRIMARY KEY(item_no));";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    if (!qstate)
        cout << "Users list table created!" << endl;
    else
        cout << "Users list table failed to create!" << endl;
}


//* check if the user, email, or catalog name exist
//* @param location
//* @param option
//* @return exist

int queryOption::checkIfExist(string location, string option) {
    if (location == "checkcatalog") {
        sqlQuery = "SELECT list_name FROM catalog WHERE id = " + getID() + "";
    }
    else {
        sqlQuery = "SELECT `" + location + "` FROM `users`";
    }
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    int exist = 0;
    res = mysql_store_result(con);
    int count = mysql_num_fields(res);
    while (row = mysql_fetch_row(res)) {
        for (int i = 0;i < count;i++) {
            if (option == row[i]) {
                exist -= 1;
                //cout<<exit;
                return exist;
            }
        }
    }
    return exist;

}


//* create a new todo list in catalog table
//* @param user_id the current user's id that can match up in the database
//* @param list_name the name of the todo list that input by user
//* @param dd the day set for this todo list
//* @param mm the month set for this todo list
//* @param yyyy the year set for this todo list
//* @return none

void queryOption::newList(string user_id, string list_name, string dd, string mm, string yyyy) {
    string listNo = genListNo();
    string dateinsert = yyyy + "-" + mm + "-" + dd;
    sqlQuery = "INSERT INTO Catalog (id, list_no, list_name, time) VALUES(" + user_id + ", " + listNo + ", '" + list_name + "', '" + dateinsert + "')";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    if (qstate)
        cout << "Query Failed: failed to create new newList." << endl;
}


//* create a new task item in the list table
//* @param list_no the specific todo list user want to add task in it
//* @param item_name the name of the task input by user
//* @return none

void queryOption::newItem(string list_no, string item_name) {
    string itemNo = genItemNo();
    sqlQuery = "INSERT INTO List VALUES(" + list_no + ", " + itemNo + ", '" + item_name + "')";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    if (qstate)
        cout << "Query Failed: failed to create new item." << endl;
}


//* generate the list number which has not been used in the catalog table, and always check the available number from 0
//* @param none
//* @return numCheck the list number that has not been used in the catalog table

string queryOption::genListNo() {
    string numCheck = "";
    int genNo = 0;
    do {
        genNo++;
        stringstream ss;
        ss << genNo;
        ss >> numCheck;
        sqlQuery = "SELECT list_no FROM Catalog where list_no = " + numCheck;
        q = sqlQuery.c_str();
        qstate = mysql_query(con, q);
        //error message
        if (qstate)
            cout << "Query Failed: failed to generate list number." << endl;
        res = mysql_store_result(con);
    } while (row = mysql_fetch_row(res));
    return numCheck;
}

// generate the item number which has not been used in the list table, and always check the available number from 0
//* @param none
//* @return numCheck the item number that has not been used in the list table

string queryOption::genItemNo() {
    string numCheck = "";
    int genNo = 0;
    do {
        genNo++;
        stringstream ss;
        ss << genNo;
        ss >> numCheck;
        sqlQuery = "SELECT item_no FROM List where item_no = " + numCheck;
        q = sqlQuery.c_str();
        qstate = mysql_query(con, q);
        //error message
        if (qstate)
            cout << "Query Failed: failed to generate item number." << endl;
        res = mysql_store_result(con);
    } while (row = mysql_fetch_row(res));
    return numCheck;
}


// set and store the current user id to the system
// @param user_id the current user id
// @return none

void queryOption::accessID(string user_id) {
    currentID = user_id;
}


//return the user id to identify the current user
//@param none
// @return temp current user id

string queryOption::getID() {
    string temp = currentID;
    return temp;
}


//*display all the todo list the current user has in the catalog table
// @param none
// @return none

void queryOption::getLists() {
    sqlQuery =	"SELECT list_no, list_name, time "
                "FROM Catalog "
                "WHERE id = " + getID();
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to get the todo lists from catalog" << endl;
    res = mysql_store_result(con);
    cout << left << setw(20) << "list_no";
    cout << left << setw(20) << "list_name";
    cout << left << setw(20) << "time" << endl;
    while (row = mysql_fetch_row(res)) {
        for (int i = 0; i < 3; i++) {
            cout << left;
            cout << setw(20) << row[i];
        }
        cout << endl;
    }
}


// display all the task items inside the todo list that current user has in the list table
// @param listNo the todo list that current user want to access into it
// @return none

void queryOption::getItems(string listNo) {
    sqlQuery = "SELECT list.list_no, list.item_no, list.item_name, catalog.id "
        "FROM catalog "
        "JOIN list "
        "ON catalog.list_no = list.list_no "
        "AND list.list_no = " + listNo;
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to get the items from list" << endl;
    res = mysql_store_result(con);
    cout << left << setw(20) << "list_no";
    cout << left << setw(20) << "item_no";
    cout << left << setw(20) << "item_name";
    cout << left << setw(20) << "user_id" << endl;
    while (row = mysql_fetch_row(res)) {
        for (int i = 0; i < 4; i++) {
            cout << left;
            cout << setw(20) << row[i];
        }
        cout << endl;
    }
}


// delete one task item in the list table
// @param itemNo the specific item that current user want to delete
// @return none

void queryOption::delItem(string itemNo) {
    sqlQuery = "DELETE FROM list WHERE item_no = " + itemNo;
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to delete the item from list" << endl;
    else
        cout << "The item_no " + itemNo + " has been deleted" << endl;
}


//delete the todo list including the task items inside the list
//@param listNo the specific todo list number that current user want to delete
//@return none

void queryOption::delList(string listNo) {
    //disable safe mode
    sqlQuery = "SET SQL_SAFE_UPDATES = 0;";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to turn off the safe mode" << endl;
    //delete the items
    sqlQuery = "DELETE FROM list WHERE list_no = " + listNo;
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to delete the items in this todo list" << endl;
    sqlQuery = "DELETE FROM catalog WHERE list_no = " + listNo;
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to delelte the list" << endl;
    else
        cout << "List_no " + listNo + " has been deleted" << endl;
    //enable safe mode
    sqlQuery = "SET SQL_SAFE_UPDATES = 1;";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to turn on the safe mode" << endl;
}


// update a task item's name in the list table
// @param newUpdate the name to replace the old name as new name for item name
// @param itemNo the target task item number that needs to update
// @return none

void queryOption::updateItem(string newUpdate, string itemNo) {
    sqlQuery =	"UPDATE list SET item_name = '" + newUpdate + "' WHERE item_no = " + itemNo;
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to update the item's name" << endl;
}


// update a todo list name in the catalog table
// @param newUpdate the name to replace the old name as new name for todo list name
// @param listNo the taget todo list number that needs to update
// @param option the option to make different changes for todo list: 0 to change the name of todo list, 1 to change the time of todo list
// @return none

void queryOption::updateList(string newUpdate, string listNo, int option) {

    //if 0 = update name, 1 = update time
    switch (option) {
        case 0:
            sqlQuery = "UPDATE catalog SET list_name = '" + newUpdate + "' WHERE list_no = " + listNo;
            q = sqlQuery.c_str();
            qstate = mysql_query(con, q);
            //error message
            if (qstate)
                cout << "Query Failed: failed to update the list's name" << endl;
            break;
        case 1:
            sqlQuery = "UPDATE catalog SET time = " + newUpdate + " WHERE list_no = " + listNo;
            q = sqlQuery.c_str();
            qstate = mysql_query(con, q);
            //error message
            if (qstate)
                cout << "Query Failed: failed to update the time" << endl;
            break;
        default:
            cout << "No date has been updated" << endl;
            break;
    }
}


// return the newest list number that current user is creating and using
// @param none
//@return resultTemp returns the newest list number for the current user

string queryOption::getNewestListNo() {
    string resultTemp = "";
    sqlQuery = "SELECT list_no FROM catalog WHERE id = " + getID() + " ORDER BY list_no DESC LIMIT 1";
    q = sqlQuery.c_str();
    qstate = mysql_query(con, q);
    //error message
    if (qstate)
        cout << "Query Failed: failed to return the newest list_no" << endl;
    res = mysql_store_result(con);
    row = mysql_fetch_row(res);
    resultTemp = row[0];
    return resultTemp;
}
*/
