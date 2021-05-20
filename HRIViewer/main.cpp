#include "main.h"

int main(int argc, char* argv[]) {
	std::cout << argv[1] << std::endl;
	std::string line;
	std::ifstream HRIimg (argv[1], std::ios::out);;

	if (HRIimg.is_open()) {
		while (std::getline(HRIimg, line))
		{
			std::cout << line << '\n';
		}
	}

	HRIimg.close();

	return 0;
}