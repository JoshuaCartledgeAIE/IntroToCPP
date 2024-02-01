
#include <iostream>

int main()
{
    std::cout << "Enter a word: ";
    char word[30];
    std::cin >> word;
    bool isPalindrome = true;
    for (int i = 0; i < strlen(word) / 2; i++) {
        if (word[i] != word[strlen(word) - i - 1]) {
            isPalindrome = false;
        }
    }

    if (isPalindrome) {
        std::cout << "The word is a palindrome!" << std::endl;
    }
    else {
        std::cout << "The word is not a palindrome." << std::endl;
    }
    
}

