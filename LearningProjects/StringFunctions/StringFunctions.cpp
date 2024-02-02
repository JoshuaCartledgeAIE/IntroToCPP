

#include <iostream>

int GetLength(const char string[]) {
    // Returns length of string
    int len = 0;
    // Loop through string and count length until null terminator is reached
    while (string[len] != '\0'){
        len++;
    }
    return len;
}

bool CompareStrings(const char stringA[], const char stringB[]) {
    // Returns true if both strings are identical, otherwise returns false
    // Check if strings are same length first so there are no issues when looping through both later
    if (GetLength(stringA) != GetLength(stringB)) {
        return false;
    }

    // Loop through each char and compare in both strings
    for (int i = 0; i < GetLength(stringA); i++) {
        if (stringA[i] != stringB[i]) {
            // One char does not match, therefore the strings are not identical, so return false
            return false;
        }
    }
    // All characters in both strings are identical, therefore return true
    return true;
}

char* CopyString(const char string[]) {
    // Make a new dynamic array based on the length of the inputted string
    char * newString = new char[GetLength(string) + 1];

    // Loop through each char in the input string and assign it to the new string
    for (int i = 0; i < GetLength(string); i++) {
        newString[i] = string[i];
    }

    // Add null terminator to the end of the string and return the finished copied string
    newString[GetLength(string)] = '\0';
    return newString;
}

char* ConcatStrings(const char stringA[], const char stringB[]) {
    // Make a new dynamic array based on the combined length of both inputted strings
    char* newString = new char[GetLength(stringA) + GetLength(stringB) + 1];

    // Loop through each char in the first string and assign it to the new string
    for (int i = 0; i < GetLength(stringA); i++) {
        newString[i] = stringA[i];
    }
    // Loop through each char in the second string and assign it to the new string
    for (int i = 0; i < GetLength(stringB); i++) {
        newString[i + GetLength(stringA)] = stringB[i];
    }

    // Add null terminator to the end of the string and return the finished concatenated string
    newString[GetLength(stringA) + GetLength(stringB)] = '\0';
    return newString;
}

int main()
{
    char string1[] = "test";
    std::cout << string1 << std::endl;
    char string2[] = "combo";
    std::cout << string2 << std::endl;

    char* string3 = ConcatStrings(string1, string2);
    
    std::cout << string3 << std::endl;

    delete[] string3;
}
