#pragma once

//Color Constants (16-bit)
#define Black 0
#define Red 1
#define Green 2
#define LightRed 3
#define Brown 4
#define Magenta 5
#define Cyan 6
#define LightGray 7
#define DarkGray 8
#define Blue 9
#define LightGreen 10
#define LightCyan 11
#define LightBlue 12
#define LightMagenta 13
#define Yellow 14
#define White 15

//Convert passed int machine to the respective color code
void CheckRGBValue(int& machine, int R, int G, int B) {

	if (R == 0 and G == 0 and B == 0) {
		machine = Black;
	}
	else if (R == 0 and G == 0 and B == 128) {
		machine = Blue;
	}
	else if (R == 0 and G == 128 and B == 0) {
		machine = Green;
	}
	else if (R == 0 and G == 128 and B == 128) {
		machine = Cyan;
	}
	else if (R == 128 and G == 0 and B == 0) {
		machine = Red;
	}
	else if (R == 128 and G == 0 and B == 128) {
		machine = Magenta;
	}
	else if (R == 128 and G == 128 and B == 0) {
		machine = Brown;
	}
	else if (R == 192 and G == 192 and B == 192) {
		machine = LightGray;
	}
	else if (R == 0 and G == 255 and B == 0) {
		machine = LightGreen;
	}
	else if (R == 128 and G == 128 and B == 128) {
		machine = DarkGray;
	}
	else if (R == 0 and G == 0 and B == 255) {
		machine = LightBlue;
	}
	else if (R == 0 and G == 255 and B == 255) {
		machine = LightCyan;
	}
	else if (R == 255 and G == 0 and B == 0) {
		machine = LightRed;
	}
	else if (R == 255 and G == 0 and B == 255) {
		machine = LightMagenta;
	}
	else if (R == 255 and G == 255 and B == 0) {
		machine = Yellow;
	}
	else if (R == 255 and G == 255 and B == 255) {
		machine = White;
	}
	else //if not a valid 16-bit color...
		machine = -1;

}
