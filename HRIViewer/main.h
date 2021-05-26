#pragma once
#include <iostream>
#include <fstream>
#include <ios>
#include <raylib.h>
#include <string>
#include <vector>
#include <algorithm>

#include "ColourType.h"

bool isHRI = false;
ColourType ctype = ColourType::NON;
int SizeX = NULL, SizeY = NULL;
std::vector<int> pixels;

class Main
{
public:
	static int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
};

