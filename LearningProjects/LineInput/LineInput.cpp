
#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Enter line of words:";

    char line[120];
    int wordTotal = 1;
    int letterTotal = 0;
    cin.getline(line, 120, '\n');
    
    for (int i = 0; i < strlen(line); i++){
        if (line[i] == ' ') {
            wordTotal++;
        }
        else {
            letterTotal++;
        }
    }

    cout << "Words: " << wordTotal << endl << "Letters: " << letterTotal;

}
