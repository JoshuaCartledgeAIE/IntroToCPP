#include <iostream>
using namespace std;

int main()
{
    char username[20];
    bool failed = false;
    do {
        cout << "Enter username: ";
        cin >> username;

        failed = true;
        for (int i = 0; i < strlen(username) - 2; i++) {
            if (username[i] == 'u' && username[i + 1] == 's' && username[i + 2] == 'r') {
                failed = false;
            }
        }

        if (failed) cout << "That doesn't contain 'usr'!" << endl;

    } while (failed);

    char password[20];
    failed = false;
    do {
        cout << "Enter password: ";
        cin >> password;

        failed = strcmp(password, "Pa55w0rd");

        if (failed) cout << "That is not an exact match!" << endl;
    } while (failed);

    char identifier[40] = "";
    strcpy_s(identifier, 40, username);
    strcat_s(identifier, 40, "-");
    strcat_s(identifier, 40, password);
    cout << "Your identifier is " << identifier;
}
