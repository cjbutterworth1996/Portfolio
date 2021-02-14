// CS1300-210 Fall 2020
// Author: Collin Butterworth
// Recitation: 210 - Steven Wilmes & Alexis Acevedo
// Project 1 - Problem #1

#include <iostream>
#include <string>
using namespace std;

/*
 * This function prints the reverse of an inputted string
 * Paramaters: user inputted string
 * Return: none
*/ 

void reverse(string input)
{
    int length = input.length();

    for (int i = length - 1; i >= 0; i--)
    {
        cout << input.substr(i, 1);
    }
}

int main ()
{
    string input; 

    cout << "Type something to reverse: ";
    getline (cin, input);
    reverse (input);

    return 0;
}