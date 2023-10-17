#include "stdafx.h"
#include "Item.h"
#include "DailyItem.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

void Daily::AddDaily() {
	//obtain input from the logged user
	std::cin.ignore();
	std::cout << "\t----- Daily Item-wise Sales entry-----" << std::endl;
	std::cout << "\tEnter Item ID: ";
	std::getline(std::cin, ItemID);
	Item i;
	if (i.ItemCheck(ItemID) == false) {
		std::cout << "\tItem " + ItemID + " not found" << std::endl;
	}
	else {
		std::cout << "\tInput Quantity: ";
		std::cin >> Quantity;
		//create a connection with the database and save the data	
		int error = sqlite3_open("POMS.db", &db);
		if (error) {
			std::cout << "Was not able to load sql" << std::endl;
			sqlite3_close(db);
			system("pause");
		}
		std::string query = "select ItemStock from Items where ItemID='" + ItemID + "'";
		error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
		if (error != SQLITE_OK) {
			std::cout << "Was not able to load sql" << std::endl;
			sqlite3_close(db);
			system("pause");
		}
		while (sqlite3_step(res) == SQLITE_ROW) {
			ItemStock = sqlite3_column_int(res, 0);
		}
		sqlite3_step(res);
		sqlite3_finalize(res);
		if (ItemStock >= Quantity) {
			ItemStock -= Quantity;
			query = "UPDATE Items SET ItemStock='" + std::to_string(ItemStock) + "' WHERE ItemID='" + ItemID + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Was not able to load sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			std::cout << "\t" <<Quantity<<" was minus from " + ItemID << std::endl;
		}
		else {
			std::cout << "Quantity input is greater than the current quantity of item" << std::endl;
		}		
		sqlite3_close(db);
	}
}