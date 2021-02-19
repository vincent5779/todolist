#include "queryOption.h"
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <mysql.h>
#include <iomanip>
using namespace std;

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

void queryOption::newList(string user_id, string list_name, int dd, int mm, int yyyy) {
	string listNo = genListNo();
	sqlQuery = "INSERT INTO Catalog VALUES(" + user_id + ", " + listNo + ", '" + list_name + "', " + "current_date())";
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	if (qstate)
		cout << "Query Failed: failed to create new todo list." << endl;
}

void queryOption::newItem(string list_no, string item_name) {
	string itemNo = genItemNo();
	sqlQuery = "INSERT INTO List VALUES(" + list_no + ", " + itemNo + ", '" + item_name + "')";
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	if (qstate)
		cout << "Query Failed: failed to create new todo list." << endl;
}

string queryOption::genListNo() {
	string numCheck = "";
	int genNo = 0;
	do {
		genNo++;
		numCheck = to_string(genNo);
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

string queryOption::genItemNo() {
	string numCheck = "";
	int genNo = 0;
	do {
		genNo++;
		numCheck = to_string(genNo);
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

void queryOption::accessID(const char* user_id) {
	currentID = user_id;
}

string queryOption::getID() {
	string temp = currentID;
	return temp;
}

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

void queryOption::getItems(string listNo) {
	sqlQuery = "SELECT list.list_no, list.item_no, list.item_name, catalog.id "
		"FROM catalog "
		"JOIN list "
		"ON catalog.id = " + getID() + " "
		"AND catalog.list_no = list.list_no "
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

void queryOption::delItem(string itemNo) {
	sqlQuery = "DELETE FROM list WHERE item_no = " + itemNo;
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to delete the item from list" << endl;
}

void queryOption::delList(string listNo) {
	//disable safe mode
	sqlQuery = "SET SQL_SAFE_UPDATES = 0;";
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to delete the list" << endl;
	else
		cout << "done" << endl;
	//delete the list
	sqlQuery =	"DELETE list, catalog "
				"FROM list "
				"INNER JOIN catalog ON catalog.list_no = list.list_no "
				"WHERE list.list_no = " + listNo;
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to delete the list" << endl;
	else
		cout << "done" << endl;
	//enable safe mode
	sqlQuery = "SET SQL_SAFE_UPDATES = 1;";
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to delete the list" << endl;
	else
		cout << "done" << endl;
}