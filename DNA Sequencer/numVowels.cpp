// CS1300-210 Fall 2020
// Author: Collin Butterworth
// Recitation: 210 - Steven Wilmes & Alexis Acevedo
// Project 1 - Problem #3

#include <iostream>
#include <string>
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

/*
 * This function determines how many vowels are in a string
 * Paramaters: user inputted string
 * Return: integer number of vowels in the string
*/

int numVowels(string input)
{
    char currentChar;
    bool vow;
    int count = 0;
    
    for (int i = 0; i < input.length(); i++)
    {
        currentChar = input[i];
        vow = isVowel(currentChar);
        
        if (vow == 1)
        {
            count++;
        }
        else
        {
        }
        
    }

    return count;
}

int main()
{
    string input;

    cout << "Type something to count vowels for: ";
    getline (cin, input);
    cout << numVowels(input) << endl;

    return 0;
}