#pragma once
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <iterator>
#include "Config.h"
#include "Color.h"
using namespace std;

std::vector<char> readBMP(const std::string& file, int& Rows, int& Columns)
{
	static constexpr size_t HEADER_SIZE = 54;

	std::ifstream bmp(file + ".BMP", std::ios::binary);
	if (!bmp.good()) {
		throw invalid_argument("File couldn't be found. Either it was deleted, or has access issues. Make sure you check the extension!");
	}
	else if (bmp.eof())
		throw invalid_argument("File is empty!");

	std::array<char, HEADER_SIZE> header;
	bmp.read(header.data(), header.size());

	auto fileSize = *reinterpret_cast<uint32_t*>(&header[2]);
	auto dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);
	auto width = *reinterpret_cast<uint32_t*>(&header[18]);
	auto height = *reinterpret_cast<uint32_t*>(&header[22]);
	auto depth = *reinterpret_cast<uint16_t*>(&header[28]);

	std::cout << "fileSize: " << fileSize << std::endl;
	std::cout << "dataOffset: " << dataOffset << std::endl;
	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;
	std::cout << "depth: " << depth << "-bit" << std::endl;



	Rows = height;
	Columns = width;

	std::vector<char> img(0);
	//cout << "Img data is " << img.data() << endl;
	cout << "Img size is " << img.size() << endl;
	bmp.read(img.data(), img.size());
	auto row_padded = ((width * 3 + 3) & (~3));
	auto dataSize = width * height * 3;
	cout << "(width * 3 + 3) = " << (width * 3 + 3) << endl;
	cout << "((width * 3 + 3) & (~3)) = " << ((width * 3 + 3) & (~3)) << endl;
	cout << "DataSize is "<<dataSize << endl;
	img.resize(dataSize);

	char tmp = 0;
	vector<char>result(dataSize);

	if (depth == 24) {
		cout << "Detected a 24-bit BMP file." << endl;
		int k = 0;
		for (int i = 0; i < height; i++)
		{
			bmp.read(img.data(), row_padded);
			for (int j = 0; j < width * 3; j += 3)
			{
				// Convert (B, G, R) to (R, G, B)
				tmp = img[j];
				img[j] = img[j + 2];
				img[j + 2] = tmp;

				cout << "R: " << (unsigned char)img[j] << " G: " << (unsigned char)img[j + 1] << " B: " << (unsigned char)img[j + 2] << endl;

				// Save pixel data of img row into a row of result
				result[k] = img[j];
				result[k + 1] = img[j + 1];
				result[k + 2] = img[j + 2];
				k += 3;
			}

		}

	}
	else if (depth == 4) {
		throw invalid_argument("Cannot read 16-color (4-bit) BMP files as of yet. Save your image as 24-bit BMP in \nMSPaint, or try checking the latest build of antiPixel on GitHub.");
	}


	//Display img to check 
	for (int i = 0; i < result.size(); i+=3) {
		if ((int)result[i] == -1) {
			cout << " ";
		}
		else
			cout << 1;
		if (i % 72 == 0) {
			cout << endl;
		}
	}

	cout << "Done iterating! The image size is " << img.size() << endl;



	return result;
}



void readTXTDrawingAndOutput(string filename, string saveHere, int& Rows, int& Columns, Config& UserConfig) {
	ifstream ifs(filename + ".txt");
	if (!ifs.good())
		throw invalid_argument("File couldn't be found. Either it was deleted, or has access issues.");
	else if (ifs.eof())
		throw invalid_argument("File is empty!");

	ofstream ofs("User_Results\\TextToASM\\" + saveHere + ".asm");
	if (!ofs.good())
		throw invalid_argument("Can't save the file! Check if the 'User_Results' folder is created in the program folder. If not, make it!");
	char c;

	ofs << ".model small" << endl;
	ofs << ".stack" << endl;
	ofs << ".data" << endl;
	ofs << endl;
	ofs << "; ============================================================" << endl;
	if (UserConfig.SCANMETHOD == 0)
		ofs << "; each array represents one row of the image" << endl;
	if (UserConfig.SCANMETHOD == 1)
		ofs << "; each line contains a row of pixels" << endl;

	int machine;
	int i = 0;
	int j = 0;
	int maxCol = 0;
	string content = "";
	cout << "Your file is... " << endl;
	while (!ifs.eof()) {
		c = ifs.get();
		cout << c;


		//FortyFix for older assemblers
		if (maxCol % (39) == 0 and maxCol != 0) {

			if (UserConfig.SCANMETHOD == 1)
				content.erase(content.end() - 2);

			content += "\n\t\t\t\t db ";
			maxCol = 0;
		}


		if (c == '\n') {
			if (maxCol > Columns)
				Columns = maxCol;
			if (content != "" && j % UserConfig.ROWSKIP == 1) {
				content.erase(content.end() - 2);
				if (UserConfig.SCANMETHOD == 0) {
					ofs << "myimagearray" << to_string(Rows) << " db ";
				}
				else if (UserConfig.SCANMETHOD == 1) {
					if (Rows == 0) {
						ofs << "myimagearray" << to_string(Rows) << "       ";
					}
					else
						ofs << "\t\t\t\t\t";
					ofs << " db ";
				}
				ofs << content;
				ofs << endl;
				ofs << endl;
				Rows++;
			}
			content = "";
			j++;
			i = 0;
			maxCol = 0;
		}
		else if (i % UserConfig.COLSKIP == 0) {
			maxCol++;
			if (c == ' ') {
				machine = 0;
			}
			else {
				machine = 1;
			}
			content += to_string(machine);
			content += ", ";
			if (UserConfig.SCANMETHOD == 0) {
				if (i % 24 == 0) {
					content += "\n				";
				}
			}
		}
		i++;
	}
	ofs << "; ============================================================" << endl;
	ofs.close();
	ifs.close();

}





