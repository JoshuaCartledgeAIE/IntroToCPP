#include <iostream>
#include <windows.h>
#include <time.h>
#include <random>
#include "String.h"

const char* CSI = "\x1b[";
const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* RED = "\x1b[91m";
const char* BLUE = "\x1b[94m";
const char* WHITE = "\x1b[97m";
const char* GREEN = "\x1b[92m";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";
const char* CLEAR_SCREEN = "\x1b[2J\x1b[H";
const char* EXTRA_OUTPUT_POS = "\x1b[25;6H";

const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTRANCE = 4;
const int EXIT = 5;

const int MAX_RANDOM_TYPE = FOOD + 1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;

const int INDENT_X = 5;
const int ROOM_DESC_Y = 8;
const int MOVEMENT_DESC_Y = 9;
const int MAP_Y = 13;
const int PLAYER_INPUT_X = 23;
const int PLAYER_INPUT_Y = 23;

const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;
const int LOOK = 9;
const int FIGHT = 10;


bool EnableVirtualTerminal();
void Initialize(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void DrawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y);
void DrawMap(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void DrawRoomDescription(int roomType);
void DrawPlayer(int x, int y);
void DrawValidDirections(int x, int y);
int GetCommand();

int main() {

	if (EnableVirtualTerminal() == false) {
		std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
		std::cout << "Press 'Enter' to exit." << std::endl;
		std::cin.get();
		return 0;
	}

	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;

	Initialize(rooms);

	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << YELLOW << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;

	std::cout << SAVE_CURSOR_POS;
	

	std::cout << CSI << MAP_Y << ";" << 0 << "H"; // sets cursor to start of map row
	// Print map
	DrawMap(rooms);

	bool gameOver = false;
	int playerX = 0;
	int playerY = 0;

	while (!gameOver) {
		
		// Write description of current room
		DrawRoomDescription(rooms[playerY][playerX]);
	
		// Print available path options
		DrawValidDirections(playerX, playerY);

		// prints player at its position
		DrawPlayer(playerX, playerY);

		int command = GetCommand();

		DrawRoom(rooms, playerX, playerY);

		// Move player in chosen direction
		switch (command) {
		case EAST:
			if (playerX < MAZE_WIDTH - 1) {
				playerX++;
			}
			break;
		case WEST: 
			if (playerX > 0) {
				playerX--;
			}
			break;
		case NORTH:
			if (playerY > 0) {
				playerY--;
			}
			break;
		case SOUTH:
			if (playerY < MAZE_HEIGHT - 1) {
				playerY++;
			}
			break;
		case LOOK:
			DrawPlayer(playerX, playerY);
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning." << std::endl;
				std::cout << INDENT << "Press 'Enter' to continue.";
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.get();
			break;
		case FIGHT:
			DrawPlayer(playerX, playerY);
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon." << std::endl;
				std::cout << INDENT << "Press 'Enter' to continue.";
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.get();
			break;
		default:
			// the direction was not valid,
			// do nothing, go back to the top of the loop and ask again
			DrawPlayer(playerX, playerY);
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << std::endl;
				std::cout << INDENT << "Press 'Enter' to continue.";
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.get();
		}
	}


	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return 0;
}

bool EnableVirtualTerminal()
{
	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

void Initialize(int map[MAZE_HEIGHT][MAZE_WIDTH]) {
	srand(time(nullptr));

	// Intitalize map rooms
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			int roomType = rand() % (MAX_RANDOM_TYPE * 2);
			if (roomType >= MAX_RANDOM_TYPE) {
				map[y][x] = EMPTY;
			}
			else {
				map[y][x] = roomType;
			}
		}
	}

	// Initialize entrance and exit
	map[0][0] = ENTRANCE;
	map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;
}

void DrawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y) {
	// find the console output position
	int outX = INDENT_X + (6 * x) + 1;
	int outY = MAP_Y + y;
	// jump to the correct location
	std::cout << CSI << outY << ";" << outX << "H" << RESET_COLOR;
	// draw the room
	switch (map[y][x]) {
	case EMPTY:
		std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
		break;
	case ENEMY:
		std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
		break;
	case TREASURE:
		std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
		break;
	case FOOD:
		std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
		break;
	case ENTRANCE:
		std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
		break;
	case EXIT:
		std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
		break;
	}
}

void DrawMap(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
	// reset draw colors
	std::cout << RESET_COLOR;
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		std::cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++) {
			DrawRoom(map, x, y);
		}
		std::cout << std::endl;
	}
}

void DrawRoomDescription(int roomType)
{
	// reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	// Delete 4 lines and insert 4 empty lines
	std::cout << CSI << "4M" << CSI << "4L" << std::endl;
	// write description of current room
	switch (roomType) {
	case EMPTY:
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
			break;
	case ENEMY:
		std::cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching." << std::endl;
			break;
	case TREASURE:
		std::cout << INDENT << "Your journey has been rewarded. You have found some treasure." << std::endl;
			break;
	case FOOD:
		std::cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
			break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked.There is no going back." << std::endl;
			break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
			break;
	}
}

void DrawPlayer(int x, int y)
{
	x = INDENT_X + (6 * x) + 3;
	y = MAP_Y + y;
	// draw the player's position on the map
	// move cursor to map pos and delete character at current position
	std::cout << CSI << y << ";" << x << "H";
	std::cout << MAGENTA << "\x81" << RESET_COLOR;
}

void DrawValidDirections(int x, int y) {
	// reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	std::cout << INDENT << "You can see paths leading to the " <<
		((x > 0) ? "west, " : "") <<
		((x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((y > 0) ? "north, " : "") <<
		((y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int GetCommand()
{
	// jump to the correct location
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	// clear any existing text
	std::cout << CSI << "4M";
	std::cout << INDENT << "Enter a command: ";
	int commandNo = 0;
	// move cursor to position for player to enter input
	std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;
	// clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	String inputCommand;
	// Read from console and convert to lowercase
	inputCommand.ReadFromConsole();
	inputCommand = inputCommand.ToLower();

	// Determine which command has been entered
	if (inputCommand.Find("move") == 0) {
		// Move command has a direction afterward
		if (inputCommand.Find(4, "north") != -1) {
			commandNo = NORTH;
		}
		else if (inputCommand.Find(4, "south") != -1) {
			commandNo = SOUTH;
		}
		else if (inputCommand.Find(4, "west") != -1) {
			commandNo = WEST;
		}
		else if (inputCommand.Find(4, "east") != -1) {
			commandNo = EAST;
		}
		else return -1; // Invalid direction word
	}
	else if (inputCommand.Find("look") == 0) {
		commandNo = LOOK;
	}
	else if (inputCommand.Find("fight") == 0) {
		commandNo = FIGHT;
	}

	return commandNo;
}




