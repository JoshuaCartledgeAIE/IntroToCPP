#include <iostream>

float result = 0;
char reuseResponse = 'n';

int main()
{

	float first = 0;
	float second = 0;
	char operand = '+';
	std::cout << "Welcome to the calculator program." << std::endl;
	while (true) {

		if (reuseResponse == 'n') {
			first = 0;
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
			std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
		}
		else {
			// user has elected to reuse the result
			first = result;
			std::cout << "Your first number is " << first << std::endl;
		}

		// reset operand and second number
		operand = '+';
		second = 0;

		// prompt user for operand
		std::cout << "Enter the operand: " << std::endl;
		std::cin >> operand;
		while (operand != '+' && operand != '-' && operand != '/' && operand != '*') { // user has entered a non-operand input
			std::cout << "That's not an operand, try again!" << std::endl;
			std::cout << "Enter the operand: " << std::endl;
			std::cin >> operand;
		}
		std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer

		// prompt user for second number
		std::cout << "Enter the second number: " << std::endl;
		std::cin >> second;
		while (std::cin.fail() == true) {
			std::cout << "That's not an integer, try again!" << std::endl;
			std::cin.clear(); // clear error
			std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
			std::cout << "Enter the second number: " << std::endl;
			std::cin >> second;
		}
		std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer

		// display correct operation and result
		switch (operand) {
		case '+':
			result = first + second;
			std::cout << first << " + " << second << " = " << result << std::endl;
			break;
		case '-':
			result = first - second;
			std::cout << first << " - " << second << " = " << result << std::endl;
			break;
		case '/':
			result = first / second;
			std::cout << first << " / " << second << " = " << result << std::endl;
			break;
		case '*':
			result = first * second;
			std::cout << first << " * " << second << " = " << result << std::endl;
			break;
		}

		

		// prompt if user wants to reuse the result
		std::cout << "Continue calculating with that result (y), or start from scratch (n)? " << std::endl;
		std::cin >> reuseResponse;
		while (reuseResponse != 'y' && reuseResponse != 'n') { // user has entered something that isn't y or n
			std::cout << "That's not 'y' or 'n', try again!" << std::endl;
			std::cout << "Continue calculating with that result (y), or start from scratch (n)? " << std::endl;
			std::cin >> reuseResponse;
		}
		std::cin.ignore(std::cin.rdbuf()->in_avail()); // remove letters from input readbuffer
		system("CLS"); // clear console
	}

	
}