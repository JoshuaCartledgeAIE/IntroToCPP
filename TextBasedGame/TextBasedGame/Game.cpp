#include "Game.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"
#include <Windows.h>
#include <time.h>
#include "Enemy.h"
#include "Item.h"
#include <vector>
#include "BasicEnemy.h"
#include "ThiefEnemy.h"
#include "EliteEnemy.h"
#include "StatBooster.h"
#include "Spellbook.h"
#include "SimpleItems.h"


Game::Game() : m_gameOver{false}
{
}

// Destroys the stored objects (items and enemies)
Game::~Game()
{
	for (auto iter = m_items.begin(); iter < m_items.end(); iter++) {
		delete (*iter);
	}
	m_items.clear();
	for (auto iter = m_enemies.begin(); iter < m_enemies.end(); iter++) {
		delete (*iter);
	}
	m_enemies.clear();
}

// Calls all functions needed to intialize the game state.
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
	// Have player learn first spell (Shift)
	m_player.LearnSpell(String("Shift"));
	m_player.LearnSpell(String("Fireball"));
	m_player.LearnSpell(String("Lightning"));
	m_player.LearnSpell(String("Aegis"));

	return true;
}

// The main function that is run every game loop.
void Game::Update()
{
	// Get player position
	Point2D playerPos = m_player.GetPosition();

	// Exit game when player reaches exit
	if (m_map[playerPos.y][playerPos.x].GetType() == EXIT) {
		m_gameOver = true;
		return;
	}

	// If player dies, exit game
	if (m_player.IsAlive() == false) {
		m_gameOver = true;
		return;
	}

	int command = -1;
	if (m_player.IsInCombat())
		command = GetCombatCommand();
	else
		command = GetCommand();

	if (command == QUIT) {
		m_gameOver = true;
		return;
	}

	// Execute the command
	m_player.ExecuteCommand(command, &m_map[playerPos.y][playerPos.x], m_spellName, m_target, this);
	
	// If there are any dead enemies, remove them from their room
	for (int i = 0; i < m_enemies.size(); i++) {
		if (m_enemies[i]->IsAlive() == false) {
			Point2D enemyPos = m_enemies[i]->GetPosition();
			m_map[enemyPos.y][enemyPos.x].RemoveGameObject(m_enemies[i]);
		}
	}

	// check if player is in a room with an enemy
	playerPos = m_player.GetPosition();
	if (m_map[playerPos.y][playerPos.x].GetEnemies().size() > 0) {
		m_player.SetCombatState(true);
	}
	else {
		m_player.SetCombatState(false);
	}
}

// Calls draw functions for everything on the screen
void Game::Draw()
{
	// Get player position
	Point2D playerPos = m_player.GetPosition();

	// List the valid directions the player can travel (if not in combat)
	if (!m_player.IsInCombat())
		DrawValidDirections();
	
	m_map[playerPos.y][playerPos.x].DrawDescription();

	// Update visibility of rooms
	UpdateRoomVisibility();

	// Draw map and player
	DrawMap();
	m_player.Draw();
	
}

// Adds a random stat booster item to the specified position
void Game::AddStatItem(Point2D pos)
{
	StatType type = (StatType)(rand() % 4);

	switch (type)
	{
	case HP:
		m_items.push_back(new StatBooster(rand() % 9 + 10, type));
		break;
	case MP:
		m_items.push_back(new StatBooster(rand() % 9 + 8, type));
		break;
	case AT:
		m_items.push_back(new StatBooster(rand() % 6 + 3, type));
		break;
	case DF:
		m_items.push_back(new StatBooster(rand() % 6 + 2, type));
		break;
	default:
		break;
	}

	m_map[pos.y][pos.x].AddGameObject(m_items[m_items.size()-1]);
}

// Adds a new enemy to the maze of the specified type at the specified location
void Game::AddEnemy(Point2D pos, EnemyType type)
{
	int enemyCount = m_map[pos.y][pos.x].GetEnemies().size();
	int chanceToAddExtraEnemy = 0;

	// Create new enemy object with appropriate type, add it to the enemy list
	switch (type)
	{
	case BASIC:
		m_enemies.push_back(new BasicEnemy);
		chanceToAddExtraEnemy = 30;
		break;
	case THIEF:
		m_enemies.push_back(new ThiefEnemy);
		chanceToAddExtraEnemy = 40;
		break;
	case SUPPORT:
		chanceToAddExtraEnemy = 70;
		break;
	case ELITE:
		m_enemies.push_back(new EliteEnemy);
		chanceToAddExtraEnemy = 20;
		break;
	default:
		break;
	}

	// Tell the enemy its position and tell the room it contains an enemy
	m_enemies[m_enemies.size()-1]->SetPosition(pos);
	m_map[pos.y][pos.x].AddGameObject(m_enemies[m_enemies.size() - 1]);

	// Potentially add more enemies to the encounter
	if (enemyCount < 3 && rand() % 100 < chanceToAddExtraEnemy)
		AddEnemy(pos, (EnemyType)(rand() % 2));
}

