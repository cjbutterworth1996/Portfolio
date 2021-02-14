#include "Book.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/* 
// This function splits strings into substrings using a separating character
// Inputs: string to split, character that acts as a separator, an array of strings, int of array size
// Returns: int count of number of splits
*/ 

int split(string split, char separator, string array[], int size)
{
    int position1 = 0; // start of substring
    int position2 = 0; // number of spaces for substring
    int j = 0; // array position
    int count = 1; // count number of splits, set to 1 because if no splits, the entire string gets set to the first array indice

    if (split.length() == 0)
    {
        return 0; // this ensures that the user is not trying to split a 1 character string
    }
    
    for (int i = 0; i < split.length() - 1; i++)
    {
        if (split[i] == separator)
        {
            position2 = i;
            array[j] = split.substr(position1, position2 - position1);
            position1 = position2 + 1;
            j++;
            count++;
        }
    }
    array[j] = split.substr(position1, split.length() - 1);

    if (position1 == 0)
    {
        array[j] = split;
    }
    if (count > size)
    {
        return -1;
    }

    return count;
}

int readBooks(string fileName, Book books[], int numBooksStored, int booksArrSize)
{
    string arr[50];
    ifstream in_file;
    string line;
    string title;
    string author;
    string genre;
    const int NUMBER_OF_BOOK_DESCRIPTORS = 3;
    const char SEPARATOR = ',';
    in_file.open(fileName);
    if (numBooksStored == booksArrSize) //Makes sure the array isn't already full
    {
        return -2;
    }
    if (in_file.fail()) //Makes sure the file opened properly
    {
        return -1;
    }
    
    while (getline(in_file, line) && numBooksStored < booksArrSize)
    {
        if (line != "") //Makes sure the line isn't empty
        {
            split(line, SEPARATOR, arr, NUMBER_OF_BOOK_DESCRIPTORS);
            author = arr[0];
            title = arr[1];
            genre = arr[2];
            Book tempBook(title, author, genre);
            books[numBooksStored] = tempBook;
            numBooksStored++;
        }
    }

    in_file.close();
    return numBooksStored;
}

int main()
{
    string fileName;
    Book books[50];
    int numberOfBooksStored = 0;
    int booksArrSize = 50;

    cout << "Enter name of file: " << endl;
    getline(cin, fileName);

    numberOfBooksStored = readBooks(fileName, books, numberOfBooksStored, booksArrSize);
    
    for (int i = 0; i < numberOfBooksStored; i++)
    {
        cout << books[i].getTitle() << " " << books[i].getAuthor() << " " << books[i].getGenre() << endl;
    }

    return 0;
}