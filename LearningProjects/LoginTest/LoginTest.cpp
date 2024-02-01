

#include <iostream>
using namespace std;

int main()
{
    cout << "Enter username: ";
    char username[20];
    cin >> username;

    char password[20];
    bool failed = false;
    do {
        cout << "Enter password: ";
        cin >> password;

        failed = false;
        bool capital = false;
        bool num = false;
        bool symbol = false;
        for (char c : password) {
            // check ASCII codes of character
            if ((c > 32 && c < 48) || (c > 122)) {
                symbol = true;
            }
            if (c > 47 && c < 58) {
                num = true;
            }
            if (c > 64 && c < 91) {
                capital = true;
            }
        }
        if (capital == false || symbol == false || num == false) {
            failed = true;
            cout << "Your password does not contain at least one captial letter, symbol and number! Try again." << endl;
        }
        
        // check length of password
        if (strlen(password) < 8) {
            failed = true;
            cout << "That is too short! Try again." << endl;
        }

    } while (failed);

    cout << "Your username is " << username << " and your password is " << password;
    
}

