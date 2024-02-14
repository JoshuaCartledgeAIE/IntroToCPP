#include "Game.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "String.h"
#include "Enemy.h"
#include "Powerup.h"
#include "Food.h"


Game::Game() : m_gameOver{false}
{
}

Game::~Game()
{

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

	if (command == QUIT) {
		m_gameOver = true;
		return;
	}

	// If player is successfully able to execute this command (i.e. it is a move command), stop
	if (m_player.ExecuteCommand(command))
		return;

	// Otherwise, it might be a room specific command (i.e. look or fight), so execute it on the room
	m_map[playerPos.y][playerPos.x].ExecuteCommand(command, &m_player);
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

	// Intitalize map room positions
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			m_map[y][x].SetPosition(Point2D{x, y});
		}
	}

	// Initialize entrance and exit
	m_map[0][0].SetType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].SetType(EXIT);
}

void Game::InitializeEnemies()
{
	// Add a random number of enemies between 2 and 5
	m_enemyCount = 2 + rand() % 3;
	m_enemies = new Enemy[m_enemyCount];

	for (int i = 0; i < m_enemyCount; i++) {
		// spawn enemies at random position (not near entrance)
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		// Tell the enemy its position and tell the room it contains an enemy
		m_enemies[i].SetPosition(Point2D{ x, y });
		m_map[y][x].SetEnemy(&m_enemies[i]);
	}

}

void Game::InitializePowerups()
{
	// create some powerups
	m_powerupCount = 3;
	m_powerups = new Powerup[m_powerupCount];
	// randomly place the food in the map
	for (int i = 0; i < m_powerupCount; i++)
	{
		String name = "";
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);
		switch (i) {
		case 0:
			name = "potion of ";
			m_powerups[i].SetHealthMultiplier(1.1f);
			break;
		case 1:
			name = "sword of ";
			m_powerups[i].SetAttackMultiplier(1.1f);
			break;
		case 2:
			name = "shield of ";
			m_powerups[i].SetDefenceMultiplier(1.1f);
			break;
		}
		name.Append(itemNames[(rand() % 15)]);
		m_powerups[i].SetName(name);
		m_map[y][x].SetPowerup(&m_powerups[i]);
	}	
}

void Game::InitializeFood()
{
	// create some food
	m_foodCount = 3;
	m_food = new Food[m_foodCount];
	// randomly place the food in the map
	for (int i = 0; i < m_foodCount; i++)
	{
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);
		m_map[y][x].SetFood(&m_food[i]);
	}
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
	// insert 4 blank lines to ensure the inventory output remains correct
	std::cout << CSI << "4L";

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
	else if (inputCommand.Find("pickup") == 0) {
		commandNo = PICKUP;
	}
	else if (inputCommand.Find("exit") == 0) {
		commandNo = QUIT;
	}

	return commandNo;
}
