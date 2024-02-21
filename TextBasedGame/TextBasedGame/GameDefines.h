#pragma once
const char* const ESC = "\x1b";
const char* const CSI = "\x1b[";

const char* const TITLE = "\x1b[1;20H";
const char* const INDENT = "\x1b[5C";
const char* const YELLOW = "\x1b[93m";
const char* const MAGENTA = "\x1b[95m";
const char* const RED = "\x1b[91m";
const char* const BLUE = "\x1b[94m";
const char* const WHITE = "\x1b[97m";
const char* const GREEN = "\x1b[92m";
const char* const RESET_COLOR = "\x1b[0m";
const char* const STATS_OUTPUT_POS = "\x1b[2;6H";
const char* const MAP_OUTPUT_POS = "\x1b[3;6H";
const char* const EXTRA_OUTPUT_POS = "\x1b[22;6H";
const char* const INVENTORY_OUTPUT_POS = "\x1b[29;6H";

// room types
const int EMPTY = 0;
const int ENTRANCE = EMPTY + 1;
const int EXIT = ENTRANCE + 1;

const int WINDOW_HEIGHT = 60;
const int WINDOW_WIDTH = 150;

const int MAZE_WIDTH = 9;
const int MAZE_HEIGHT = 7;

// screen positions
const int INDENT_X = 5;
const int ROOM_DESC_Y = 18;
const int MOVEMENT_DESC_Y = 19;
const int MAP_Y = 4;
const int PLAYER_INPUT_X = 30;
const int PLAYER_INPUT_Y = 21;

// input commands
const int SOUTH = 2;
const int EAST = 6;
const int WEST = 4;
const int NORTH = 8;

const int LOOK = 9;
const int FIGHT = 10;
const int PICKUP = 11;
const int CAST = 12;
const int QUIT = 13;

// Adjectives for item names
static const char itemNames[15][30] = {
"indifference", "invisibility", "invulnerability", "incontinence",
"improbability", "impatience", "indecision", "inspiration",
"independence", "incurability", "integration", "invocation",
"inferno", "indigestion", "inoculation"
};

// Priority Values
const int PRIORITY_DEFAULT = 5;
const int PRIORITY_PLAYER = 0;
const int PRIORITY_ENEMY = 1;
const int PRIORITY_Item = 2;
const int PRIORITY_FOOD = 3;
