#pragma once

#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "ColourType.h"



struct HRI
{
	HRI();
	HRI(char* fileName) {
		file = fileName;
	};
	int Read(bool debug = false);
	void newFile(std::string fileName, ColourType Colour, int xSize, int ySize);
	void WritePixel(int xpos, int ypos, std::int64_t Colour, bool hasHead = true);
	std::vector<std::int64_t> getPixels();
	int getSizeX();
	int getSizeY();
	ColourType getColourType();
	void save();
	
private:
	std::string file = "";
	bool dbg = false;
	std::vector<std::string> HRIU;
	std::vector<std::int64_t> basePixels;
};

class HRISys {
public:
	static std::string RGBtoHex(int r, int g, int b, int a);
	static int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
};
