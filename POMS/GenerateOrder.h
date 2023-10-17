#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"

class Order {
	std::string POID, PRID, PMName;
	sqlite3 *db, *db1;
	sqlite3_stmt *res, *res1;
	const char *errMSG;
	const char *tail, *tail1;
protected:
	void AddOdr();
	void EditOdr();
	void RemoveOdr();
public:
	bool OrderCheck(std::string oID);
	void ViewOdr();
};