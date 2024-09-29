#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

int main() {

    string gender;
    int age, weight, height, activityLevel;

    cout << "Please enter your gender (male or female): ";
    cin >> gender;
    cout << "Please enter your age: ";
    cin >> age;
    cout << "Please enter your weight (in kg): ";
    cin >> weight;
    cout << "Please enter your height (in cm): ";
    cin >> height;
    cout << "Please enter your activity level (1- Sedentary, 2- Lightly Active, 3- Moderately Active, 4- Very Active, 5- Extra Active): ";
    cin >> activityLevel;


    int bmr;
    if (gender == "male") {
        bmr = 66 + (13.7 * weight) + (5 * height) - (6.8 * age);
    } else {
        bmr = 655 + (9.6 * weight) + (1.8 * height) - (4.7 * age);
    }


    int tdee;
    switch(activityLevel) {
        case 1:
            tdee = bmr * 1.2;
            break;
        case 2:
            tdee = bmr * 1.375;
            break;
        case 3:
            tdee = bmr * 1.55;
            break;
        case 4:
            tdee = bmr * 1.725;
            break;
        case 5:
            tdee = bmr * 1.9;
            break;
        default:
            cout << "Invalid activity level." << endl;
            return 1;
    }

    cout << "Your daily caloric needs are: " << tdee << " calories." << endl;

    getch();
}