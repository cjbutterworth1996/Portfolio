#include "Book.h"
#include <string>
#include <iostream>
using namespace std;

/* 
// This function prints titles and authors of Book objects in an array
// Inputs: an array of Book objects, int number of Book objects in the array
// Returns: nothing
*/ 

void printAllBooks(Book books[], int numberOfBooksInArray)
{
    if (numberOfBooksInArray <= 0)
    {
        cout << "No books are stored" << endl;
    }
    else
    {
        cout << "Here is a list of books" << endl;
        for (int i = 0; i < numberOfBooksInArray; i++)
        {
            cout << books[i].getTitle() << " by " << books[i].getAuthor() << endl;
        }
    }
    
}

int main()
{
    Book books[50];
    string author;
    string title;
    string genre;
    int numberOfBooksInArray = 0;

    cout << "Enter number of books: " << endl;
    cin >> numberOfBooksInArray;
    cin.ignore();
    
    for (int i = 0; i < numberOfBooksInArray; i++)
    {
        cout << "Enter title: " << endl;
        getline(cin, title);
        cout << "Enter author: " << endl;
        getline(cin, author);
        cout << "Enter genre: " << endl;
        getline(cin, genre);
        Book tempBook(title, author, genre);
        books[i] = tempBook;
    }

    printAllBooks(books, numberOfBooksInArray);

    return 0;
}