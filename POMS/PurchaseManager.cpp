#include "stdafx.h"
#include "User.h"
#include "Item.h"
#include "Supplier.h"
#include "PurchaseRequisition.h"
#include "GenerateOrder.h"
#include "PurchaseManager.h"
#include <iostream>
#include <string>


void PurchaseManager::menu() {
	int option = -1;
	Item i;
	Supplier s;
	Requisition r;
	system("cls");
	while (option != 0) {		
		std::cout << "====== Purchase Manager Menu ======" << std::endl;
		std::cout << "1. List of Items" << std::endl;
		std::cout << "2. List of Suppliers" << std::endl;
		std::cout << "3. List of Purchase Requisitions" << std::endl;
		std::cout << "4. Purchase Ordr Management" << std::endl;
		std::cout << "0. Logout" << std::endl;
		std::cout << std::endl;
		std::cout << "Input ->:";
		std::cin >> option;
		if (option == 1) {
			i.ViewItm();
		}
		else if (option == 2) {
			s.ViewSpplier();
		}
		else if (option == 3) {
			r.ViewRequisitions();
		}
		else if (option == 4) {
			system("cls");
			int poOption = -1;
			while (poOption != 0) {
				std::cout << "----- Purchase Order Management -----" << std::endl;
				std::cout << "1. Add Purchase Ordr" << std::endl;
				std::cout << "2. Edit Purchase Ordr" << std::endl;
				std::cout << "3. Delete Purchase Ordr" << std::endl;
				std::cout << "4. View Purchase Ordr" << std::endl;
				std::cout << "0. Previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Input ->:";
				std::cin >> poOption;
				if (poOption == 1) {
					AddOdr();
				}
				else if (poOption == 2) {
					EditOdr();
				}
				else if (poOption == 3) {
					RemoveOdr();
				}
				else if (poOption == 4) {
					ViewOdr();
				}
				else if (poOption == 0) {

				}
				else {
					std::cout << "Invalid option" << std::endl;
				}
			}
		}
		else if (option == 0) {
			Logout();
		}
		else {
			std::cout << "Invalid option" << std::endl;
		}
	}
}