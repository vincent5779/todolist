#pragma once
#ifndef QUERYOPTION_H
#define QUERYOPTION_H
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include <mysql.h>
#include <iomanip>
using namespace std;


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
		queryOption(MYSQL *conn) {
			con = conn;
			row = NULL;
			res = NULL;
			currentID = "34";		//temp need to remove after testing
		}
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
};

#endif