// Configures terminal to handle special sequences
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

// Creates rooms in the map and generates their transitions
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

// Adds enemies to the map when the maze is first generated
void Game::InitializeEnemies()
{
	// Add a specific quantity of each enemy type randomly around the maze
	for (int i = 0; i < 10; i++) {
		// Add basic enemy to random unoccupied room
		AddEnemy(GetRandomEmptyPos(), BASIC);
	}

	for (int i = 0; i < 5; i++) {
		// Add thief enemy to random unoccupied room
		AddEnemy(GetRandomEmptyPos(), THIEF);
	}

	for (int i = 0; i < 5; i++) {
		// Add elite enemy to random unoccupied room
		AddEnemy(GetRandomEmptyPos(), ELITE);
	}
}

// Adds items to the map when the maze is first generated
void Game::InitializeItems()
{
	// add a set number of stat booster items
	for (int i = 0; i < 5; i++) {
		AddStatItem(GetRandomEmptyPos());
	}

	// add a spellbook for every spell
	String spellNames[] = { "Earthquake", "Fireball", "Lightning", 
		"Teleport", "Aegis"};
	for (String spell : spellNames) {
		// add the spellbook to the items array
		m_items.push_back(new Spellbook(spell));
	}

	//// Add one of each special item
	m_items.push_back(new LuckyClover);
	m_items.push_back(new SpellcastingGuidebook);
	m_items.push_back(new Torch);
	m_items.push_back(new HarvestersScythe);

	// For each item, add it to a random room in the maze
	for (Item* item : m_items) {
		Point2D pos = GetRandomEmptyPos();
		m_map[pos.y][pos.x].AddGameObject(item);
	}
	
}

// Makes every 2nd room randomise transitions to adjacent rooms
void Game::GenerateTransitions()
{
	for (int i = 0; i < MAZE_HEIGHT * MAZE_WIDTH; i += 2) {
		m_map[(int)(i / MAZE_WIDTH)][i % MAZE_WIDTH].RandomiseTransitions(this);
	}
}

// Returns a Point2D of a random room in the maze that is not occupied adn not near the entrance or exit
Point2D Game::GetRandomEmptyPos()
{
	int x = 0;
	int y = 0;
	int emergencyExit = 0;

	// find random unoccupied space
	do {
		x = rand() % MAZE_WIDTH;
		y = rand() % MAZE_HEIGHT;
		
		emergencyExit++; // Just to make sure there are no infinite while loops!
		if (emergencyExit > 1000) { return Point2D{ 1,1 }; }

	} while (m_map[y][x].GetEnemies().size() > 0 || m_map[y][x].GetItem() != nullptr
		|| x + y <= 2 || abs(MAZE_WIDTH - x) + abs(MAZE_HEIGHT - y) <= 2);
	// the conditions above also ensure that the position is not near the entrance or exit
	
	return Point2D{x, y};
}

// Updates if each room is visible based on the player's position and vision range
void Game::UpdateRoomVisibility()
{
	// Get player position
	Point2D playerPos = m_player.GetPosition();
	Point2D position = { 0, 0 };
	// Loop through rooms and make them visible if they are in the vision range of the player
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++) {
			if (abs(playerPos.x - position.x) + abs(playerPos.y - position.y) <= m_player.m_visionRange)
			m_map[position.y][position.x].SetVisibility(true);
		}
	}
}

// Redraws each room in the map, plus the borders and help text on the side
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
	DrawCommands();
}

