#pragma once
#include <iostream>

class Player
{
public:
    struct Bullet { float x, y; };

    Player(int max_ammo)
    {
        bullets = new Bullet[max_ammo];
        ammo = 0;
        health = 0;
        max_health = 100;
    }

    ~Player() {
        delete[] bullets;
    } 

    int health;
    int max_health;
    int ammo;
    int max_ammo;
    Bullet* bullets;
};

class TileMap
{
public:
    struct Tile { int x, y; int tile_value; };

    TileMap(int a_width, int a_height)
    {
        width = a_width;
        height = a_height;

        tiles = new Tile * [height];

        for (int row_index = 0; row_index < height; ++row_index)
        {
            tiles[row_index] = new Tile[width];
        }
    }
    ~TileMap() 
    {
        for (int row_index = 0; row_index < height; ++row_index)
        {
            delete[] tiles[row_index];
        }
        delete[] tiles;
    }

    int width;
    int height;
    Tile** tiles;
};

class Texture
{
public:
    Texture(char* a_filepath,
        int a_width,
        int a_height,
        int a_bytes_per_pixel)
    {
        int path_len = strlen(a_filepath);
        filepath = new char[path_len + 1];
        strcpy(filepath, a_filepath);

        width = a_width;
        height = a_height;

        pixel_data = new char[width * height * a_bytes_per_pixel];
    }

    ~Texture() 
    {
        delete[] filepath;
        delete[] pixel_data;
    }

    char* filepath;
    char* pixel_data;
    int width;
    int height;
};