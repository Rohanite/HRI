#include "main.h"

int main(int argc, char* argv[]) {
	std::cout << argv[1] << std::endl;
	std::string line;
	std::ifstream HRIimg (argv[1], std::ios::out);;
	std::vector<std::string> HRI;


	if (HRIimg.is_open()) {
		while (std::getline(HRIimg, line))
		{
			HRI.push_back(line);
			std::cout << line << '\n';
		}

			if (HRI[0].substr(0, 4) == "#HRI") {
				std::cout << "File is HRI \n";
				isHRI = true;
			}
			else {
				std::cout << "FATAL ERROR: File is not HRI! ending program..." << HRI[0].substr(4) << "\n";
			}

		if (isHRI) {
			
			for (int i = 0; i < HRI.size(); i++) {

				std::string ActiveHRI = HRI[i];

				// Test if pixels are in RGB or Hex format
				if (ActiveHRI.find("!rgb") != std::string::npos) {
					ctype = ColourType::RGB;
					std::cout << "ColourType is: " << "RGB \n";
				} else 	if (ActiveHRI.find("!hex") != std::string::npos) {
					ctype = ColourType::HEX;
					std::cout << "ColourType is: " << "Hex \n";
				}


				
				//Read pixels
				std::size_t OpLoc = -1;
				std::size_t CpLoc = -1;
				if (SizeX != NULL && SizeY != NULL) {
					for (int i2 = 0; i2 < std::count(ActiveHRI.begin(), ActiveHRI.end(), '{'); i2++) {
						
						OpLoc = ActiveHRI.find("{", OpLoc + 1, 1);
						CpLoc = ActiveHRI.find("}", CpLoc+1, 1);
						std::string TempPix = ActiveHRI.substr(OpLoc+1, CpLoc-OpLoc-1);
						std::cout << TempPix << " " << std::endl;
						//read RGB pixels
						if (ctype == ColourType::RGB) {
							std::string r, g, b, a;
							r = TempPix.substr(0, Main::nthOccurrence(TempPix, ",", 1));
							g = TempPix.substr(Main::nthOccurrence(TempPix, ",", 1)+2, Main::nthOccurrence(TempPix, ",", 2)- Main::nthOccurrence(TempPix, ",", 1)-2);
							b = TempPix.substr(Main::nthOccurrence(TempPix, ",", 2) + 2, Main::nthOccurrence(TempPix, ",", 3) - Main::nthOccurrence(TempPix, ",", 2) - 2);
							a = TempPix.substr(Main::nthOccurrence(TempPix, ",", 3) + 2, Main::nthOccurrence(TempPix, ",", 4) - Main::nthOccurrence(TempPix, ",", 3) - 2);
							std::cout << r  << std::endl << g << std::endl << b << std::endl << a << std::endl;
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
								std::cout << "FATAL ERROR: Non-number found in pixels! Exiting Program... \n";
								return 0;
							}
							int finalpix;
							try {
								finalpix = std::stoi(Main::RGBtoHex(nr, ng, nb, na));
							}
							catch (...) {
								std::cout << "FATAL ERROR: RGB to hex conversion failed! Exiting Program... \n";
								return 0;
							}
							std::cout << finalpix << std::endl;
							pixels.push_back(finalpix);
							
						}

						if (ctype == ColourType::HEX) {
							int finalpix = 0;

							try {
								finalpix = std::stoi(TempPix, (size_t*)nullptr, 16);
							}
							catch (...) {
								"FATAL ERROR: Invalid char found in pixels! Exiting Program... \n";
							}
							std::cout << finalpix << "\n";
						}

					}
					std::cout << "Number of pixels are: " << pixels.size() << "Ending file reading!" << std::endl;
				}
			//Find the size of the image
			if (ActiveHRI.find("!{") != std::string::npos) {
					std::string Tempsize = ActiveHRI.substr(ActiveHRI.find("!{") + 2, ActiveHRI.find("}") - 2);
					std::cout << Tempsize << std::endl;
					std::string tempSizeX = Tempsize.substr(0, Tempsize.find(","));
					std::cout << tempSizeX << "\n";
					std::string tempSizeY = Tempsize.substr(Tempsize.find(",") + 2);
					std::cout << tempSizeY << "\n";
					try {
						SizeX = std::stoi(tempSizeX);
						SizeY = std::stoi(tempSizeY);
					}
					catch (...) {
						std::cout << "FATAL ERROR: Found a non-number in the size definition! \n";
					}
				}
		
			}

			if (SizeX == NULL || SizeY == NULL) {
				std::cout << "FATAL ERROR: Size not defined! Exiting Program... \n";
				return 0;
			}
			if (SizeX > 300 || SizeY > 300) {
				std::cout << "FATAL ERROR: Image is too large! Max Dimensions are 300x300! Exiting Program... \n";
				return 0;
			}
			if (ctype == ColourType::NON) {
				std::cout << "FATAL ERROR: No ColouType Defined! Exiting Program... \n";
				return 0;
			}

		}


		
	}

	HRIimg.close();

	//Pause command REMEMBER TO DELETE when window is integrated
	std::cin.get();
	

	return 0;
}

//Finds nth occurrence of char in string. I tried doing it myself but after too long I decided to borrow some code from jv74 on stackexchange https://stackoverflow.com/a/37327537
int Main::nthOccurrence(const std::string& str, const std::string& findMe, int nth)
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

std::string Main::RGBtoHex(int r, int g, int b, int a) {
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

