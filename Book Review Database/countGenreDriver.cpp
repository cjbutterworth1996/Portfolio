#include "Book.h"
#include <string>
#include <iostream>
using namespace std;

/* 
// This function counts the number of Book objects in an array that have a specified genre
// Inputs: string of genre, an array of Book objects, int number of Book objects in the array
// Returns: int number of Book objects with specified genre
*/ 

int countGenre(string genre, Book books[], int numBooksStored)
{
    int count = 0;

    for (int i = 0; i < numBooksStored; i++)
    {
        if (books[i].getGenre() == genre)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    Book books[50];
    string genre;
    int numBooksStored = 0;

    cout << "Enter genre name: " << endl;
    getline(cin, genre);
    cout << "Enter number of books stored: " << endl;
    cin >> numBooksStored;

    books[0].setTitle("The Hobbit");
    books[0].setAuthor("J.R.R. Tolkien");
    books[0].setGenre("Fantasy");

    books[1].setTitle("Ender's Game");
    books[1].setAuthor("Orson Scott Card");
    books[1].setGenre("Science Fiction");

    books[2].setTitle("Harry Potter and the Sorcerer's Stone");
    books[2].setAuthor("J.K. Rowling");
    books[2].setGenre("Fantasy");

    cout << countGenre(genre, books, numBooksStored) << endl;

    return 0;
}