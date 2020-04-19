#pragma once
#include "Config.h"
#include <fstream>
#include <string>
using namespace std;


Config loadUserConfig() {
		ifstream ifs;
		string line = "";
		ifs.open("config.CONFIG", ifstream::in);
		if (!ios::failbit) {
			ifs.close();
			throw invalid_argument ("ERROR: Loading failed.");
		}
		if (ifs.eof()) {
			ifs.close();
			throw invalid_argument ("ERROR: File is empty.");
			//return false;
		}
		if (!ifs.good()) {
			ifs.close();
			throw invalid_argument ("ERROR: File couldn't be found. Either it was deleted, or has access issues.");
			//return false;
		}
		Config userConfig;
		getline(ifs, line, '\n');
		userConfig.SCANMETHOD = stoi(line);
		line = "";

		getline(ifs, line, '\n');
		userConfig.ROWSKIP = stoi(line);
		line = "";

		getline(ifs, line, '\n');
		userConfig.COLSKIP = stoi(line);
		line = "";

		getline(ifs, line, '\n');
		userConfig.HEADERSIZE = stoi(line);
		line = "";

		ifs.close();
		return userConfig;
}

Config writeUserConfig(Config newConfig) {
	ofstream ofs("config.CONFIG");
	
	ofs << newConfig.SCANMETHOD << endl;
	ofs << newConfig.ROWSKIP << endl;
	ofs << newConfig.COLSKIP << endl;
	ofs << newConfig.HEADERSIZE << endl;

	ofs.close();
	return newConfig;
}