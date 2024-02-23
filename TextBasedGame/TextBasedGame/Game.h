#pragma once
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

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

	Room& GetRoom(int x, int y);
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

	int m_enemyCount;
	Enemy* m_enemies;

	int m_ItemCount;
	Item* m_Items;

	Player m_player;

	String m_spellName;
};

