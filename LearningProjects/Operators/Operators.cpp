#include <iostream>

int main()
{
	float first = 0;
	float second = 0;

	// prompt user for first number
	std::cout << "Enter the first number: " << std::endl;
	std::cin >> first;
	while (std::cin.fail() == true) { // user has entered a non-integer input
		std::cout << "That's not an integer, try again!" << std::endl;
		std::cin.clear(); // clear error
		std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
		std::cout << "Enter the first number: " << std::endl;
		std::cin >> first; // Try to get input again
	}

	std::cout << "Enter the second number: " << std::endl;
	std::cin >> second;
	while (std::cin.fail() == true) {
		std::cout << "That's not an integer, try again!" << std::endl;
		std::cin.clear(); // clear error
		std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
		std::cout << "Enter the second number: " << std::endl;
		std::cin >> second;
	}

	std::cout << "The two numbers entered are: " << first << " and " << second << "." << std::endl;
	std::cout << first << " + " << second << " = " << (first + second) << std::endl;
	std::cout << first << " - " << second << " = " << (first - second) << std::endl;
	std::cout << first << " / " << second << " = " << (first / second) << std::endl;
	std::cout << first << " * " << second << " = " << (first * second) << std::endl;
	//std::cout << first << " % " << second << " = " << (first % second) << std::endl;
}