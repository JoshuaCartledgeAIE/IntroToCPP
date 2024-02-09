#include "Game.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "String.h"

Game::Game() : m_gameOver{false}
{
}

Game::~Game()
{
	// Deallocate memory from nested array of rooms
	for (int i = 0; i < MAZE_HEIGHT; i++) {
		delete[] m_map[i];
	}
	delete[] m_map;
}

bool Game::Startup()
{
	if (!EnableVirtualTerminal()) {
		std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
			std::cout << "Press 'Enter' to exit." << std::endl;
		std::cin.get();
		return false;
	}

	// Initialise map grid with random rooms
	InitializeMap();

	// Set player to start pos
	m_player.SetPosition(Point2D{ 0,0 });

	DrawWelcomeMessage();

	return true;
}

void Game::Update()
{
	// Get player position
	Point2D playerPos = m_player.GetPosition();

	// Exit game when player reaches exit
	if (m_map[playerPos.y][playerPos.x].GetType() == EXIT) {
		m_gameOver = true;
		return;
	}

	int command = GetCommand();

	// If player is successfully able to execute this command (i.e. it is a move command), stop
	if (m_player.ExecuteCommand(command)) 
		return;

	// Otherwise, it might be a room specific command (i.e. look or fight), so execute it on the room
	m_map[playerPos.y][playerPos.x].ExecuteCommand(command);
}

void Game::Draw()
{
	// Get player position
	Point2D playerPos = m_player.GetPosition();

	// List the valid directions the player can travel
	DrawValidDirections();
	
	m_map[playerPos.y][playerPos.x].DrawDescription();

	// Draw map and player
	DrawMap();
	m_player.Draw();
	
}

bool Game::IsGameOver()
{
	return m_gameOver;
}

bool Game::EnableVirtualTerminal()
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

void Game::InitializeMap()
{
	srand(time(nullptr));

	// Intitalize map rooms
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			int roomType = rand() % (MAX_RANDOM_TYPE * 2);
			if (roomType >= MAX_RANDOM_TYPE) {
				m_map[y][x].SetType(EMPTY);
			}
			else {
				m_map[y][x].SetType(roomType);
			}
			m_map[y][x].SetPosition(Point2D{x, y});
		}
	}

	// Initialize entrance and exit
	m_map[0][0].SetType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].SetType(EXIT);
}

void Game::DrawWelcomeMessage()
{
	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << YELLOW << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;
}

void Game::DrawMap()
{
	Point2D position = { 0, 0 };

	// reset draw colors
	std::cout << RESET_COLOR;
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		std::cout << INDENT;
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++) {
			m_map[position.y][position.x].Draw();
		}
		std::cout << std::endl;
	}
}

void Game::DrawValidDirections()
{
	// reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	std::cout << INDENT << "You can see paths leading to the " <<
		((m_player.GetPosition().x > 0) ? "west, " : "") <<
		((m_player.GetPosition().x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((m_player.GetPosition().y > 0) ? "north, " : "") <<
		((m_player.GetPosition().y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int Game::GetCommand()
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
