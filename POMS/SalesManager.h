#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"
#include "Item.h"
#include "Supplier.h"
#include "DailyItem.h"
#include "PurchaseRequisition.h"
#include "User.h"

class SalesManager : public User, public Item, public Supplier, public Daily, public Requisition {
public:
	void menu();
};