// Draws the map borders, in a color indicating what is in the player's current room
void Game::DrawMapBorders() {
	// set border color based on current combat state
	String borderColor = GREY;
	if (m_player.IsInCombat())
		borderColor = RED;
	else if (m_map[m_player.GetPosition().y][m_player.GetPosition().x].GetItem() != nullptr)
		borderColor = YELLOW;


	// Draw top map border
	std::cout << borderColor << MAP_OUTPUT_POS << "\xC9";
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

// Draws a legend explaining what each symbol means on the map
void Game::DrawLegend()
{
	// Position cursor right of map at top
	std::cout << CSI << "3;" << MAZE_WIDTH * 5 + 11 << "H";

	// Write definitions of each symbol on the map
	std::cout << YELLOW << "Map Legend:" << RESET_COLOR << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << "\x9d = Entrance" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << MAGENTA << "\x81" << RESET_COLOR << " = Player" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << GREEN << "\xb1" << RESET_COLOR << " = Empty" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << RED << "\x94" << WHITE << ", " << ORANGE << "\x8B" << WHITE << ", "
		<< DARK_RED << "\x99" << RESET_COLOR << " = Enemies" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	std::cout << YELLOW << "$" << RESET_COLOR << " = Treasure" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";
	std::cout << "\xFE = Exit" << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

}

// Draws a list of available commands that the player can do
void Game::DrawCommands()
{
	// Position cursor right of map
	std::cout << CSI << "11;" << MAZE_WIDTH * 5 + 11 << "H";
	std::cout << YELLOW << "Commands:" << RESET_COLOR << std::endl;
	std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

	// Depending on if player is in combat, write available commands
	if (m_player.IsInCombat()) {
		std::cout << MAGENTA << "normal <enemyNum>" << RESET_COLOR << " OR " << MAGENTA
			<< "attack <enemyNum>" << RESET_COLOR << ": Performs a normal attack (deals damage equal to your AT stat)" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

		std::cout << MAGENTA << "risky <enemyNum>" << RESET_COLOR << ": Performs a risky attack (deals 2xAT damage, but only a " << m_player.m_riskyHitChance * 100 << "% chance to hit)" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

		std::cout << MAGENTA << "cast spellName" << RESET_COLOR << ": casts the named spell (see known spells below)" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

		std::cout << MAGENTA << "exit" << RESET_COLOR << ": Quits the game" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";
	}
	else {
		std::cout << MAGENTA << "move north/south/east/west" << RESET_COLOR << " OR " << MAGENTA
			<<  "w / a / s / d"  << RESET_COLOR << ": Moves player in the specified direction on the map" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

		std::cout << MAGENTA << "pickup" << RESET_COLOR << ": Picks up an item (if there is one) in the current room" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

		std::cout << MAGENTA << "cast spellName" << RESET_COLOR << ": casts the named spell (see known spells below)" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";

		std::cout << MAGENTA << "exit" << RESET_COLOR << ": Quits the game" << std::endl;
		std::cout << CSI << MAZE_WIDTH * 5 + 10 << "C";
	}
	
}

// Draws the directions in which the player can move from the current room
void Game::DrawValidDirections()
{
	// reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	// Delete 1 line and insert 1 line
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

// Gets the user's text input and converts it into a command
int Game::GetCommand()
{
	// jump to the correct location
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	// clear any existing text
	std::cout << CSI << "12M";
	// insert blank lines to ensure the inventory output remains correct
	std::cout << CSI << "12L";

	std::cout << INDENT << "Enter a command: ";
	int commandNo = -1;
	// move cursor to position for player to enter input
	std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;
	// clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	String inputCommand;
	// Read from console and convert to lowercase
	inputCommand.ReadFromConsole();
	inputCommand = inputCommand.ToLower();
	m_spellName = "";

	
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
	// Shorthands for move commands
	else if (inputCommand.Find("w") == 0 && inputCommand.Length() == 1) {
		commandNo = NORTH;
	}
	else if (inputCommand.Find("s") == 0 && inputCommand.Length() == 1) {
		commandNo = SOUTH;
	}
	else if (inputCommand.Find("a") == 0 && inputCommand.Length() == 1) {
		commandNo = WEST;
	}
	else if (inputCommand.Find("d") == 0 && inputCommand.Length() == 1) {
		commandNo = EAST;
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
	
	return commandNo;
}

// Gets the user's input during combat and converts it into a combat command
int Game::GetCombatCommand()
{
	// jump to the correct location
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	// clear any existing text
	std::cout << CSI << "12M";
	// insert blank lines to ensure the inventory output remains correct
	std::cout << CSI << "12L";

	std::cout << INDENT << "Enter a command: ";
	int commandNo = -1;
	// move cursor to position for player to enter input
	std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;
	// clear the input buffer, ready for player input
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	String inputCommand;
	// Read from console and convert to lowercase
	inputCommand.ReadFromConsole();
	inputCommand = inputCommand.ToLower();
	m_spellName = "";

	// Determine which command has been entered
	if (inputCommand.Find("normal") == 0 || inputCommand.Find("normal attack") == 0
		|| inputCommand.Find("attack") == 0) {
		commandNo = NORMAL_ATTACK;
		// get target index by removing everything else from the command
		inputCommand.Replace("normal", "");
		inputCommand.Replace("attack", "");
		inputCommand.Replace(" ", "");
		m_target = strtol(inputCommand, NULL, 10);
	}
	else if (inputCommand.Find("risky") == 0 || inputCommand.Find("risky attack") == 0) {
		commandNo = RISKY_ATTACK;
	}
	else if (inputCommand.Find("cast") == 0) {
		commandNo = CAST;
		inputCommand.Append(" "); // so that the find " " below works even if player just types "cast fireball"
		// get name of spell being cast
		m_spellName = inputCommand.Substring(5, inputCommand.Find(6, " "));
		// get target index by removing everything else from the command
		inputCommand.Replace("cast", "");
		inputCommand.Replace(m_spellName, "");
		inputCommand.Replace(" ", "");
		m_target = strtol(inputCommand, NULL, 10);
	}
	else if (inputCommand.Find("exit") == 0) {
		commandNo = QUIT;
	}
	else {
		commandNo = COMBAT_FAIL;
	}

	// default target is first enemy
	if (m_target == 0) m_target = 1;

	return commandNo;
}
