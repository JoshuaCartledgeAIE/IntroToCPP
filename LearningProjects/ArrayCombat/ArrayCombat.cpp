// ArrayCombat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    int healths[5];

    // initalise health values to 100
    for (int i = 0; i < 5; i++) {
        healths[i] = 100;
    }

    for (int i = 0; i < 5; i++) {
        int targetChar = 0;
        bool failed = false;
        do {
            std::cout << "Enter which character should be attacked (0-4):";
            failed = false;
            std::cin >> targetChar;
            if (std::cin.fail()) {
                failed = true;
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
            }
            else if (healths[targetChar] == 0) {
                failed = true;
                std::cout << "That character is already dead!" << std::endl;
                std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
            }
        } while (failed);
        std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer

        // attack target character
        int damage = rand() % 30 + 20;
        std::cout << "Character " << targetChar << " took " << damage << " damage!" << std::endl;
        healths[targetChar] -= damage;
        healths[targetChar] = (healths[targetChar] < 0) ? 0 : healths[targetChar]; // limit min health to 0

        for (int i = 0; i < 5; i++) {
            std::cout << "Character " << i << ": " << healths[i] << "HP, ";
        }
        std::cout << std::endl;
    }
}

