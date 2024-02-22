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
	// Have player learn first spell
	m_player.LearnSpell(String("Shift"));
	m_player.LearnSpell(String("Teleport"));

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
	m_player.ExecuteCommand(command, &m_map[playerPos.y][playerPos.x], m_spellName, this);
	
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

	// Update visibility of rooms
	UpdateRoomVisibility();

	// Draw map and player
	DrawMap();
	m_player.Draw();
	
}

bool Game::IsGameOver()
{
	return m_gameOver;
}

Room& Game::GetRoom(int y, int x)
{
	return m_map[y][x];
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
		m_map[(int)(i / MAZE_WIDTH)][i % MAZE_WIDTH].RandomiseTransitions(this);
	}
}

void Game::UpdateRoomVisibility()
{
	// Get player position
	Point2D playerPos = m_player.GetPosition();
	Point2D position = { 0, 0 };
	// Loop through rooms and make them visible if they are 3 rooms away from the player
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++) {
			if (abs(playerPos.x - position.x) + abs(playerPos.y - position.y) <= VISION_RANGE)
			m_map[position.y][position.x].SetVisibility(true);
		}
	}
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

	// Draw Map borders (afterward so nothing draws over them)
	DrawMapBorders();

	DrawLegend();
}

void Game::DrawMapBorders() {
	// Draw top map border
	std::cout << YELLOW << MAP_OUTPUT_POS << "\xC9";
	for (int i = 0; i < MAZE_WIDTH * 5 - 1; i++) {
		std::cout << "\xCD";
	}
	std::cout << "\xBB" << std::endl;

	// Draw side map borders
	std::cout << MAP_OUTPUT_POS << CSI << "1C";
	for (int i = 0; i < MAZE_HEIGHT * 2 - 1; i++) {
		// Move cursor down 1 and back 1 and draw vertical line char
		std::cout << CSI << "1B" << CSI << "1D" << "\xBA";
	}
	// Move to other side of map
	std::cout << CSI << MAP_Y - 1 << ";" << MAZE_WIDTH * 5 + 7 << "H";
	for (int i = 0; i < MAZE_HEIGHT * 2 - 1; i++) {
		// Move cursor down 1 and back 1 and draw vertical line char
		std::cout << CSI << "1B" << CSI << "1D" << "\xBA";
	}

	// Draw bottom map border
	std::cout << CSI << MAP_Y - 1 + MAZE_HEIGHT * 2 << ";6H" << "\xC8";
	for (int i = 0; i < MAZE_WIDTH * 5 - 1; i++) {
		std::cout << "\xCD";
	}
	std::cout << "\xBC" << std::endl << RESET_COLOR;

}

void Game::DrawLegend()
{
	// Position cursor right of map
	std::cout << CSI << "6;" << MAZE_WIDTH * 5 + 11 << "H";
	std::cout << YELLOW << "Map Legend:" << RESET_COLOR << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << "\x9d = Entrance" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << MAGENTA << "\x81" << RESET_COLOR << " = Player" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << GREEN << "\xb1" << RESET_COLOR << " = Empty" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << RED << "\x94" << RESET_COLOR << " = Enemy" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << YELLOW << "$" << RESET_COLOR << " = Treasure" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";
	std::cout << "\xFE = Exit" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";
	
}

void Game::DrawValidDirections()
{
	// reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	// Delete 1 lines and insert 1 line
	std::cout << CSI << "1M" << CSI << "1L";

	int dirCount = m_map[m_player.GetPosition().y][m_player.GetPosition().x].GetTransitions().size();
	if (dirCount > 1)
		std::cout << INDENT << "You can see paths leading to the ";
	else
		std::cout << INDENT << "You can see a path leading to the ";
	
	for (int i = 0; i < dirCount; i++) {
		int dir = m_map[m_player.GetPosition().y][m_player.GetPosition().x].GetTransitions()[i];
		switch (dir) {
		case NORTH:
			std::cout << "north";
			break;
		case SOUTH:
			std::cout << "south";
			break;
		case EAST:
			std::cout << "east";
			break;
		case WEST:
			std::cout << "west";
			break;
		}
		if (i < dirCount - 2) {
			std::cout << ", ";
		}
		else if (i < dirCount - 1) {
			std::cout << " and ";
		}
		else {
			std::cout << ".";
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

	m_spellName = "";

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
		else if (inputCommand.Find("fight") == 0) {
			commandNo = FIGHT;
		}
		else if (inputCommand.Find("pickup") == 0) {
			commandNo = PICKUP;
		}
		else if (inputCommand.Find("cast") == 0) {
			commandNo = CAST;
			m_spellName = inputCommand.Substring(5, inputCommand.Length());
		}
		else if (inputCommand.Find("exit") == 0) {
			commandNo = QUIT;
		}
	}
	
	return commandNo;
}
