// CS1300-210 Fall 2020
// Author: Collin Butterworth
// Recitation: 210 - Steven Wilmes & Alexis Acevedo
// Project 1 - Problem #2 

#include <iostream>
using namespace std;

/*
 * This function determines if a character is a vowel
 * Paramaters: user inputted character
 * Return: "TRUE" if vowel, "FALSE" if not
*/

bool isVowel(char input)
{
    bool vowel;
    
    if (input == 65 || input == 69 || input == 73 || input == 79 || input == 85 || input == 97 || input == 101 || input == 105 || input == 111 || input == 117)
    {
        vowel = true;
    }
    else
    {
        vowel = false;
    }

    return vowel;
}

int main()
{
    char input;
    
    cout << "Type a single character: ";
    cin >> input;
    cout << isVowel(input) << endl;
    
    return 0;
}