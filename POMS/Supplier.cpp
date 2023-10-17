#include "stdafx.h"
#include "Supplier.h"
#include "Item.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

bool Supplier::SupplierCheck(std::string sID) {

	int error = sqlite3_open("POMS.db", &db1);
	if (error) {
		std::cout << "Couldn't open db" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}
	std::string query = "select * from Suppliers";
	error = sqlite3_prepare_v2(db1, query.c_str(), query.length(), &res1, &tail1);
	if (error != SQLITE_OK) {
		std::cout << "Couldn't prepare sql" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}

	while (sqlite3_step(res1) == SQLITE_ROW) {
		if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res1, 0))) == sID) {
			sqlite3_finalize(res1);
			sqlite3_close(db1);
			return true;
		}
	}
	sqlite3_finalize(res1);
	sqlite3_close(db1);
	return false;
}

void Supplier::AddSpplier() {
	int check = 0;
	while (check != 1) {
		//receive input from user
		std::cin.ignore();
		std::cout << "\t====== Add Supplier ======" << std::endl;
		std::cout << "\tEnter Supplier ID: ";
		std::getline(std::cin, SupplierID);
		//check if supplier already exists
		if (SupplierCheck(SupplierID) == true) {
			std::cout << "\tSupplier " + SupplierID + " already exist" << std::endl;
		} //if not continue
		else {
			check = 1;
			std::cout << "\tEnter Supplier Name: ";
			std::getline(std::cin, SupplierName);

			std::cout << "\tEnter Supplier Contact: ";
			std::getline(std::cin, SupplierContact);

			std::cout << "\tEnter Supplier Email: ";
			std::getline(std::cin, SupplierEmail);

			std::cout << "\tEnter Supplier Account: ";
			std::getline(std::cin, SupplierAccount);

			std::cout << "\tEnter Supplier Address: ";
			std::getline(std::cin, SupplierAddress);
			//connect to database and save data	
			int error = sqlite3_open("POMS.db", &db);
			if (error) {
				std::cout << "Couldn't open Database" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			std::string query = "INSERT INTO Suppliers VALUES('" + SupplierID + "','" + SupplierName + "','" + SupplierContact + "','" + SupplierEmail + "','" + SupplierAccount + "','" + SupplierAddress + "')";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Couldn't prepare sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			sqlite3_close(db);
		}
	}
}

void Supplier::EditSpplier() {
	//open database
	std::cout << "\t====== Edit Supplier ======" << std::endl;
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "Couldn't open Database" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	//get supplier id to work with
	int check = 0;
	while (check != 1) {
		std::cout << "\tEnter Item ID to Edit: ";
		std::getline(std::cin, SupplierID);
		//check if supplier id exists to be able to edit
		if (SupplierCheck(SupplierID) == true) {
			check = 1;
			int option = -1;
			while (option != 0) {
				std::cout << "\t-------- Edit " + SupplierID + "--------" << std::endl;
				std::cout << "\tSelect field to edit:" << std::endl;
				std::cout << "\t1. Supplier Name" << std::endl;
				std::cout << "\t2. Supplier Contact" << std::endl;
				std::cout << "\t3. Supplier Email" << std::endl;
				std::cout << "\t4. Supplier Account" << std::endl;
				std::cout << "\t5. Supplier Address" << std::endl;
				std::cout << "\t0. Back to  previous menu" << std::endl;
				std::cout << "\t---------------------------" << std::endl;
				std::cin >> option;
				//edit supplier name
				if (option == 1) {
					std::cin.ignore();
					std::cout << "\tEnter new Supplier Name: ";
					std::getline(std::cin, SupplierName);
					std::string query = "UPDATE Suppliers SET SupplierName='" + SupplierName + "' WHERE SupplierID='" + SupplierID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					//execute query
					sqlite3_step(res);
					//destruct query
					sqlite3_finalize(res);
					std::cout << "\tSupplier Name changed" << std::endl;
				} //edit supplier contact 
				else if (option == 2) {
					std::cin.ignore();
					std::cout << "\tEnter new Supplier Contact: ";
					std::getline(std::cin, SupplierContact);
					std::string query = "UPDATE Suppliers SET SupplierContact='" + SupplierContact + "' WHERE SupplierID='" + SupplierID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					//execute query
					sqlite3_step(res);
					//destruct query
					sqlite3_finalize(res);
					std::cout << "\tSupplier Contact changed" << std::endl;
				}  //edit supplier email 
				else if (option == 3) {
					std::cin.ignore();
					std::cout << "\tEnter new Supplier Contact: ";
					std::getline(std::cin, SupplierEmail);
					std::string query = "UPDATE Suppliers SET SupplierEmail='" + SupplierEmail + "' WHERE SupplierID='" + SupplierID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					//execute query
					sqlite3_step(res);
					//destruct query
					sqlite3_finalize(res);
					std::cout << "\tSupplier Contact changed" << std::endl;
				} // edit supplier email
				else if (option == 4) {
					std::cin.ignore();
					std::cout << "\tEnter new Supplier Account: ";
					std::getline(std::cin, SupplierAccount);
					std::string query = "UPDATE Suppliers SET SupplierAccount='" + SupplierAccount + "' WHERE SupplierID='" + SupplierID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					//execute query
					sqlite3_step(res);
					//destruct query
					sqlite3_finalize(res);
					std::cout << "\tSupplier Account changed" << std::endl;
				} // edit supplier email
				else if (option == 5) {
					std::cin.ignore();
					std::cout << "\tEnter new Supplier Address: ";
					std::getline(std::cin, SupplierAccount);
					std::string query = "UPDATE Suppliers SET SupplierAddress='" + SupplierAddress + "' WHERE SupplierID='" + SupplierID + "'";
					error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
					if (error != SQLITE_OK) {
						std::cout << "Couldn't prepare sql" << std::endl;
						sqlite3_close(db);
						system("pause");
					}
					//execute query
					sqlite3_step(res);
					//destruct query
					sqlite3_finalize(res);
					std::cout << "\tSupplier Address changed" << std::endl;
				}
				else if (option == 0) {
					//while look will break automatically
				}
				else {
					std::cout << "\tWrong option" << std::endl;
				}
			}
		}
		else {
			std::cout << "\tSupplier ID " + SupplierID + " not found" << std::endl;
		}
	}
	sqlite3_close(db);
}

void Supplier::DeleteSpplier() {
	int check = 0;
	while (check != 1) {
		std::cin.ignore();
		std::cout << "\t====== Delete Supplier ======" << std::endl;
		std::cout << "\tEnter Supplier ID to Delete: ";
		std::getline(std::cin, SupplierID);
		if (SupplierCheck(SupplierID) == true) {
			check = 1;
			int error = sqlite3_open("POMS.db", &db);
			if (error) {
				std::cout << "Couldn't open Database" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			std::string query = "DELETE FROM Suppliers WHERE SupplierID='" + SupplierID + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Couldn't prepare sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			query = "Select ItemID FROM Items WHERE SupplierID='" + SupplierID + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Couldn't prepare sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			std::cout << "\tItems deleted with " + SupplierID << std::endl;
			while (sqlite3_step(res) == SQLITE_ROW) {
				std::cout << "\t" << sqlite3_column_text(res, 0) << std::endl;
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			query = "DELETE FROM Items WHERE SupplierID='" + SupplierID + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Couldn't prepare sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			sqlite3_close(db);
			std::cout << "\tSupplier ID " + SupplierID + " deleted" << std::endl;
		}
		else {
			std::cout << "\tSupplier ID " + SupplierID + " not found" << std::endl;
		}
	}
}

void Supplier::ViewSpplier() {
	std::cout << "\t====== View Suppliers ======" << std::endl;
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "Couldn't open db" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::string query = "select * from Suppliers";
	error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
	if (error != SQLITE_OK) {
		std::cout << "Couldn't prepare sql" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::cout << "Supplier ID" << "\t" << "Supplier Name" << "\t" << "Supplier Contact" << "\t" << "Supplier Email" << "\t" << "Supplier Account" << "\t" << "Supplier Address" << std::endl;
	while (sqlite3_step(res) == SQLITE_ROW) {
		std::cout << sqlite3_column_text(res, 0) << "\t" << sqlite3_column_text(res, 1) << "\t" << sqlite3_column_text(res, 2) << "\t" << sqlite3_column_text(res, 3) << "\t" << sqlite3_column_text(res, 4) << "\t" << sqlite3_column_text(res, 5) << std::endl;
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
}