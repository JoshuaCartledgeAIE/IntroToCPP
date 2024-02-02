
#include <iostream>

int main()
{
    int frequencies[26];
    for (int i = 0; i < 26; i++) {
        frequencies[i] = 0;
    }

    char inputStr[100];
    std::cout << "Enter a line of text: ";
    std::cin.getline(inputStr, 100);

    for (int i = 0; i < strlen(inputStr); i++) {
        frequencies[inputStr[i] - 97]++;
    }

    int mostFrequentFrequency = 0;
    char mostFrequentLetter = ' ';

    for (int i = 0; i < 26; i++) {
        if (frequencies[i] > mostFrequentFrequency) {
            mostFrequentFrequency = frequencies[i];
            mostFrequentLetter = i + 97;
        }
    }

    std::cout << "The most frequent letter was " << mostFrequentLetter << " and it appeared " << mostFrequentFrequency << " times";
}
