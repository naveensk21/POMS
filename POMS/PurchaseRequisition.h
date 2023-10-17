#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"

class Requisition {
	std::string PRID, ItemID, Date, SMName;
	int ItemStock;
	sqlite3 *db, *db1;
	sqlite3_stmt *res, *res1;
	const char *errMSG;
	const char *tail, *tail1;
protected:
	void AddRequisition();
	void EditRequisition();
	void DeleteRequisition();
public:
	bool RequisitionCheck(std::string rID);
	void ViewRequisitions();
};