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
			std::cout << "File is not HRI, ending program." << HRI[0].substr(4)<< "\n";
		}

		if (isHRI) {

		}
		
	}

	HRIimg.close();

	

	return 0;
}