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
				
				if (HRI[i].find("!rgb") != std::string::npos) {
					ctype = ColourType::RGB;
					std::cout << "ColourType is: " << "RGB \n";
				} else 	if (HRI[i].find("!hex") != std::string::npos) {
					ctype = ColourType::HEX;
					std::cout << "ColourType is: " << "Hex \n";
				}


		//REMINDER: TEST IF COLOURTYPE VAIRABLE IS DEFINED
		}
			if (ctype == ColourType::NON) {
				std::cout << "FATAL ERROR: No ColouType Defined! Exiting Program... \n";
			}
		}


		
	}

	HRIimg.close();

	//Pause command REMEMBER TO DELETE when window is integrated
	std::cin.get();
	

	return 0;
}