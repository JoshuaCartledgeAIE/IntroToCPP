
#include <iostream>

int main()
{
    while (true) {
        char word[15];
        std::cout << "Put in word to be translated:";
        std::cin >> word;

        char translated[20];
        bool firstCharIsVowel = false;
        bool secondCharIsVowel = false;
        for (int i = 0; i < 4; i++) {
            if (word[0] == "aeiou"[i]) {
                firstCharIsVowel = true;
            }
            if (word[1] == "aeiou"[i]) {
                secondCharIsVowel = true;
            }
        }

        if (firstCharIsVowel) {
            std::cout << word << "way";
        }
        else if (firstCharIsVowel == false && secondCharIsVowel) {
            for (int i = 1; i < strlen(word); i++) {
                std::cout << word[i];
            }
            std::cout << word[0] << "ay";
        }
        else if (firstCharIsVowel == false && secondCharIsVowel == false) {
            for (int i = 2; i < strlen(word); i++) {
                std::cout << word[i];
            }
            std::cout << word[0] << word[1] << "ay";
        }
        std::cout << std::endl;
    }
}

