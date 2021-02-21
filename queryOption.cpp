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

void queryOption::newList(string user_id, string list_name, string dd, string mm, string yyyy) {
	string listNo = genListNo();
	string dateinsert = yyyy + "-" + mm + "-" + dd;
	sqlQuery = "INSERT INTO Catalog (id, list_no, list_name, time) VALUES(" + user_id + ", " + listNo + ", '" + list_name + "', '" + dateinsert + "')";
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
		cout << "Query Failed: failed to create new item." << endl;
}

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

void queryOption::accessID(string user_id) {
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

void queryOption::delItem(string itemNo) {
	sqlQuery = "DELETE FROM list WHERE item_no = " + itemNo;
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to delete the item from list" << endl;
	else
		cout << "The item_no " + itemNo + "has been deleted" << endl;
}

void queryOption::delList(string listNo) {
	//disable safe mode
	sqlQuery = "SET SQL_SAFE_UPDATES = 0;";
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to turn off the safe mode" << endl;
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
		cout << "The list_no " + listNo + "has been deleted" << endl;
	//enable safe mode
	sqlQuery = "SET SQL_SAFE_UPDATES = 1;";
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to turn on the safe mode" << endl;
}

void queryOption::updateItem(string newUpdate, string itemNo) {
	sqlQuery =	"UPDATE list SET item_name = '" + newUpdate + "' WHERE item_no = " + itemNo;
	q = sqlQuery.c_str();
	qstate = mysql_query(con, q);
	//error message
	if (qstate)
		cout << "Query Failed: failed to update the item's name" << endl;
}

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