void RGBConversion(string& readFrom, string filename, vector <char>& img, int &Rows, int& Columns, Config &UserConfig) {

	img = readBMP(readFrom, Rows, Columns);

	reverse(img.begin(), img.end());

	ofstream ofs("User_Results\\BMPColorASM\\" + filename + ".asm");


	string content = "";
	int getRows = 0;
	int getColumns = 0;

	for (int i = 0; i < img.size(); i++) {

		if (i % 3 == 0) {
			int machine;
			
			CheckRGBValue(machine, (unsigned char)img[i], (unsigned char)img[i+1], (unsigned char)img[i+2]);
			
			content += to_string(machine);
			content += ", ";
			if (UserConfig.SCANMETHOD == 0) {
				if (i % ((Columns / 5) * 3) == 0 and i != 0) {
					content += "\n				";
				}
			}
			getColumns++;

		}

		//due to limit of MASM 8086, an array can't be declared with more than 40 elements
		if (getColumns % (39) == 0 and getColumns != 0) {

			if (UserConfig.SCANMETHOD == 1)
				content.erase(content.end() - 2);

			content += "\n\t\t\t\t db ";
			getColumns = 0;
		}

		if (i % ((Columns - 1) * 3) == 0 and i != 0) {

			content.erase(content.end() - 2);
			if (UserConfig.SCANMETHOD == 0) {
				ofs << "myimagearray" << to_string(getRows);
				ofs << " db ";
			}
			else if (UserConfig.SCANMETHOD == 1) {
				if (getRows == 0) {
					ofs << "myimagearray" << to_string(getRows) << "       ";
				}
				else
					ofs << "\t\t\t\t\t";
				ofs << " db ";
			}
			ofs << content;
			ofs << endl;

			getRows++;
			getColumns = 0;
			content = "";
		}

	}
	ofs.close();
}
















void oneToOneConversion(string &readFrom, string filename, vector <char> &img, int &Rows, int &Columns, Config &UserConfig) {

	img = readBMP(readFrom, Rows, Columns);

	reverse(img.begin(), img.end());

	ofstream ofs("User_Results\\BMPMonoASM\\" + filename + ".asm"	);


	string content = "";
	int getRows = 0;
	int getColumns = 0;

	for (int i = 0; i < img.size(); i++) {

		if (i % 3 == 0 and i!=0) {
			int machine;
			if ((int)img[i] == -1 and (int)img[i-1] == -1 and (int)img[i-2] == -1) {
				machine = 0;
			}
			else
				machine = 1;
			//machine = (int)img[i] + 1;
			content += to_string(machine);
			content += ", ";
			if (UserConfig.SCANMETHOD == 0){
				if (i % ((Columns / 5) * 3) == 0 and i != 0) {
					content += "\n				";
				}
			}
			getColumns++;
			
		}

		//due to limit of MASM 8086, an array can't be declared with more than 40 elements
		if (getColumns % (39) == 0 and getColumns!=0) {
		
			if (UserConfig.SCANMETHOD==1)
				content.erase(content.end() - 2);

			content += "\n\t\t\t\t db ";
			getColumns = 0;
		}

		if (i % ((Columns-1)*3) == 0 and i!=0) {

			content.erase(content.end() - 2);
			if (UserConfig.SCANMETHOD == 0) {
				ofs << "myimagearray" << to_string(getRows);
				ofs << " db ";
		}
		else if (UserConfig.SCANMETHOD == 1) {
				if (getRows == 0) {
					ofs << "myimagearray" << to_string(getRows)<<"       ";
				}
				else
					ofs << "\t\t\t\t\t";
				ofs << " db ";
			}
			ofs << content;
			ofs << endl;

			getRows++;
			getColumns = 0;
			content = "";
		}

	}
	ofs.close();
}





// =====================================    THIS CODE DID NOT WORK   =============================================//


