// SecurityQuestions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <limits.h>
#include <random>
#include <map>
#include <ctype.h>
using namespace std;

//Basic User information
struct theUser
{
public:
    string username;
    string userID;
    string password;
    string encryptFormula(string& convertedPassword);
    string encrypt(string& password);
};

//Security Questions - These are unique per user
struct securityQuestions
{
    map<string, string> securityQs;
    map<securityQuestions, theUser> userQuestions;
};

//Encrypts passwords -- Method is simple enough -- Take password, convert to ASCII, take segments and modify to encrypt.
//Formula used to Encrypt
string theUser::encryptFormula(string& convertedPassword)
{
    int pos = 0;
    string encrypted; //Value to be returned;
    while (pos < convertedPassword.length())
    {
        int numberCombo = convertedPassword.at(pos);
        numberCombo = ((numberCombo * 128) % 287) + 33;
        //127 is a control character, but it prints a space, so it's good.
        encrypted += char(numberCombo);
        pos++;
    }

    return encrypted;
}
//Driver Function
string theUser::encrypt(string& password)
{
    //Password to be returned
    string encryptedPassword;

    for (int i = 0; i < password.length(); i++)
    {
        int ASCII; //Stores the ASCII values of a designated character
        if (isdigit(i))
        {
            int num = password.at(i);
            ASCII = int(num);
            encryptedPassword.append(to_string(ASCII));
        }
        else
        {
            char character = password.at(i);
            ASCII = int(character);
            encryptedPassword.append(to_string(ASCII));
        }
    }
    
    encryptedPassword = encryptFormula(encryptedPassword);
    return encryptedPassword;
}

//TO DO: Develop a Decrypter function

int main()
{
    //IDEA: Encrypt the password
    string user_name;
    string password; //What will be stored will be ENCRYPTED
    string userID;
    int userNamecount;
    vector<theUser> userList;

    cout << "How many users do you want to create? Enter a digit (ex. 2)" << endl;
    cin >> userNamecount;
    //Create a new theUser with this information
    for (int i = 0; i < userNamecount; i++)
    {
        theUser newUser;

        //User Input
        cout << "Enter your username" << endl;
        cin >> user_name;
        cout << endl;
        cout << "Enter your password" << endl;
        cin >> password;
        cout << endl;

        //Store user input into struct object
        newUser.username = user_name;
        newUser.password = newUser.encrypt(password);

        //Generate a random userID based on the username inputs and numbers
        unsigned int usernameLength = user_name.length();
        srand(time(nullptr));

        //All username lengths will be 8 characters long
        string userid;
        for (int i = 0; i < 8; i++)
        {

            //If the random number is divisible by 2 (mod 2 = 0), then append a random number between 0-9
            //If the random number is NOT divisible by 2 (mod 2 != 0), then append a random character based on what the user placed as his username
            int random = rand();
            bool isDivisibleby2 = (random % 2 == 0);

            if (isDivisibleby2)
            {
                int randNum = rand() % 10;
                userid.append(to_string(randNum));
            }
            else
            {
                int randPos = rand() % usernameLength;
                char letter = user_name.at(randPos);
                userid += letter;
            }

        }

        //Add the new userID into the object
        newUser.userID = userid;

        //Add the new object into the struct vector
        userList.push_back(newUser);
    }

    //Print all the usernames and userIDs
    int index = 0; //Position to extract information from user
    while (index < userList.size())
    {
        cout << "Username: " << userList.at(index).username;
        cout << "\n" << endl;
        cout << "User ID: " << userList.at(index).userID;
        cout << "\n" << endl;
        cout << "Encrypted Password: " << userList.at(index).password;
        cout << "\n" << endl;


        index++;
    }
}