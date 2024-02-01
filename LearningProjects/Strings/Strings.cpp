

#include <iostream>
#include <string>

int main()
{
    char firstNames[5][20];
    char lastNames[5][20];
    char fullNames[5][40];

    for (int i = 0; i < 5; i++) {
        std::cout << "Add a first and last name: ";
        std::cin >> firstNames[i];
        std::cin >> lastNames[i];
        strcpy_s(fullNames[i], 40, firstNames[i]);
        strcat_s(fullNames[i], 40, " ");
        strcat_s(fullNames[i], 40, lastNames[i]);
        std::cout << std::endl;
    }
    
    
    for (int i = 0; i < 5; i++) {
        std::cout << "Hello " << fullNames[i] << ", ";
    }
}


