#pragma once
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "ColourType.h"



struct HRI
{

	static int Init(std::string file, bool debug = false);
	static std::vector<int> getPixels();
	static int getSizeX();
	static int getSizeY();
	static ColourType getColourType();

	

	
};

class HRISys {
public:
	static std::string RGBtoHex(int r, int g, int b, int a);
	static int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
};
