// BMPtoASMconvertor.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Created by grayhat

#include "reader.h"
#include "ConfigHandler.h"
#include "BMPtoASMconvertor.h"

using namespace std;
int main()
{
    //std::cout << "Hello World!\n";

cout << "					    $$\\    $$\\   $$$$$$\\   $$\\                        $$\\"<<endl;
cout << "					    $$ |   \\__|  $$ __$$\\  \\__|                       $$ |" << endl;
cout << "			$$$$$$\\  $$$$$$$\\ $$$$$$\\   $$\\  $$ | $$ |  $$\\  $$\\   $$\\  $$$$$$\\   $$ |" << endl;
cout << "			\\____$$\\ $$  __$$\\\\_$$ _|   $$ | $$$$$$$ |  $$ |  \\$$\\ $$ | $$ __$$\\  $$ |" << endl;
cout << "			$$$$$$$ | $$ | $$ | $$ |    $$ | $$  ____/  $$ |  \\$$$$ /   $$$$$$$$| $$ |" << endl;
cout << "			$$ __$$ | $$ | $$ | $$ |$$\\ $$ | $$ |       $$ |  $$  $$<   $$ ____|  $$ |" << endl;
cout << "			\\$$$$$$$| $$ | $$ | \$$$$$$ |$$ | $$ |       $$ | $$ / \\$$\  \\$$$$$$$\\  $$ |" << endl;
cout << "			 \\______| \\__| \\__| \\____ / \\__| \\__|      \\__| \\__/ \\__ |  \\_______| \\__|" << endl;




cout << endl;


	cout << "Welcome to the BMP to ASM compiler." << endl;
	cout << "Enter:\n1 for TXT to ASM code conversion.\n2 for .BMP Image to .ASM conversion (16 color),\n3 for .BMP Image to .ASM conversion (Black-and-White),\n5 for Advanced Configuration,\n0 to exit." << endl;
	int option;
	cin >> option;

	switch (option) {
	case 1:
	{
		string filename;
		string saveTo;
		int Rows = 0;
		int Columns = 0;
		cout << endl;
		cout << endl;
		cout << "================= Text File to ASM File conversion ================="<<endl;

		cout << "Enter the .txt file to load (do not enter the extension): ";
		cin.ignore();
		getline(cin, filename);

		cout << "Save as (do not enter the extension): ";
		getline(cin, saveTo);
		Config UserConfig;
		loadSettings(UserConfig);

		try {
			readTXTDrawingAndOutput(filename, saveTo, Rows, Columns, UserConfig);
			cout << "Max Rows = " << Rows << endl;
			cout << "Max Columns = " << Columns << endl;

			cout << "Go check out your code in User_Results\\TextToASM\\" << saveTo << endl;
			cout << "Didn't get the results you were looking for? Try changing the configuration settings!" << endl;
		}
		catch (invalid_argument& e) {
			cout << "Error caught. " << e.what() << endl;
		}

		break;
	}

	case 2:
	{
		string filename;
		string saveTo;
		
		cout << endl;
		cout << endl;
		cout << "================= BMP Image to ASM File conversion =================" << endl;


		int Rows = 0;
		int Columns = 0;
		vector <char> myImage;

		cout << "Enter the .BMP file to load (do not enter the extension): ";
		cin.ignore();
		getline(cin, filename);

		cout << "Save as (do not enter the extension): ";
		getline(cin, saveTo);


		Config UserConfig;
		loadSettings(UserConfig);


		try {
			RGBConversion(filename, saveTo, myImage, Rows, Columns, UserConfig);
			cout << "Max Rows = " << Rows << endl;
			cout << "Max Columns = " << Columns << endl;

			cout << "Go check out your code in User_Results\\BMPColorASM\\" << saveTo << endl;
		}
		catch (invalid_argument& e) {
			cout << "Error caught. " << e.what() << endl;
		}

		break;
	}

	case 3:
	{
		string filename;
		string saveTo;

		cout << endl;
		cout << endl;
		cout << "================= BMP Image to ASM File conversion (B/W) =================" << endl;


		int Rows = 0;
		int Columns = 0;
		vector <char> myImage;
		cout << "Enter the .BMP file to load (do not enter the extension): ";
		cin.ignore();
		getline(cin, filename);

		cout << "Save as (do not enter the extension): ";
		getline(cin, saveTo);
		Config UserConfig;
		loadSettings(UserConfig);

		try {

			oneToOneConversion(filename, saveTo, myImage, Rows, Columns, UserConfig);
			cout << "Max Rows = " << Rows << endl;
			cout << "Max Columns = " << Columns << endl;

			cout << "Go check out your code in User_Results\\BMPMonoASM\\" << saveTo << endl;
		}
		catch (invalid_argument& e) {
			cout << "Error caught. " << e.what() << endl;
		}

		break;
	}

	case 5: {

		cout << " ============= ADVANCED SETTINGS ============ " << endl;
		Config UserConfig;
		loadSettings(UserConfig);

		cout << "Your current settings are:" << endl;
		cout << "1. Scan Method: " << UserConfig.SCANMETHOD << " (";
		if (!UserConfig.SCANMETHOD) cout << "Each line will have a separate address name";
		else cout << "The lines will be separated by datatype only";
		cout << ")" << endl;
		cout << "2. Rowskip: " << UserConfig.ROWSKIP << endl;
		cout << "3. Colskip: " << UserConfig.COLSKIP << endl;
		cout << "4. Header Size: " << UserConfig.HEADERSIZE << endl;
		cout << endl;
		cout << "Enter a number to change the values. Enter 9 to restore defaults. Enter 0 to exit the settings." << endl;
		int settingsOption;



		do {
			cin >> settingsOption;
			switch (settingsOption)
			{
				case 0:
				{
					exitProgram();
					break;
				}
				case 1:
				{
					cout << "Enter a number for scan method: ";
					cin >> UserConfig.SCANMETHOD;
					try {
						writeUserConfig(UserConfig);
					}
					catch (out_of_range& e) {
						cout << "Caught an error. " << e.what();
					}
					break;
				}
				case 2:
				{
					cout << "Enter a number for row skip: ";
					cin >> UserConfig.ROWSKIP;
					try {
						writeUserConfig(UserConfig);
					}
					catch (out_of_range& e) {
						cout << "Caught an error. " << e.what();
					}
					break;
				}
				case 3:
				{
					cout << "Enter a number for column skip: ";
					cin >> UserConfig.COLSKIP;
					try {
						writeUserConfig(UserConfig);
					}
					catch (out_of_range& e) {
						cout << "Caught an error. " << e.what();
					}
					break;
				}
				case 4:
				{
					cout << "Enter a number for header size (Note: by standard, most BMPs have 54 header size but in some cases it can be 62): ";
					Config defaultConfig;
					writeUserConfig(defaultConfig);
					break;
				}
				case 9:
				{
					cout << "Restoring defaults..." << endl;

					writeUserConfig(UserConfig);
					cout << "Default settings restored!";
					break;
				}



			}
		} while (settingsOption);


	}
	}
	exitProgram();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
