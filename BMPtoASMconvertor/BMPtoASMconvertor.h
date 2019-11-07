#pragma once

#include <iostream>

void exitProgram() {
	std::cout << "Thank you for using this program!" << std::endl;
	exit(1);
}


void loadSettings(Config &UserConfig) {
	try {
		UserConfig = loadUserConfig();
	}
	catch (out_of_range& e) {
		cout << "Oops, we hit a snag! " << e.what() << endl;
		cout << "Do you wish to restore default settings? (Y / N)" << endl;
		char option;
		cin >> option;
		if (option == 'y' or option == 'Y') {
			cout << "Restoring default settings..." << endl;
			writeUserConfig(UserConfig);
		}
		else
			exitProgram();
	}
	catch (invalid_argument& e) {
		cout << "Oops, we hit a snag! " << e.what() << endl;
		cout << "Do you wish to restore default settings? (Y / N)" << endl;
		char option;
		cin >> option;
		if (option == 'y' or option == 'Y') {
			cout << "Restoring default settings..." << endl;
			writeUserConfig(UserConfig);
		}
		else
			exitProgram();
	}

}