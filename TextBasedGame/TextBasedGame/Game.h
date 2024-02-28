#pragma once
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"
#include <vector>

class Enemy;
class Item;

class Game {
public:
	Game();
	~Game();

public:
	bool Startup();
	void Update();
	void Draw();
	bool IsGameOver();

	Room& GetRoom(int y, int x) { return m_map[y][x]; }
	Room& GetRoom(Point2D pos) { return m_map[pos.y][pos.x]; }
	Player* GetPlayer() { return &m_player; }

private:
	bool EnableVirtualTerminal();
	void InitializeMap();
	void InitializeEnemies();
	void InitializeItems();
	
	void GenerateTransitions();

	void UpdateRoomVisibility();
	void DrawMap();
	void DrawMapBorders();
	void DrawLegend();
	void DrawCommands();
	void DrawValidDirections();

	int GetCommand();

	int GetCombatCommand();

private:
	bool m_gameOver;

	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];

	std::vector<Enemy*> m_enemies;

	std::vector<Item*> m_items;

	Player m_player;

	String m_spellName;
};

