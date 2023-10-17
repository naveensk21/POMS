#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"

class User {
	friend class Admin;
	void AddUsr();
	void EditUsr();
	void DeleteUsr();
	void ViewUsr();
	bool UsrCheck(std::string uName);
	sqlite3 *db, *db1;
	sqlite3_stmt *res, *res1;
	const char *errMSG;
	const char *tail, *tail1;
protected:
	std::string Username, Password, Name, Usertype;
	virtual void menu();
public:
	std::string getName();
	void Login();
	void Logout();
};