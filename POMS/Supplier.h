#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"

class Supplier {
	std::string SupplierID, SupplierName, SupplierContact, SupplierEmail, SupplierAccount, SupplierAddress;
	sqlite3 *db, *db1;
	sqlite3_stmt *res, *res1;
	const char *errMSG;
	const char *tail, *tail1;	
protected:
	void AddSpplier();
	void EditSpplier();
	void DeleteSpplier();
public:
	bool SupplierCheck(std::string sID);
	void ViewSpplier();
};
