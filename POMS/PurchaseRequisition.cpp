#include "stdafx.h"
#include "PurchaseRequisition.h"
#include "Item.h"
#include "User.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

bool Requisition::RequisitionCheck(std::string rID) {
	int error = sqlite3_open("POMS.db", &db1);
	if (error) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}
	std::string query = "select * from Requisitions";
	error = sqlite3_prepare_v2(db1, query.c_str(), query.length(), &res1, &tail1);
	if (error != SQLITE_OK) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}

	while (sqlite3_step(res1) == SQLITE_ROW) {
		//change char value to string value
		if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res1, 0))) == rID) {
			sqlite3_finalize(res1);
			sqlite3_close(db1);
			return true;
		}
	}
	sqlite3_finalize(res1);
	sqlite3_close(db1);
	return false;
}

void Requisition::AddRequisition() {
	int check = 0;
	std::cin.ignore();
	while (check != 1) {
		//obtain input		
		std::cout << "\t====== Add Requisition ======" << std::endl;
		std::cout << "\tInput Requisition ID: ";
		std::getline(std::cin, PRID);
		if (RequisitionCheck(PRID) == true) {
			std::cout << "\tPurchase Requisition " + PRID + " already exist" << std::endl;
		}
		else {
			check = 1;
			Item i;
			int sCheck = 0;
			while (sCheck != 1) {
			std::cout << "\tInput Item ID: ";
			std::getline(std::cin, ItemID);			
				if (i.ItemCheck(ItemID) == false) {
					std::cout << "\tItem ID is not found" << std::endl;
				}
				else {
					sCheck = 1;
					std::cout << "\tInput SM Name: ";
					std::getline(std::cin, SMName);
					std::cout << "\tInput Quantity: ";
					std::cin >> ItemStock;
					std::cin.ignore();
					std::cout << "\tInput Date: ";
					std::getline(std::cin, Date);
					//connection to database
					int error = sqlite3_open("POMS.db", &db);
					if (error) {
						std::cout << "was unable to load the sql databas" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					std::string query = "INSERT INTO Requisitions VALUES('" + PRID + "','" + ItemID + "','" + std::to_string(ItemStock) + "','" + Date + "','" + SMName + "')";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "was unable to load the sql databas" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					sqlite3_step(res);
					sqlite3_finalize(res);
					sqlite3_close(db);
					std::cout << "\tRequisition ID " + PRID + " added to the database" << std::endl;
				}
			}			
		}
	}
}

void Requisition::EditRequisition() {
	std::cout << "\t====== Edit Requisition ======" << std::endl;
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	int check = 0;
	while (check != 1) {
		std::cout << "\tEnter Requistion ID to Edit: ";
		std::getline(std::cin, PRID);
		if (RequisitionCheck(PRID) == true) {
			check = 1;
			int option = -1;
			while (option != 0) {
				std::cout << "\t------ Edit " + PRID + "------" << std::endl;
				std::cout << "\tSelect field to edit:" << std::endl;
				std::cout << "\t1. Item ID" << std::endl;
				std::cout << "\t2. Quantity" << std::endl;
				std::cout << "\t3. Date" << std::endl;
				std::cout << "\t0. Back to  previous menu" << std::endl;
				std::cout << "\t---------------------------" << std::endl;
				std::cin >> option;

				if (option == 1) {
					std::cin.ignore();
					std::cout << "\tInput Item ID: ";
					std::getline(std::cin, ItemID);
					Item i;
					if (i.ItemCheck(ItemID) == false) {
						std::cout << "\tItem ID is not found in the database" << std::endl;
					}
					else {
						std::string query = "UPDATE Requisitions SET ItemID='" + ItemID + "' WHERE PRID='" + PRID + "'";
						error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
						if (error != SQLITE_OK) {
							std::cout << "was unable to load the sql databas" << std::endl;
							sqlite3_close(db);
							system("pause");
						}
						sqlite3_step(res);
						sqlite3_finalize(res);
						std::cout << "\tItem ID changed" << std::endl;
					}

				} 
				else if (option == 2) {
					std::cout << "\tEnter new Quantity: ";
					std::cin >> ItemStock;
					std::string query = "UPDATE Requisitions SET Quantity='" + std::to_string(ItemStock) + "' WHERE PRID='" + PRID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "was unable to load the sql databas" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					sqlite3_step(res);
					sqlite3_finalize(res);
					std::cout << "\tQuantity changed" << std::endl;
				}  
				else if (option == 3) {
					std::cin.ignore();
					std::cout << "\tInput new Date: ";
					std::getline(std::cin, Date);
					std::string query = "UPDATE Requisitions SET Date='" + Date + "' WHERE PRID='" + PRID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "was unable to load the sql databas" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					
					sqlite3_step(res);
					sqlite3_finalize(res);
					std::cout << "\tDate changed" << std::endl;
				}  
				else if (option == 0) {
				}
				else {
					std::cout << "\tInvalid option" << std::endl;
				}
			}

		}
		else {
			std::cout << "\tPurchase Requisition ID " + PRID + " not found in the database" << std::endl;
		}
	}
	sqlite3_close(db);
}

void Requisition::DeleteRequisition() {
	int check = 0;
	while (check != 1) {
		std::cin.ignore();
		std::cout << "\t====== Delete Requisition ======" << std::endl;
		std::cout << "\tInput Requisition ID to Delete: ";
		std::getline(std::cin, PRID);
		if (RequisitionCheck(PRID) == true) {
			check = 1;
			int error = sqlite3_open("POMS.db", &db);
			if (error) {
				std::cout << "was unable to load the sql databas" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			std::string query = "DELETE FROM Requisitions WHERE PRID='" + PRID + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "was unable to load the sql databas" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			sqlite3_close(db);
			std::cout << "\tRequisition ID " + PRID + " deleted from the database" << std::endl;
		}
		else {
			std::cout << "\tRequisition ID " + PRID + " not found in the database" << std::endl;
		}
	}
}

void Requisition::ViewRequisitions() {
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::string query = "select * from Requisitions";
	error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
	if (error != SQLITE_OK) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::cout << "Requisition ID" << "\t" << "Item ID" << "\t" << "Quantity" << "\t" << "Date" << "\t" << "Supplier Manager Name" << std::endl;
	while (sqlite3_step(res) == SQLITE_ROW) {
		std::cout << sqlite3_column_text(res, 0) << "\t" << sqlite3_column_text(res, 1) << "\t" << sqlite3_column_text(res, 2) << "\t" << sqlite3_column_text(res, 3) << "\t" << sqlite3_column_text(res, 4) << std::endl;
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
}