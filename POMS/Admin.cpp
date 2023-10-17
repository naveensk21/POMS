#include "stdafx.h"
#include "User.h"
#include "Admin.h"
#include "Item.h"
#include "Supplier.h"
#include "PurchaseRequisition.h"
#include "GenerateOrder.h"
#include "DailyItem.h"
#include <iostream>
#include <string>

void Admin::menu() {	
	int option = -1;
	User u;	
	system("cls");
	while (option != 0) {	
		std::cout << "---------- Administrator Menu ----------" << std::endl;
		std::cout << "1. User Magmt" << std::endl;
		std::cout << "2. Item Mgmt" << std::endl;
		std::cout << "3. Supplier Mgmt" << std::endl;
		std::cout << "4. Purchase Requisition Mgmt" << std::endl;
		std::cout << "5. Purchase Order Mgmt" << std::endl;
		std::cout << "6. Daily item sales entry Mgmt" << std::endl;
		std::cout << "0. Logout" << std::endl;
		std::cout << "---------- Administrator Menu ----------" << std::endl;
		std::cout << std::endl;
		std::cout << "Select Option ->:";
		std::cin >> option;		
		if (option == 1) {
			system("cls");
			int umOption = -1;
			while (umOption != 0) {				
				std::cout << "----- User Management -----" << std::endl;
				std::cout << "1. Add Usr to the system" << std::endl;
				std::cout << "2. Edit Usr in the system" << std::endl;
				std::cout << "3. Delete Usr in the system" << std::endl;
				std::cout << "4. View  in the system" << std::endl;
				std::cout << "0. Back to previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Select Option ->:";
				std::cin >> umOption;
				if (umOption == 1) {
					u.AddUsr();
				}
				else if (umOption == 2) {
					u.EditUsr();
				}
				else if (umOption == 3) {
					u.DeleteUsr();
				}
				else if (umOption == 4) {
					u.ViewUsr();
				}
				else if (umOption == 0) {

				}
				else {
					std::cout << "Invalid Option" << std::endl;
				}
			}			
		} 
		else if (option == 2) {
			system("cls");
			int imOption = -1;
			while (imOption != 0) {				
				std::cout << "----- Item Management -----" << std::endl;
				std::cout << "1. Add Itm" << std::endl;
				std::cout << "2. Edit Itm" << std::endl;
				std::cout << "3. Delete Itm" << std::endl;
				std::cout << "4. View Itms" << std::endl;
				std::cout << "0. Back to previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Select Option ->:";
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
					std::cout << "Invalid Option" << std::endl;
				}
			}			
		}
		else if (option == 3) {
			system("cls");
			int smOption = -1;
			while (smOption != 0) {				
				std::cout << "-----Supplier Management -----" << std::endl;
				std::cout << "1. Add Spplier" << std::endl;
				std::cout << "2. Edit Spplier" << std::endl;
				std::cout << "3. Delete Spplier" << std::endl;
				std::cout << "4. View Sppliers" << std::endl;
				std::cout << "0. Back to previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Select Option ->:";
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
					std::cout << "Invalid Option" << std::endl;
				}
			}
		}
		else if (option == 4) {
			system("cls");
			int prOption = -1;
			while (prOption != 0) {				
				std::cout << "----- Purchase Requisition Management -----" << std::endl;
				std::cout << "1. Add Purchase Requisition" << std::endl;
				std::cout << "2. Edit Purchase Requisition" << std::endl;
				std::cout << "3. Delete Purchase Requisition" << std::endl;
				std::cout << "4. View Purchase Requisitions" << std::endl;
				std::cout << "0. Back to previous Menu" << std::endl;
				std::cout << std::endl;
				std::cout << "Select Option ->:";
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
					std::cout << "Invalid Option" << std::endl;
				}
			}
		}
		else if (option == 5) {
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
				std::cout << "Select Option ->:";
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
					std::cout << "Invalid Option" << std::endl;
				}
			}
		}
		else if (option == 6) {
			AddDaily();
		}
		else if (option == 0) {
			u.Logout();
		} else {
			std::cout << "Invalid Option" << std::endl;
		}
	}
}