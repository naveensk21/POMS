#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"

class Daily {
	std::string ItemID;
	int Quantity, ItemStock;
	sqlite3 *db;
	sqlite3_stmt *res;
	const char *errMSG;
	const char *tail;
protected:
	void AddDaily();
};