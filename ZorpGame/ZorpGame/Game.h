#pragma once
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

class Enemy;
class Food;
class Powerup;

class Game {
public:
	Game();
	~Game();

public:
	bool Startup();
	void Update();
	void Draw();
	bool IsGameOver();

private:
	bool EnableVirtualTerminal();
	void InitializeMap();
	void InitializeEnemies();
	void InitializePowerups();
	void InitializeFood();

	void DrawWelcomeMessage();
	void DrawMap();
	void DrawValidDirections();
	int GetCommand();

private:
	bool m_gameOver;

	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];

	int m_enemyCount;
	Enemy* m_enemies;

	int m_foodCount;
	Food* m_food;

	int m_powerupCount;
	Powerup* m_powerups;

	Player m_player;
};

