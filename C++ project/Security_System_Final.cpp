#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string name;
    int id;
    string password;

public:
    void setName(string name) {
        this->name = name;
    }

    void setID(int id) {
        this->id = id;
    }

    void setPassword(string password) {
        this->password = password;
    }

    bool login(int id, string password) {
        return (this->id == id && this->password == password);
    }

    void changePassword(string newPassword) {
        password = newPassword;
        cout << "Password changed successfully." << endl;
    }

    void saveIDandPassword() {
        cout << "ID and password saved." << endl;
    }
};

int main() {
    User user;
    string name, password;
    int id;

    cout << "Enter name: ";
    getline(cin, name);
    user.setName(name);

    cout << "Enter ID: ";
    cin >> id;
    user.setID(id);

    cout << "Enter password: ";
    cin >> password;
    user.setPassword(password);

    // Saving ID and password
    user.saveIDandPassword();

    // Login setup
    int loginID;
    string loginPassword;

    cout << "Enter login ID: ";
    cin >> loginID;
    cout << "Enter login password: ";
    cin >> loginPassword;

    if (user.login(loginID, loginPassword)) {
        cout << "Login successful." << endl;
        // Change password
        string newPassword;
        cout << "Enter new password: ";
        cin >> newPassword;
        user.changePassword(newPassword);
    } else {
        cout << "Invalid login credentials." << endl;
    }

    return 0;
}