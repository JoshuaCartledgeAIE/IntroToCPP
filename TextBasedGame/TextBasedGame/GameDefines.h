#pragma once
// Important includes that are used by basically everything
#include "Point2D.h"
#include "String.h"
#include <iostream>

const char * const ESC = "\x1b";
const char * const CSI = "\x1b[";

// Screen Positions
const char * const TITLE = "\x1b[1;35H";
const char * const INDENT = "\x1b[5C";
const char * const RESET_COLOR = "\x1b[0m";
const char * const STATS_OUTPUT_POS = "\x1b[2;6H";
const char * const MAP_OUTPUT_POS = "\x1b[3;6H";
const char * const EXTRA_OUTPUT_POS = "\x1b[23;6H";
const char * const INVENTORY_OUTPUT_POS = "\x1b[31;6H";

// Colors
const char * const YELLOW = "\x1b[38;5;228m";
const char * const MAGENTA = "\x1b[38;5;164m";
const char * const ORANGE = "\x1b[38;5;208m";
const char * const RED = "\x1b[38;5;160m";
const char * const DARK_RED = "\x1b[38;5;88m";
const char * const BLUE = "\x1b[38;5;45m";
const char * const WHITE = "\x1b[38;5;15m";
const char * const GREEN = "\x1b[38;5;34m";
const char * const GREY = "\x1b[38;5;243m";

// room types
const int EMPTY = 0;
const int ENTRANCE = EMPTY + 1;
const int EXIT = ENTRANCE + 1;

const int WINDOW_HEIGHT = 60;
const int WINDOW_WIDTH = 200;

const int MAZE_WIDTH = 15;
const int MAZE_HEIGHT = 7;

// screen positions
const int INDENT_X = 5;
const int ROOM_DESC_Y = 18;
const int MOVEMENT_DESC_Y = 19;
const int MAP_Y = 4;
const int PLAYER_INPUT_X = 30;
const int PLAYER_INPUT_Y = 21;

// input commands
const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;

const int NORMAL_ATTACK = 9;
const int RISKY_ATTACK = 10;
const int PICKUP = 11;
const int CAST = 12;
const int QUIT = 13;
const int COMBAT_FAIL = 14;

// Priority Values
const int PRIORITY_DEFAULT = 5;
const int PRIORITY_PLAYER = 0;
const int PRIORITY_ENEMY = 1;
const int PRIORITY_ITEM = 2;


// Possible Enemy Attack Intents
const enum EnemyAttack {WEAK, MED, STRONG, DEBUFF, STEAL, ESCAPE};

// Different stat types (for stat booster item)
const enum StatType {HP, MP, AT, DF};

// Different Enemy types
const enum EnemyType {BASIC, THIEF, SUPPORT, ELITE};