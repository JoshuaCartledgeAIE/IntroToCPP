#include <iostream>
#include <windows.h>

const char* CSI = "\x1b[";
const char* TITLE = "\x1b[2;50H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";
const char* CLEAR_SCREEN = "\x1b[2J\x1b[H";


void main() {

	// Set output to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;
	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << YELLOW << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;
	std::cout << RESET_COLOR << "First, some questions..." << std::endl;

	std::cout << SAVE_CURSOR_POS;

	std::cout << "How tall are you, in centimeters? " << YELLOW << std::endl;
	std::cin >> height;
	std::cout << RESET_COLOR;
	std::cout << CSI << "?3l";

	if (std::cin.fail()) {
		std::cout << INDENT << "You have failed the first challenge and are eaten by a grue." << std::endl;
		return;
	}
	else {
		std::cout << INDENT << "You entered " << height << std::endl;
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cout << RESTORE_CURSOR_POS;
	std::cout << CSI << "4M";
	std::cout << "What is the first letter of your name? " << YELLOW << std::endl;
	std::cin >> firstLetterOfName;

	std::cout << RESET_COLOR;
	if (std::cin.fail() || !isalpha(firstLetterOfName)) {
		std::cout << INDENT << "You have failed the second challenge and are eaten by a grue." << std::endl;
		return;
	}
	else {
		std::cout << INDENT << "You entered " << firstLetterOfName << std::endl;
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	if (firstLetterOfName != 0) {
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else {
		avatarHP = 0;
	}

	std::cout << TITLE << CSI << 2L << MAGENTA << "BLOOP!" << RESET_COLOR;
	std::cout << RESTORE_CURSOR_POS << CSI << "A" << CSI << "4M";
	
	
	std::cout << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hitpoint(s)." << std::endl;
	std::cout << std::endl << "Press 'Enter' to exit the program." << std::endl;
	std::cin.get();
	return;
}

