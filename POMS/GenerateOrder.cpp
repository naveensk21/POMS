#include "stdafx.h"
#include "GenerateOrder.h"
#include "PurchaseRequisition.h"
#include "Item.h"
#include "User.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

bool Order::OrderCheck(std::string oID) {
	int error = sqlite3_open("POMS.db", &db1);
	if (error) {
		std::cout << "Was not able to load sql" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}
	std::string query = "select * from Orders";
	error = sqlite3_prepare_v2(db1, query.c_str(), query.length(), &res1, &tail1);
	if (error != SQLITE_OK) {
		std::cout << "Was not able to load sql" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}

	while (sqlite3_step(res1) == SQLITE_ROW) {
		//For comparison value type char is converted to string 
		if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res1, 0))) == oID) {
			sqlite3_finalize(res1);
			sqlite3_close(db1);
			return true;
		}
	}
	sqlite3_finalize(res1);
	sqlite3_close(db1);
	return false;
}

void Order::AddOdr() {
	int check = 0;
	while (check != 1) {
		//obtain data from the user
		std::cin.ignore();
		std::cout << "\t----- Add Purchase Order -----" << std::endl;
		std::cout << "\tInput Purchase Order ID: ";
		std::getline(std::cin, POID);
		if (OrderCheck(POID) == true) {
			std::cout << "\tPurchase Order " + POID + " already exist in the database" << std::endl;
		}
		else {
			check = 1;
			Requisition r;
			int sCheck = 0;
			while (sCheck != 1) {
				std::cout << "\tInput Purchase Requisition ID: ";
				std::getline(std::cin, PRID);			
				if (r.RequisitionCheck(PRID) == false) {
					std::cout << "\tPurchase Requisition ID does not exist" << std::endl;
				}
				else {
					sCheck = 1;
					std::cout << "\tInput PM Name: ";
					std::getline(std::cin, PMName);
					//form connection and save the data
					int error = sqlite3_open("POMS.db", &db);
					if (error) {
						std::cout << "Was not able to load sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					std::string query = "INSERT INTO Orders VALUES('" + POID + "','" + PRID + "','" + PMName + "')";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Was not able to load sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					sqlite3_step(res);
					sqlite3_finalize(res);
					sqlite3_close(db);
					std::cout << "\tPurchase Order ID " + POID + " added to the database" << std::endl;
				}
			}			
		}
	}
}

void Order::EditOdr() {
	//open database
	std::cout << "\t----- Edit Purchase Order -----" << std::endl;
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "Was not able to load sql" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	int check = 0;
	while (check != 1) {
		//get item id to work with
		std::cout << "\tInput Purchase Order ID to Edit: ";
		std::getline(std::cin, POID);
		if (OrderCheck(PRID) == true) {
			int option = -1;
			while (option != 0) {
				std::cout << "\t------ Edit " + POID + "------" << std::endl;
				std::cout << "\tSelect which field to edit by choosing 1 or 2:" << std::endl;
				std::cout << "\t1. Purchase Requisition ID" << std::endl;
				std::cout << "\t0. Back to  previous menu" << std::endl;
				std::cout << "\t---------------------------" << std::endl;
				std::cin >> option;
				//edit item name
				if (option == 1) {
					std::cin.ignore();
					std::cout << "\Input Purchase Requisition ID: ";
					std::getline(std::cin, PRID);
					Requisition r;
					if (r.RequisitionCheck(PRID) == false) {
						std::cout << "\tPurchase Requisition ID is not found in the database" << std::endl;
					}
					else {
						std::string query = "UPDATE Orders SET PRID='" + PRID + "' WHERE POID='" + POID + "'";
						error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
						if (error != SQLITE_OK) {
							std::cout << "Was not able to load sql" << std::endl;
							sqlite3_close(db);
							system("pause");
						}
						//execute query
						sqlite3_step(res);
						//destruct query
						sqlite3_finalize(res);
						std::cout << "\tPurchase Requisition ID has being successfully changed" << std::endl;
					}

				} //edit supplier id 
				else if (option == 0) {
					//while look will break automatically
				}
				else {
					std::cout << "\tInvalid option selected" << std::endl;
				}
			}

		}
		else {
			std::cout << "\tPurchase Order ID " + POID + " not found in the database" << std::endl;
		}
	}
	sqlite3_close(db);
}

void Order::RemoveOdr() {
	int check = 0;
	while (check != 1) {
		std::cin.ignore();
		std::cout << "\t----- Delete Purchase Order -----" << std::endl;
		std::cout << "\tInput Purchase Order ID to Delete: ";
		std::getline(std::cin, POID);
		if (OrderCheck(POID) == true) {
			check = 1;
			int error = sqlite3_open("POMS.db", &db);
			if (error) {
				std::cout << "Was not able to load sql" << std::endl;
				sqlite3_close(db);
				system("PAUSE");
			}
			std::string query = "DELETE FROM Orders WHERE POID='" + POID + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Was not able to load sql" << std::endl;
				sqlite3_close(db);
				system("PAUSE");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			sqlite3_close(db);
			std::cout << "\tPurchase Order ID " + POID + " removed" << std::endl;
		}
		else {
			std::cout << "\tPurchase Order ID " + POID + " not found in the database" << std::endl;
		}
	}
}

void Order::ViewOdr() {
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "was unable to load the sql database" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::string query = "select * from Orders";
	error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
	if (error != SQLITE_OK) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::cout << "Purchase Order ID" << "\t" << "Purchase Requisition ID" << "\t" << "Purchase Manager Name" << std::endl;
	while (sqlite3_step(res) == SQLITE_ROW) {
		std::cout << sqlite3_column_text(res, 0) << "\t" << sqlite3_column_text(res, 1) << "\t" << sqlite3_column_text(res, 2) << std::endl;
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
}