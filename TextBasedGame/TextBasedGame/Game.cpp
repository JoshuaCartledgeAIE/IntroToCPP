#include "Game.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "String.h"
#include "Enemy.h"
#include "Item.h"
#include <vector>


Game::Game() : m_gameOver{false}
{
}

Game::~Game()
{
	delete[] m_Items;
	delete[] m_enemies;
	delete[] m_food;
}

bool Game::Startup()
{
	if (!EnableVirtualTerminal()) {
		std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
			std::cout << "Press 'Enter' to exit." << std::endl;
		std::cin.get();
		return false;
	}

	srand(time(nullptr));

	// Initialise map grid with random rooms
	InitializeMap();
	InitializeEnemies();
	InitializeItems();

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

	// Execute the command
	m_player.ExecuteCommand(command, &m_map[playerPos.y][playerPos.x]);
	
	// If there are any dead enemies, remove them from their room
	for (int i = 0; i < m_enemyCount; i++) {
		if (m_enemies[i].IsAlive() == false) {
			Point2D enemyPos = m_enemies[i].GetPosition();
			m_map[enemyPos.y][enemyPos.x].RemoveGameObject(&m_enemies[i]);
		}
	}
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

	std::cout << CSI << "8;" << WINDOW_HEIGHT << ";" << WINDOW_WIDTH << "t";

	return true;
}

void Game::InitializeMap()
{
	// Intitalize map room positions
	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			m_map[y][x].SetPosition(Point2D{x, y});
		}
	}

	// Add random transitions to rooms
	GenerateTransitions();

	// Initialize entrance and exit
	m_map[0][0].SetType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].SetType(EXIT);
}

void Game::InitializeEnemies()
{
	// Add a random number of enemies between 8 and 10
	m_enemyCount = 8 + rand() % 3;
	m_enemies = new Enemy[m_enemyCount];

	for (int i = 0; i < m_enemyCount; i++) {
		// spawn enemies at random position (not near entrance)
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		// Tell the enemy its position and tell the room it contains an enemy
		m_enemies[i].SetPosition(Point2D{ x, y });
		m_map[y][x].AddGameObject(&m_enemies[i]);
	}

}

void Game::InitializeItems()
{
	// create some Items
	m_ItemCount = 7;
	m_Items = new Item[m_ItemCount];
	// randomly place the food in the map
	for (int i = 0; i < m_ItemCount; i++)
	{
		String name = "";
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);
		switch (rand() % 3) {
		case 0:
			name = "potion of ";
			m_Items[i].SetHealthMultiplier(1.1f);
			break;
		case 1:
			name = "sword of ";
			m_Items[i].SetAttackMultiplier(1.1f);
			break;
		case 2:
			name = "shield of ";
			m_Items[i].SetDefenceMultiplier(1.1f);
			break;
		}
		name.Append(itemNames[(rand() % 15)]);
		m_Items[i].SetName(name);
		m_map[y][x].AddGameObject(&m_Items[i]);
	}	
}

void Game::GenerateTransitions()
{
	for (int i = 0; i < MAZE_HEIGHT * MAZE_WIDTH; i += 2) {
		m_map[(int)(i / MAZE_WIDTH)][i % MAZE_WIDTH].RandomiseTransitions(&m_map);
	}
}

void Game::DrawWelcomeMessage()
{
	
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
	std::cout << INDENT << "You can see paths leading to the ";
	for (int dir : m_map[m_player.GetPosition().y][m_player.GetPosition().x].GetTransitions()) {
		switch (dir) {
		case NORTH:
			std::cout << "north, ";
			break;
		case SOUTH:
			std::cout << "south, ";
			break;
		case EAST:
			std::cout << "east, ";
			break;
		case WEST:
			std::cout << "west, ";
			break;
		}
	}
}

int Game::GetCommand()
{
	// jump to the correct location
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	// clear any existing text
	std::cout << CSI << "5M";
	// insert 5 blank lines to ensure the inventory output remains correct
	std::cout << CSI << "5L";

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

	// Move command has a direction afterward
	if (inputCommand.Find("W") == 0) {
		commandNo = NORTH;
	}
	else if (inputCommand.Find("S") == 0) {
		commandNo = SOUTH;
	}
	else if (inputCommand.Find("A") == 0) {
		commandNo = WEST;
	}
	else if (inputCommand.Find("D") == 0) {
		commandNo = EAST;
	}
	else {
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
	}
	

	return commandNo;
}
