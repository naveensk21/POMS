#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"

class Item {
	std::string ItemID, ItemName, SupplierID, ItemDescription;
	int ItemStock;
	sqlite3 *db, *db1;
	sqlite3_stmt *res, *res1;
	const char *errMSG;
	const char *tail, *tail1;
protected:
	void AddItm();
	void EditItm();
	void DeleteItm();
public:
	bool ItemCheck(std::string iID);
	void ViewItm();
};