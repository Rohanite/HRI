// HRI.cpp : Defines the functions for the static library.
//

#include "HRI.h"

static bool isHRI = false;
static ColourType ctype = ColourType::NON;
static int SizeX = NULL, SizeY = NULL;
static std::vector<int> pixels;

// TODO: This is an example of a library function
int HRI::Read(bool debug) {
	if (debug) {
		std::cout << file << std::endl;
	}
std::string line;
std::ifstream HRIimg(file, std::ios::out);;
std::vector<std::string> HRI;


if (HRIimg.is_open()) {
	//read individual lines
	while (std::getline(HRIimg, line))
	{
		HRI.push_back(line);
		if (debug) {
			std::cout << line << '\n';
		}
	}

	if (HRI[0].substr(0, 4) == "#HRI") {
		if (debug) {
			std::cout << "File is HRI \n";
		}
		isHRI = true;
	}
	else if (isHRI == false){
		return 1;
	}

	if (isHRI) {

		for (int i = 0; i < HRI.size(); i++) {

			std::string ActiveHRI = HRI[i];

			// Test if pixels are in RGB or Hex format
			if (ActiveHRI.find("!rgb") != std::string::npos) {
				ctype = ColourType::RGB;
				if (debug) {
					std::cout << "ColourType is: " << "RGB \n";
				}
			}
			else 	if (ActiveHRI.find("!hex") != std::string::npos) {
				ctype = ColourType::HEX;
				if (debug) {
					std::cout << "ColourType is: " << "Hex \n";
				}
			}


			//Read pixels
			std::size_t OpLoc = -1;
			std::size_t CpLoc = -1;
			if (SizeX != NULL && SizeY != NULL) {
				for (int i2 = 0; i2 < std::count(ActiveHRI.begin(), ActiveHRI.end(), '{'); i2++) {

					OpLoc = ActiveHRI.find("{", OpLoc + 1, 1);
					CpLoc = ActiveHRI.find("}", CpLoc + 1, 1);
					std::string TempPix = ActiveHRI.substr(OpLoc + 1, CpLoc - OpLoc - 1);
					if (debug) {
						std::cout << TempPix << " " << std::endl;
					}
					//read RGB pixels
					if (ctype == ColourType::RGB) {
						std::string r, g, b, a;
						r = TempPix.substr(0, HRISys::nthOccurrence(TempPix, ",", 1));
						g = TempPix.substr(HRISys::nthOccurrence(TempPix, ",", 1) + 2, HRISys::nthOccurrence(TempPix, ",", 2) - HRISys::nthOccurrence(TempPix, ",", 1) - 2);
						b = TempPix.substr(HRISys::nthOccurrence(TempPix, ",", 2) + 2, HRISys::nthOccurrence(TempPix, ",", 3) - HRISys::nthOccurrence(TempPix, ",", 2) - 2);
						a = TempPix.substr(HRISys::nthOccurrence(TempPix, ",", 3) + 2, HRISys::nthOccurrence(TempPix, ",", 4) - HRISys::nthOccurrence(TempPix, ",", 3) - 2);
						if (debug) {
							std::cout << r << std::endl << g << std::endl << b << std::endl << a << std::endl;
						}
						int nr;
						int ng;
						int nb;
						int na;
						try {
							nr = std::stoi(r);
							ng = std::stoi(g);
							nb = std::stoi(b);
							na = std::stoi(a);
						}
						catch (...) {
							return 2;
						}
						int finalpix;
						try {
							finalpix = std::stoul(HRISys::RGBtoHex(nr, ng, nb, na), nullptr, 16);
						}
						catch (...) {
							
							return 3;
						}
						if (debug) {
							std::cout << std::hex << finalpix << std::endl;
						}
						pixels.push_back(finalpix);

					}

					//read hex pixel
					if (ctype == ColourType::HEX) {
						int finalpix = 0;

						try {
							finalpix = std::stoul(TempPix, nullptr, 16);
						}
						catch (...) {
							return 4;
						}
						if (debug) {
							std::cout << std::hex << finalpix << "\n";
						}
						pixels.push_back(finalpix);
					}

				}

			}
			//Find the size of the image
			if (ActiveHRI.find("!{") != std::string::npos) {
				std::string Tempsize = ActiveHRI.substr(ActiveHRI.find("!{") + 2, ActiveHRI.find("}") - 2);
				if (debug) {
					std::cout << Tempsize << std::endl;
				}
				std::string tempSizeX = Tempsize.substr(0, Tempsize.find(","));
				if (debug) {
					std::cout << tempSizeX << "\n";
				}
				std::string tempSizeY = Tempsize.substr(Tempsize.find(",") + 2);
				if (debug) {
					std::cout << tempSizeY << "\n";
				}
				try {
					SizeX = std::stoi(tempSizeX);
					SizeY = std::stoi(tempSizeY);
				}
				catch (...) {
					return 5;
				}
			}

		}

		if (SizeX == NULL || SizeY == NULL) {
			return 6;
		}
		if (SizeX > 300 || SizeY > 300) {
			return 7;
		}
		if (ctype == ColourType::NON) {
			return 8;
		}

	}



}

if (debug) {
	std::cout << "Number of pixels are: " << pixels.size() << ". Ending file reading!" << std::endl;
}
if (pixels.size() < SizeX * SizeY) {
	return 9;
}
else if (pixels.size() > SizeX * SizeY) {
	std::cout << "WARNING: More pixels then stated! Not all pixels with defined colours will be displayed!" << std::endl;
}

HRIimg.close();


return 0;
}

std::vector<int> HRI::getPixels() {
	return pixels;
}

int HRI::getSizeX() {
	return SizeX;
}

int HRI::getSizeY() {
	return SizeY;
}

ColourType HRI::getColourType() {
	return ctype;
}

//Finds nth occurrence of char in string. I tried doing it myself but after too long I decided to borrow some code from jv74 on stackexchange https://stackoverflow.com/a/37327537
int HRISys::nthOccurrence(const std::string& str, const std::string& findMe, int nth)
{
	size_t  pos = 0;
	int     cnt = 0;

	while (cnt != nth)
	{
		pos += 1;
		pos = str.find(findMe, pos);
		if (pos == std::string::npos)
			return -1;
		cnt++;
	}
	return pos;
}

//Turn RGB pixels into hex pixels
std::string HRISys::RGBtoHex(int r, int g, int b, int a) {
	std::stringstream ss;

	ss << std::hex << r;
	if (ss.str().length() != 2) {
		ss << "0";
	}
	ss << std::hex << g;
	if (ss.str().length() != 4) {
		ss << "0";
	}
	ss << std::hex << b;
	if (ss.str().length() != 6) {
		ss << "0";
	}
	ss << std::hex << a;
	if (ss.str().length() != 8) {
		ss << "0";
	}

	return ss.str();
}