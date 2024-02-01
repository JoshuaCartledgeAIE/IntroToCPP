
#include <iostream>

float gallonsToLitres = 3.78533f;

float convertLitresToGallons(const float litres);

int main() {
	float gallons;
	float litres;

	std::cout << "Input Gallons: ";
	std::cin >> gallons;

	litres = gallons * gallonsToLitres;
	std::cout << "That is equal to " << litres << " litres.";
	std::cout << "That is equal to " << convertLitresToGallons(litres) << " gallons.";
}

