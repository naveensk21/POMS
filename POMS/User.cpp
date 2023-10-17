#include "stdafx.h"
#include "User.h"
#include "Admin.h"
#include "SalesManager.h"
#include "PurchaseManager.h"
#include <iostream>
#include <string>
#include "sqlite3.h"

bool User::UsrCheck(std::string uName) {
	int error = sqlite3_open("POMS.db", &db1);
	if (error) {
		std::cout << "Couldn't open db" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}
	std::string query = "select * from Users";
	error = sqlite3_prepare_v2(db1, query.c_str(), query.length(), &res1, &tail1);
	if (error != SQLITE_OK) {
		std::cout << "Couldn't prepare sql" << std::endl;
		sqlite3_close(db1);
		system("pause");
		return 0;
	}

	while (sqlite3_step(res1) == SQLITE_ROW) {
		if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res1, 0))) == uName) {
			sqlite3_finalize(res1);
			sqlite3_close(db1);
			return true;
		}
	}
	sqlite3_finalize(res1);
	sqlite3_close(db1);
	return false;
}

void User::menu() {}

void User::AddUsr() {
	int check = 0;
	std::cin.ignore();
	while (check != 1) {
		//receive input from user
		
		std::cout << "\t====== Add User ======" << std::endl;
		std::cout << "\tEnter Username: ";
		std::getline(std::cin, Username);
		if (UsrCheck(Username) == true) {
			std::cout << "\tUsername " + Username + " already exist" << std::endl;
		}
		else {
			std::cout << "\tEnter Password: ";
			std::getline(std::cin, Password);

			std::cout << "\tEnter Name: ";
			std::getline(std::cin, Name);
			int type = -1;
			Usertype = "";
			std::cout << "\tSelect Usertype:" << std::endl;
			std::cout << "\t1. Administrator" << std::endl;
			std::cout << "\t2. Sales Manager" << std::endl;
			std::cout << "\t3. Purchase Manager" << std::endl;
			std::cout << "\tInput ->:";
			std::cin >> type;
			if (type == 1) {
				Usertype = "Administrator";
			}
			else if (type == 2) {
				Usertype = "Sales Manager";
			}
			else if (type == 3) {
				Usertype = "Purchase Manager";
			}
			else {
				std::cout << "\tWrong option" << std::endl;
			}
			if (Usertype != "") {
				//connect to database and save data	
				int error = sqlite3_open("POMS.db", &db);
				if (error) {
					std::cout << "Couldn't open Database" << std::endl;
					sqlite3_close(db);
					system("pause");
				}
				std::string query = "INSERT INTO Users VALUES('" + Username + "','" + Password + "','" + Name + "','" + Usertype + "')";
				error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
				if (error != SQLITE_OK) {
					std::cout << "Couldn't prepare sql" << std::endl;
					sqlite3_close(db);
					system("pause");
				}
				sqlite3_step(res);
				sqlite3_finalize(res);
				sqlite3_close(db);
				std::cout << "\tUsername " + Username + " added" << std::endl;
				check = 1;
			}
			else {
				std::cout << "\tUser wasn't added. Try again." << std::endl;
			}
		}
	}
	
}

void User::EditUsr() {
	//open database
	std::cout << "\t----- Edit User -----" << std::endl;
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "Couldn't open Database" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	int check = 0;
	while (check != 1) {
		//get username to work with
		std::cin.ignore();
		std::cout << "\tEnter Username to Edit: ";
		std::getline(std::cin, Username);
		//check if supplier id exists to be able to edit
		if (UsrCheck(Username) == true) {
			check = 1;
			int option = -1;
			while (option != 0) {
				std::cout << "\t------ Edit " + Username + "-----" << std::endl;
				std::cout << "\tSelect field to edit:" << std::endl;
				std::cout << "\t1. Password" << std::endl;
				std::cout << "\t2. Name" << std::endl;
				std::cout << "\t3. Usertype" << std::endl;
				std::cout << "\t0. Back to  previous menu" << std::endl;
				std::cout << "\t------------------------------" << std::endl;
				std::cout << "\tInput ->:";
				std::cin >> option;
				//edit supplier name
				if (option == 1) {
					std::cin.ignore();
					std::cout << "\tEnter new Password: ";
					std::getline(std::cin, Password);
					std::string query = "UPDATE Users SET Password='" + Password + "' WHERE Username='" + Username + "'";
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
					std::cout << "\tPassword changed" << std::endl;
				} //edit supplier contact 
				else if (option == 2) {
					std::cin.ignore();
					std::cout << "\tEnter new Name: ";
					std::getline(std::cin, Name);
					std::string query = "UPDATE Users SET Name='" + Name + "' WHERE Username='" + Username + "'";
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
					std::cout << "Name changed" << std::endl;
				}  //edit supplier email 
				else if (option == 3) {
					int type = -1;
					Usertype = "";
					std::cout << "\tSelect new Usertype: " << std::endl;
					std::cout << "\t1. Administrator" << std::endl;
					std::cout << "\t2. Sales Manager" << std::endl;
					std::cout << "\t3. Purchase Manager" << std::endl;
					std::cout << "\tInput ->:";
					std::cin >> type;
					if (type == 1) {
						Usertype = "Administrator";
					}
					else if (type == 2) {
						Usertype = "Sales Manager";
					}
					else if (type == 3) {
						Usertype = "Purchase Manager";
					}
					else {
						std::cout << "\tWrong option" << std::endl;
					}
					if (Usertype != "") {
						std::string query = "UPDATE Users SET Usertype='" + Usertype + "' WHERE Username='" + Username + "'";
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
						std::cout << "\tUsertype changed" << std::endl;
					}
				} // edit supplier email
				else if (option == 0) {
					//while look will break automatically
				}
				else {
					std::cout << "\tWrong option" << std::endl;
				}
			}
		}
		else {
			std::cout << "\tUsername " + Username + " not found" << std::endl;
		}
	}
	sqlite3_close(db);
}

