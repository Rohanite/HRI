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


				

				std::size_t OpLoc = -1;
				std::size_t CpLoc = -1;
				if (SizeX != NULL && SizeY != NULL) {
					for (int i2 = 0; i2 < std::count(ActiveHRI.begin(), ActiveHRI.end(), '{'); i2++) {
						
						OpLoc = ActiveHRI.find("{", OpLoc + 1, 1);
						CpLoc = ActiveHRI.find("}", CpLoc+1, 1);
						std::string TempPix = ActiveHRI.substr(OpLoc+1, CpLoc-OpLoc-1);
						std::cout << TempPix << " " << std::endl;

						if (ctype == ColourType::RGB) {
							std::string r, g, b, a;
							int rloc, gloc, bloc, aloc;
							rloc = TempPix.find(",");
							r = TempPix.substr(0, rloc);
							std::cout << r << std::endl;
							gloc = TempPix.find(",", rloc + 1);
							g = TempPix.substr(rloc+2, gloc-rloc-2);
							std::cout << g << std::endl;
							bloc = TempPix.find(",", gloc + 1);
							b = TempPix.substr(bloc, bloc-gloc);
							std::cout << b << " " << gloc << " " << rloc << " " << bloc << std::endl;
						} 

					}
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