// Fibonacci.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int NextFibNum(int prevNum, int curNum) {
    return prevNum + curNum;
}

int GetNthFibNum(int n) {
    if (n == 1) return 0;
    
    int a = 0;
    int b = 1;
    int result = 0;
    for (int i = 0; i < n - 2; i++) {
        result = NextFibNum(a, b);
        a = b;
        b = result;
    }
    return b;
}

int main()
{
    while (true) {
        // prompt user for n
        int n = 0;
        std::cout << "Enter a value for n: ";
        std::cin >> n;
        while (std::cin.fail() == true || n <= 0) { // user has entered a non-integer input
            std::cout << "That's not a positive integer, try again!" << std::endl;
            std::cin.clear(); // clear error
            std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
            std::cout << "Enter a value for n: ";
            std::cin >> n; // Try to get input again
        }
        std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer


        

        std::cout << "The value in position " << n << " of the fibonacci sequence is " << GetNthFibNum(n) << std::endl;
    }
}

