#pragma once
#include <iostream>
using namespace std;
class Config {
public:
	int SCANMETHOD;
	int ROWSKIP;
	int COLSKIP;
	int HEADERSIZE;


	//default values in case the user wants to restore
	Config() : SCANMETHOD(1), ROWSKIP(2), COLSKIP(4), HEADERSIZE(54) {

	}

	//parameterized constructor if ever needed
	Config(int sm, int rs, int cs, int hs) {
		if ((sm < 0 or sm>3) or rs <= 0 or cs <= 0) {
			throw out_of_range ("A value you have defined is out of range!");
		}
		SCANMETHOD = sm;
		ROWSKIP = rs;
		COLSKIP = cs;
		HEADERSIZE = hs;
	}

	//enables copying of loaded Config to current Config and vice versa
	Config(const Config &toCopy) {
		if ((toCopy.SCANMETHOD < 0 or toCopy.SCANMETHOD>3) or toCopy.ROWSKIP <= 0 or toCopy.COLSKIP <= 0) {
			throw out_of_range ("A value during the copy is out of range!");
		}
		this->COLSKIP = toCopy.COLSKIP;
		this->HEADERSIZE = toCopy.HEADERSIZE;
		this->ROWSKIP = toCopy.ROWSKIP;
		this->SCANMETHOD = toCopy.SCANMETHOD;
	}
};