#include "Book.h"
#include <string>
#include <iostream>
using namespace std;

/* 
// This function prints a list of Book objects with specified genre and authors starting with specified character
// Inputs: string of genre, char of author's first letter of name, an array of Book objects, int number of Book objects stored in the array
// Returns: int number of Book objects with specified genre and author name starting with specified character
*/

int printAuthorGenre(string genre, char authorFirstLetter, Book books[], int numBooksStored)
{
    int count = 0;
    string temp;
    bool declaration = 0;

    for (int i = 0; i < numBooksStored; i++)
    {
        if (books[i].getGenre() == genre)
        {
            temp = books[i].getAuthor();

            if (temp[0] == authorFirstLetter)
            {
                count++;
                
                if (declaration == 0)
                {
                    cout << "Here is a list of books that match this genre-author pair: " << endl;
                    declaration = 1;
                    cout << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
                }
                else
                {
                    cout << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
                }
            }
        }
    }

    if (count == 0)
    {
        cout << "No titles found for this genre-author pair." << endl;
    }

    return count;
}

int main()
{
    string genre;
    char authorFirstLetter;
    Book books[50];
    int numBooksStored = 0;

    cout << "Please enter genre: " << endl;
    getline(cin, genre);
    cout << "Please enter the first letter of the author's name: " << endl;
    cin >> authorFirstLetter;
    cout << "Please enter the number of books stored: " << endl;
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

    cout << printAuthorGenre(genre, authorFirstLetter, books, numBooksStored) << endl;

    return 0;
}