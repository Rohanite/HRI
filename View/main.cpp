#include "main.h"

int main(int argc, char* argv[]) {

	if (argv[1] == NULL) {
		std::cout << "FATAL ERROR: No file given! Ending Program..." << std::endl;

	}
	bool debug = false;
	
	HRI Image = HRI(argv[1]);

	if (argv[2] != NULL) {
		if (std::strcmp(argv[2], "-d") == 0) {
			debug = true;
			std::cout << "Debug True" << std::endl;
		}
	}
	int initSuccess = Image.Read(debug);
	if (debug == true) {
		std::cout << "Writing Pixel! \n";
		Image.WritePixel(3, 2, 0xFFFFFFFF);
		Image.WritePixel(1, 2, 0xFFAACCFF);
	    Image.save();
	}

	if (initSuccess == 0) {

		int SizeX = Image.getSizeX();
		int SizeY = Image.getSizeY();
		std::vector<std::int64_t> pixels = Image.getPixels();
		const int WindowSizeX = 1000, WindowSizeY = 1000;
		InitWindow(WindowSizeX, WindowSizeY, "View");
		while (!WindowShouldClose()) {
			BeginDrawing();
			ClearBackground(GRAY);
			//draw pixels
			int pixelsizeY = WindowSizeY / (SizeY * 2);
			int pixelsizeX = WindowSizeY / (SizeY * 2);
			if (SizeX == SizeY) {
				pixelsizeX = pixelsizeX * 1.5;
				pixelsizeY = pixelsizeY * 1.5;
			}
			int offsetX = WindowSizeX / 2 - pixelsizeX * SizeX / 2;
			int offsetY = WindowSizeY / 2 - pixelsizeY * SizeY / 2;
			int pixnum = 0;

			for (int i = 0; i < SizeY; i++) {
				for (int i2 = 0; i2 < SizeX; i2++) {
					DrawRectangle(i2 * pixelsizeX + offsetX, i * pixelsizeY + offsetY, pixelsizeX, pixelsizeY, GetColor(pixels[pixnum]));
					pixnum++;

				}
			}

			//draw barrier
			DrawRectangle(offsetX, offsetY - 10, SizeX * pixelsizeX, 10, WHITE);
			DrawRectangle(offsetX, SizeY * pixelsizeY + offsetY, SizeX * pixelsizeX, 10, WHITE);
			DrawRectangle(offsetX - 10, offsetY - 10, 10, SizeY * pixelsizeY + 20, WHITE);
			DrawRectangle(SizeX * pixelsizeX + offsetX, offsetY - 10, 10, SizeY * pixelsizeY + 20, WHITE); 
			EndDrawing();
		}
		CloseWindow();

	}
	else if (initSuccess == 0) {
		std::cout << "FATAL ERROR: File is not HRI! Ending program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 2) {
		std::cout << "FATAL ERROR: Non-number found in pixels! Exiting Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 3) {
		std::cout << "FATAL ERROR: RGB to hex conversion failed! Exiting Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 4) {
		std::cout << "FATAL ERROR: Invalid char found in pixels! Exiting Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 5) {
		std::cout << "FATAL ERROR: Found a non-number in the size definition! Exiting Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 6) {
		std::cout << "FATAL ERROR: Size not defined! Exiting Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 7) {
		std::cout << "FATAL ERROR: Image is too large! Max Dimensions are 300x300! Exiting Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 8) {
		std::cout << "FATAL ERROR: No ColouType Defined! Exiting Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 9) {
		std::cout << "FATAL ERROR: Less pixels then stated! Closing Program..." << std::endl;
		std::cin;
	}
	else if (initSuccess == 10) {
		std::cout << "FATAL ERROR: File is empty! Exiting Program...";
		std::cin;
	}
	else if (initSuccess >= 11) {
		std::cout << "FATAL ERROR: UNDEFINED! If this error persists and the build you are using was pre-built then please lodge an issue at https://github.com/Rohanite/HRI/issues! Exiting Program...";
		std::cin;
	}

	return 0;
}