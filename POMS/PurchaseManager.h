#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"
#include "User.h"
#include "GenerateOrder.h"

class PurchaseManager : public User, public Order {
public:
	void menu();
};