void User::DeleteUsr() {
	std::cin.ignore();
	std::cout << "\t----- Delete User -----" << std::endl;
	std::cout << "\tEnter Username to Delete: ";
	std::getline(std::cin, Username);
	if (Username == "Admin") {
		std::cout << "\tThis user cannot be deleted" << std::endl;
	}
	else {
		if (UsrCheck(Username) == true) {
			int error = sqlite3_open("POMS.db", &db);
			if (error) {
				std::cout << "Couldn't open Database" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			std::string query = "DELETE FROM Users WHERE Username='" + Username + "'";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Couldn't prepare sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			sqlite3_step(res);
			sqlite3_finalize(res);
			sqlite3_close(db);
			std::cout << "\tUsername " + Username + " deleted" << std::endl;
		}
		else {
			std::cout << "\tUsername " + Username + " not found" << std::endl;
		}
	}	
}

void User::ViewUsr() {
	std::cout << "\t----- View Users -----" << std::endl;
	int error = sqlite3_open("POMS.db", &db);
	if (error) {
		std::cout << "Couldn't open db" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::string query = "select * from Users";
	error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
	if (error != SQLITE_OK) {
		std::cout << "Couldn't prepare sql" << std::endl;
		sqlite3_close(db);
		system("pause");
	}
	std::cout << "Username" << "\t" << "Password" << "\t" << "Name" << "\t\t" << "Usertype" << std::endl;
	while (sqlite3_step(res) == SQLITE_ROW) {		
		std::cout << sqlite3_column_text(res, 0) << "\t\t" << sqlite3_column_text(res, 1) << "\t\t" << sqlite3_column_text(res, 2) << "\t\t" << sqlite3_column_text(res, 3) << std::endl;
	}
	sqlite3_finalize(res);
	sqlite3_close(db);
}

void User::Login() {
	std::cout << "----- Login -----" << std::endl;
	int loggedIn = -1;
	while (loggedIn != 1) {		
		std::cout << "Enter Username: ";
		std::getline(std::cin, Username);
		if (UsrCheck(Username) == true) {
			std::cout << "Enter Password: ";
			std::getline(std::cin, Password);
			int error = sqlite3_open("POMS.db", &db);
			if (error) {
				std::cout << "Couldn't open db" << std::endl;
				sqlite3_close(db);
				system("pause");
			}
			std::string query = "select * from Users";
			error = sqlite3_prepare_v2(db, query.c_str(), query.length(), &res, &tail);
			if (error != SQLITE_OK) {
				std::cout << "Couldn't prepare sql" << std::endl;
				sqlite3_close(db);
				system("pause");
			}

			while (sqlite3_step(res) == SQLITE_ROW) {
				if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 0))) == Username && std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 1))) == Password) {
					if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3))) == "Administrator") {
						Usertype = "Administrator";
						Name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
					}
					else if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3))) == "Sales Manager") {
						Usertype = "Sales Manager";
						Name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
					}
					else if (std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 3))) == "Purchase Manager") {
						Usertype = "Purchase Manager";
						Name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(res, 2)));
					}
				}
			}
			sqlite3_finalize(res);
			sqlite3_close(db);
			if (Usertype == "Administrator") {
				loggedIn = 1;
				Admin a;				
				a.menu();				
			}
			else if (Usertype == "Sales Manager") {
				loggedIn = 1;
				SalesManager s;
				s.menu();
			}
			else if (Usertype == "Purchase Manager") {
				loggedIn = 1;
				PurchaseManager p;
				p.menu();
			}
		}
		else {
			std::cout << "User not found" << std::endl;
		}
	}		
}

std::string User::getName() {
	return Name;
}

void User::Logout() {
	system("cls");
	std::cin.ignore();
	Login();
}