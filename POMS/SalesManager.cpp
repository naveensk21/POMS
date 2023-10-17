#include "stdafx.h"
#include "User.h"
#include "Item.h"
#include "Supplier.h"
#include "PurchaseRequisition.h"
#include "GenerateOrder.h"
#include "DailyItem.h"
#include "SalesManager.h"
#include <iostream>
#include <string>


void SalesManager::menu() {
	int option = -1;
	Order o;
	system("cls");
	while (option != 0) {
		std::cout << "---------- Sales Manager Menu ----------" << std::endl;
		std::cout << "1. Item Mgmt" << std::endl;
		std::cout << "2. Supplier Mgmt" << std::endl;
		std::cout << "3. Purchase Requisition Mgmt" << std::endl;
		std::cout << "4. List Purchase Orders" << std::endl;
		std::cout << "5. Daily item Sales entry Mgmt" << std::endl;
		std::cout << "0. Logout" << std::endl;
		std::cout << std::endl;
		std::cout << "Input ->:";
		std::cin >> option;
		if (option == 1) {
			system("cls");
			int imOption = -1;
			while (imOption != 0) {
				std::cout << "----- Item Management -----" << std::endl;
				std::cout << "1. Add Item" << std::endl;
				std::cout << "2. Edit Item" << std::endl;
				std::cout << "3. Delete Item" << std::endl;
				std::cout << "4. View Items" << std::endl;
				std::cout << "0. Back Previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Input ->:";
				std::cin >> imOption;
				if (imOption == 1) {
					AddItm();
				}
				else if (imOption == 2) {
					EditItm();
				}
				else if (imOption == 3) {
					DeleteItm();
				}
				else if (imOption == 4) {
					ViewItm();
				}
				else if (imOption == 0) {

				}
				else {
					std::cout << "Invalid option" << std::endl;
				}
			}
		}
		else if (option == 2) {
			system("cls");
			int smOption = -1;
			while (smOption != 0) {
				std::cout << "----- Supplier Management -----" << std::endl;
				std::cout << "1. Add Supplier" << std::endl;
				std::cout << "2. Edit Supplier" << std::endl;
				std::cout << "3. Delete Supplier" << std::endl;
				std::cout << "4. View Suppliers" << std::endl;
				std::cout << "0. Back Previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Input ->:";
				std::cin >> smOption;
				if (smOption == 1) {
					AddSpplier();
				}
				else if (smOption == 2) {
					EditSpplier();
				}
				else if (smOption == 3) {
					DeleteSpplier();
				}
				else if (smOption == 4) {
					ViewSpplier();
				}
				else if (smOption == 0) {

				}
				else {
					std::cout << "Invalid option" << std::endl;
				}
			}
		}
		else if (option == 3) {
			system("cls");
			int prOption = -1;
			while (prOption != 0) {
				std::cout << "----- Purchase Requisition Management -----" << std::endl;
				std::cout << "1. Add Purchase Requisition" << std::endl;
				std::cout << "2. Edit Purchase Requisition" << std::endl;
				std::cout << "3. Delete Purchase Requisition" << std::endl;
				std::cout << "4. View Purchase Requisitions" << std::endl;
				std::cout << "0. Back Previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Input ->:";
				std::cin >> prOption;
				if (prOption == 1) {
					AddRequisition();
				}
				else if (prOption == 2) {
					EditRequisition();
				}
				else if (prOption == 3) {
					DeleteRequisition();
				}
				else if (prOption == 4) {
					ViewRequisitions();
				}
				else if (prOption == 0) {

				}
				else {
					std::cout << "Invalid option" << std::endl;
				}
			}
		}
		else if (option == 4) {
			o.ViewOdr();			
		}
		else if (option == 5) {
			AddDaily();
		}
		else if (option == 0) {
			Logout();
		}
		else {
			std::cout << "Invalid option" << std::endl;
		}
	}
}