//std::vector<char> readBMP(const std::string& file)
//{
//	static constexpr size_t HEADER_SIZE = 54;
//
//	std::ifstream bmp(file + ".BMP", std::ios::binary);
//	if (!bmp.good()) {
//		throw invalid_argument("File couldn't be found. Either it was deleted, or has access issues. Make sure you check the extension!");
//	}
//	else if (bmp.eof())
//		throw invalid_argument("File is empty!");
//
//	std::array<char, HEADER_SIZE> header;
//	bmp.read(header.data(), header.size());
//
//	auto fileSize = *reinterpret_cast<uint32_t*>(&header[2]);
//	auto dataOffset = *reinterpret_cast<uint32_t*>(&header[10]);
//	auto width = *reinterpret_cast<uint32_t*>(&header[18]);
//	auto height = *reinterpret_cast<uint32_t*>(&header[22]);
//	auto depth = *reinterpret_cast<uint16_t*>(&header[28]);
//
//	std::cout << "fileSize: " << fileSize << std::endl;
//	std::cout << "dataOffset: " << dataOffset << std::endl;
//	std::cout << "width: " << width << std::endl;
//	std::cout << "height: " << height << std::endl;
//	std::cout << "depth: " << depth << "-bit" << std::endl;
//
//
//	std::vector<char> img(HEADER_SIZE - dataOffset);
//	//cout << "Img data is " << img.data() << endl;
//	cout << "Img size is " << img.size() << endl;
//	bmp.read(img.data(), img.size());
//	cout << "Bitwise negation of 3... " << (~3) << endl;
//	auto row_padded = ((width * 3 + 3) & (~3));
//	auto dataSize = row_padded * height;
//	cout << "(width * 3 + 3) = " << (width * 3 + 3) << endl;
//	cout << "((width * 3 + 3) & (~3)) = " << ((width * 3 + 3) & (~3)) << endl;
//	cout << "DataSize is "<<dataSize << endl;
//	img.resize(dataSize);
//	bmp.read(img.data(), img.size());
//
//	char temp = 0;
//
//
//
//
//	for (auto i = dataSize - 4; i > 0; i -= 3)
//	{
//		temp = img[i];
//		img[i] = img[i + 2];
//		img[i + 2] = temp;
//
//		std::cout << "R: " << int(img[i] & 0xff) << " G: " << int(img[i + 1] & 0xff) << " B: " << int(img[i + 2] & 0xff) << std::endl;
//		cout << "Iteration..." << i << endl;
//	}
//
//	//Display img to check 
//	//for (int i = 0; i < img.size(); i++) {
//	//	cout << img[i] << " ";
//	//	if (i % 24 == 0) {
//	//		cout << endl;
//	//	}
//	//}
//
//	cout << "Done iterating! The image size is " << img.size() << endl;
//
//
//
//	return img;
//}

//unsigned char* ReadBMP(char* filename)
//{
//	int i;
//	FILE** f = 0;
//	std::ifstream bmp(filename, std::ios::binary);
//
//	if (!bmp.good())
//		throw invalid_argument("file not found");
//
//	//if (f == NULL)
//	//	throw invalid_argument ("Argument Exception");
//
//	unsigned char info[54];
//	bmp.read(0, 54); // read the 54-byte header
//
//	// extract image height and width from header
//	int width = *(int*)& info[18];
//	int height = *(int*)& info[22];
//
//	cout << endl;
//	cout << "  Name: " << filename << endl;
//	cout << " Width: " << width << endl;
//	cout << "Height: " << height << endl;
//
//	int row_padded = (width * 3 + 3) & (~3);
//	unsigned char* data = new unsigned char[row_padded];
//	unsigned char tmp;
//
//	for (int i = 0; i < height; i++)
//	{
//		fread(data, sizeof(unsigned char), row_padded, *f);
//		for (int j = 0; j < width * 3; j += 3)
//		{
//			// Convert (B, G, R) to (R, G, B)
//			tmp = data[j];
//			data[j] = data[j + 2];
//			data[j + 2] = tmp;
//
//			cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
//		}
//	}
//
//	fclose(*f);
//	return data;
//}



//unsigned char* ReadBMPFrankenstein(char* filename)
//{
//	int i;
//	FILE** f = 0;
//	errno_t e;
//	e = fopen_s(f, filename, "rb");
//
//	if (e != 0) {
//		f = 0;
//	}
//
//	//if (f == NULL)
//	//	throw invalid_argument ("Argument Exception");
//
//	unsigned char info[54];
//	fread(info, sizeof(unsigned char), 54, *f); // read the 54-byte header
//
//	// extract image height and width from header
//	int width = *(int*)& info[18];
//	int height = *(int*)& info[22];
//
//	cout << endl;
//	cout << "  Name: " << filename << endl;
//	cout << " Width: " << width << endl;
//	cout << "Height: " << height << endl;
//
//	int row_padded = (width * 3 + 3) & (~3);
//	unsigned char* data = new unsigned char[row_padded];
//	unsigned char tmp;
//
//	for (int i = 0; i < height; i++)
//	{
//		fread(data, sizeof(unsigned char), row_padded, *f);
//		for (int j = 0; j < width * 3; j += 3)
//		{
//			// Convert (B, G, R) to (R, G, B)
//			tmp = data[j];
//			data[j] = data[j + 2];
//			data[j + 2] = tmp;
//
//			cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
//		}
//	}
//
//	fclose(*f);
//	return data;
//}

// ===============================================================================================================//



