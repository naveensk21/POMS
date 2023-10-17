#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"
#include "Item.h"
#include "Supplier.h"
#include "PurchaseRequisition.h"
#include "GenerateOrder.h"
#include "DailyItem.h"

class Admin : public Item, public Supplier, public Requisition, public Order, public Daily  {
public:
	void menu();
};