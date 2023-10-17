#include "stdafx.h"
#include "Item.h"
#include "Supplier.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

//identify if the data is in the database (existense) 
bool Item::ItemCheck(std::string iID) {
	int error = sqlite3_open("POMS.db", &db1);
	if (error) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}
	std::string query = "select * from Items";
	error = sqlite3_prepare_v2(db1, query.c_str(), query.length(), &res1, &tail1);
	if (error != SQLITE_OK) {
		std::cout << "was unable to load the sql databas" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}

	while (sqlite3_step(res1) == SQLITE_ROW) {
		//conversion of char value to string value
		if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res1, 0))) == iID) {
			sqlite3_finalize(res1);
			sqlite3_close(db1);
			return true;
		}
	}	
	sqlite3_finalize(res1);
	sqlite3_close(db1);
	return false;
}

//obtain data from the user
void Item::AddItm() {
	int check = 0;
	while (check != 1) {
		std::cin.ignore();
		std::cout << "\t----- Add Item ------" << std::endl;
		std::cout << "\tEnter Item ID: ";
		std::getline(std::cin, ItemID);
		if (ItemCheck(ItemID) == true) {
			std::cout << "\tItem " + ItemID + " already exist in the database" << std::endl;
		}
		else {
			check = 1;
			std::cout << "\tInput Item Name: ";
			std::getline(std::cin, ItemName);
			int sCheck = 0;
			while (sCheck != 1) {
				std::cout << "\tInput Supplier ID: ";
				std::getline(std::cin, SupplierID);
				Supplier s;			
				if (s.SupplierCheck(SupplierID) == false) {
					std::cout << "\tSupplier ID is not found in the database" << std::endl;
				}
				else {
					sCheck = 1;
					std::cout << "\tInput Item Description: ";
					std::getline(std::cin, ItemDescription);

					std::cout << "\tInput Item Stock: ";
					std::cin >> ItemStock;
					//the connection is made to save the data to the database
					int error = sqlite3_open("POMS.db", &db);
					if (error) {
						std::cout << "was unable to load the sql databas" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					std::string query = "INSERT INTO Items VALUES('" + ItemID + "','" + ItemName + "','" + SupplierID + "','" + ItemDescription + "'," + std::to_string(ItemStock) + ")";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "was unable to load the sql databas" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					sqlite3_step(res);
					sqlite3_finalize(res);
					sqlite3_close(db);
					std::cout << "\tItem ID " + ItemID + " added to the database" << std::endl;
				}
			}
		}
	}
	
}

void Item::EditItm() {
	//create database
	std::cin.ignore();
	std::cout << "\t====== Edit Item ======" << std::endl;
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "Couldn't open Database" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	//obtain item id
	int check = 0;
	while (check != 1) {
		std::cout << "\tEnter Item ID to Edit: ";
		std::getline(std::cin, ItemID);
		if (ItemCheck(ItemID) == true) {
			check = 1;
			int option = -1;
			while (option != 0) {
				std::cout << "\t------ Edit " + ItemID + "------" << std::endl;
				std::cout << "\tSelect field to edit:" << std::endl;
				std::cout << "\t1. Item Name" << std::endl;
				std::cout << "\t2. Supplier ID" << std::endl;
				std::cout << "\t3. Item Description" << std::endl;
				std::cout << "\t4. Item Stock" << std::endl;
				std::cout << "\t0. Back to  previous menu" << std::endl;
				std::cout << "\t---------------------------" << std::endl;
				std::cin >> option;
				//edit item
				if (option == 1) {
					std::cin.ignore();
					std::cout << "\tEnter new Item Name: ";
					std::getline(std::cin, ItemName);
					std::string query = "UPDATE Items SET ItemName='" + ItemName + "' WHERE ItemID='" + ItemID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					//execute query
					sqlite3_step(res);
					sqlite3_finalize(res);
					std::cout << "\tItem Name changed" << std::endl;
				} //change supplier id 
				else if (option == 2) {
					std::cin.ignore();
					std::cout << "\tEnter Supplier ID: ";
					std::getline(std::cin, SupplierID);
					Supplier s;
					if (s.SupplierCheck(SupplierID) == true) {
						std::string query = "UPDATE Items SET SupplierID='" + SupplierID + "' WHERE ItemID='" + ItemID + "'";
						error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
						if (error != SQLITE_OK) {
							std::cout << "Couldn't prepare sql" << std::endl;
							sqlite3_close(db);
							system("pause");
						}
						//execute query
						sqlite3_step(res);
						sqlite3_finalize(res);
						std::cout << "\tSupplier ID changed" << std::endl;
					}
				} //change item description 
				else if (option == 3) {
					std::cin.ignore();
					std::cout << "\tEnter new Item Description: ";
					std::getline(std::cin, ItemDescription);
					std::string query = "UPDATE Items SET ItemDescription='" + ItemDescription + "' WHERE ItemID='" + ItemID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					//execute query
					sqlite3_step(res);
					sqlite3_finalize(res);
				} //change item stock 
				else if (option == 4) {
					std::cout << "\tEnter new Item Stock: ";
					std::cin >> ItemStock;
					std::string query = "UPDATE Items SET ItemStock='" + std::to_string(ItemStock) + "' WHERE ItemID='" + ItemID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					sqlite3_step(res);
					sqlite3_finalize(res);
					std::cout << "\tItem Stock changed" << std::endl;
				}
				else if (option == 0) {
				}
				else {
					std::cout << "\tInvalid option" << std::endl;
				}
			}

		}
		else {
			std::cout << "\tItem ID " + ItemID + " not found" << std::endl;
		}
	}
	sqlite3_close(db);
}

void Item::DeleteItm() {
	int check = 0;
	while (check != 1) {
		std::cin.ignore();
		std::cout << "\t====== Delete Item ======" << std::endl;
		std::cout << "\tEnter Item ID to Delete: ";
		std::getline(std::cin, ItemID);
		if (ItemCheck(ItemID) == true) {
			check = 1;
			int error = sqlite3_open("POMS.db", &db);
			if (error) {
				std::cout << "Couldn't open Database" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			std::string query = "DELETE FROM Items WHERE ItemID='" + ItemID + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Couldn't prepare sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			sqlite3_close(db);
			std::cout << "\tItem ID " + ItemID + " deleted" << std::endl;
		}
		else {
			std::cout << "\tItem ID " + ItemID + " not found" << std::endl;
		}
	}
}

void Item::ViewItm() {
	
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "Couldn't open db" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::string query = "select * from Items";
	error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
	if (error != SQLITE_OK) {
		std::cout << "Couldn't prepare sql" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::cout << "Item ID" << "\t" << "Item Name" << "\t" << "Supplier ID" << "\t" << "Item Description" << "\t" << "Item Stock" << std::endl;
	while (sqlite3_step(res) == SQLITE_ROW) {
		std::cout << sqlite3_column_text(res, 0) << "\t" << sqlite3_column_text(res, 1) << "\t" << sqlite3_column_text(res, 2) << "\t" << sqlite3_column_text(res, 3) << "\t" << sqlite3_column_text(res, 4) << std::endl;
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
}