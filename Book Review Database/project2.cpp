#include "User.h"
#include "Book.h"
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
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

/* 
// This function reads from a file and places the contents into an array of Book objects
// Inputs: string of file name, array of Book objects, int number of books stored in array, int size of Book object array
// Returns: int number of books stored
*/ 

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

/* 
// This function adds a User object to a User object array
// Inputs: string of username, an array of User objects, int number of book ratings, int number of User objects stored in the array, int number size of User object array
// Returns: int number of User objects stored in the array
*/

int addUser(string userName, User users[], int numRatings, int numUsersStored, int usersArrSize)
{
    if (numUsersStored >= usersArrSize) //Makes sure the array isn't already full
    {
        return -2;
    }
    for (int i = 0; i < numUsersStored; i++) //Makes sure the username isn't already taken
    {
        if (users[i].getUsername() == userName)
        {
            return -1;
        }
    }
    if (userName == "") //Makes sure the username isn't empty
    {
        return -1;
    }

    users[numUsersStored].setUsername(userName);
    users[numUsersStored].setNumRatings(0);
    numUsersStored++;
    
    return numUsersStored;
}

/* 
// This function reads from a file to fill ratings for User objects
// Inputs: string of file name, User object array, int number of User objects stored in array, int number size of array, int number of max columns (i.e. max ratings)
// Returns: int number of User objects in array
*/

int readRatings(string filename, User users[], int numUsersStored, int usersArrSize, int maxCol)
{
    ifstream in_file;
    string line;
    string temp[50000];
    const char SEPARATOR = ',';
    string tempUsername;
    int tempRatings[50];
    int tempRate;
    int row = numUsersStored;

    in_file.open(filename); //Makes sure the User array isn't already full
    if (numUsersStored >= usersArrSize)
    {
        return -2;
    }
    if (in_file.fail()) //Makes sure the file opened properly
    {
        return -1;
    }

    if (maxCol < 0 || maxCol > 50)
    {
        maxCol = 50;
    }

    while (getline(in_file, line) && numUsersStored < usersArrSize)
    {
        if (line != "") //Makes sure the line isn't empty
        {
            split(line, SEPARATOR, temp, maxCol);
            tempUsername = temp[0];
            users[numUsersStored].setUsername(tempUsername);
            int count = 1;

            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == SEPARATOR)
                {
                    line = line.substr(i + 1, line.length() - i); //This gets rid of the username
                    break;
                }
            }

            split(line, SEPARATOR, temp, maxCol);

            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == SEPARATOR)
                {
                    count++;
                }
            }

            if (count > 50)
            {
                count = 50;
            }

            users[numUsersStored].setNumRatings(count);

            for (int i = 0; i < count; i++)
            {
                tempRate = stoi(temp[i]);
                users[numUsersStored].setRatingAt(i, tempRate);
            }

            numUsersStored++;
        }
    }

    return numUsersStored;
}

/* 
// This function converts a string to all lowercase in order for case insensitive identification
// Inputs: string to convert
// Returns: converted to lowercase string
*/

string toLower(string username)
{
    for (int i = 0; i < username.length(); i++)
    {
        if (username[i] >= 65 && username[i] <= 90)
        username[i] = username[i] + 32;
    }

    return username;
}

/* 
// This function returns a specfic user's rating of a specific book
// Inputs: string of username, string of title, array of User objects, array of Book objects, int number of Users in array, int number of Books in array
// Returns: int number rating of specified user's rating of specified book
*/

int getRating(string username, string title, User users[], Book books[], int numUsers, int numBooks)
{
    username = toLower(username);
    string tempName;
    title = toLower(title);

    for (int i = 0; i < numUsers; i++)
    {
        tempName = users[i].getUsername();
        tempName = toLower(tempName);
        users[i].setUsername(tempName);
    }

    for (int i = 0; i < numBooks; i++)
    {
        tempName = books[i].getTitle();
        tempName = toLower(tempName);
        books[i].setTitle(tempName);
    }

    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].getUsername() == username)
        {
            for (int j = 0; j < numBooks; j++)
            {
                if (books[j].getTitle() == title)
                {
                    return users[i].getRatingAt(j);
                }
            }
        }
    }
    
    return -3;
}

/* 
// This function prints a specfic user's average rating
// Inputs: string of username, array of User objects, int number of Users in array, int number of Books in array
// Returns: abstract integer based on what the function accomplished
*/

int getUserStats(string username, User users[], int numUsersStored, int numBooksStored)
{
    double count = 0;
    double avgTotal = 0;
    double temp;
    double avg;

    for (int i = 0; i < numUsersStored; i++)
    {
        if (users[i].getUsername() == username)
        {
            for (int j = 0; j < numBooksStored; j++)
            {
                if (users[i].getRatingAt(j) != 0)
                {
                    count++;
                    temp = users[i].getRatingAt(j);
                    avgTotal += temp;
                }
            }

            if (count > 0) //Prevents dividing by 0
            {
                avg = avgTotal / count;
            }

            if (count == 0)
            {
                cout << username << " has not rated any books." << endl;
                return 0;
            }
            else
            {
                cout << username << " rated " << fixed << setprecision(0) << count << " books" << endl;
                cout << username << "'s average rating was " << fixed << setprecision(2) << avg << endl;
                return 1;
            }

            count = 0;
            avgTotal = 0;
        }
    }

    cout << username << " does not exist." << endl;
    return -3; 
}

int main()
{
    int option = 1;
    string file;
    Book books[10000];
    int numBooksStored = 0;
    int booksArrSize = 10000;
    int value;
    string genre;
    int count;
    char auth;
    string author;
    string username;
    User users[100];
    int numRatings = 0;
    int numUsersStored = 0;
    const int usersArrSize = 100;
    const int maxCol = 50;
    string title;

    while (option != 9)
    {
        cout << "Select a numerical option:" << endl;
        cout << "======Main Menu=====" << endl;
        cout << "1. Read books from file" << endl;
        cout << "2. Print all books" << endl;
        cout << "3. Book-count by genre" << endl;
        cout << "4. Filter books by genre, author" << endl;
        cout << "5. Add user" << endl;
        cout << "6. Read ratings" << endl;
        cout << "7. Get rating" << endl;
        cout << "8. Get user statistics" << endl;
        cout << "9. Quit" << endl;

        cin >> option;

        if (option < 1 || option > 9)
        {
            cout << "Invalid input." << endl;
        }

        if (option == 1)
        {
            cout << "Enter a book file name: " << endl;
            cin.ignore();
            getline(cin, file);
            value = readBooks(file, books, numBooksStored, booksArrSize);
            
            if (value == -1)
            {
                cout << "No books saved to the database." << endl;
            }
            if (value == -2)
            {
                cout << "Database is already full. Some books may have not been added." << endl;
            }
            if (value >= 0 && value < 50)
            {
                cout << "Total books in the database: " << value << endl;
            }
            if (value == 50)
            {
                cout << "Database is full. Some books may have not been added." << endl;
            }

            numBooksStored = value;
        }

        if (option == 2)
        {
            printAllBooks(books, numBooksStored);
        }

        if (option == 3)
        {
            cout << "Enter the genre: " << endl;
            cin.ignore();
            getline(cin, genre);
            count = countGenre(genre, books, numBooksStored);

            cout << "Total " << genre << " books in the database: " << count << endl;
        }

        if (option == 4)
        {
            cout << "Enter the genre: " << endl;
            cin.ignore();
            getline(cin, genre);
            cout << "Enter first char of author name: " << endl;
            cin >> auth;

            value = printAuthorGenre(genre, auth, books, numBooksStored);
            cout << "Number of titles found for this filter: " << value << endl;
        }

        if (option == 5)
        {
            cout << "Enter a user name: " << endl;
            cin.ignore();
            getline(cin, username);

            value = addUser(username, users, numRatings, numUsersStored, usersArrSize);
            if (value == -2)
            {
                cout << "Database is already full. User cannot be added." << endl;
            }
            if (value == -1)
            {
                cout << "User already exists or the username is empty." << endl;
            }
            if (value >= 0)
            {
                cout << "Welcome, " << username << "!" << endl;
            }
        }

        if (option == 6)
        {
            cout << "Enter the ratings file name: " << endl;
            cin.ignore();
            getline(cin, file);
            value = readRatings(file, users, numUsersStored, usersArrSize, maxCol);
            numUsersStored = value;

            if (value >= 0)
            {
                cout << "Total users in the database: " << numUsersStored << endl;
            }
            if (value == -1)
            {
                cout << "No ratings saved to the database." << endl;
            }
            if (value == -2)
            {
                cout << "Database is already full. No ratings were added." << endl;
            }
            if (value == usersArrSize)
            {
                cout << "Database is full. Some ratings may have not been added." << endl;
            }
        }

        if (option == 7)
        {
            cout << "Enter a user name: " << endl;
            cin.ignore();
            getline(cin, username);
            cout << "Enter a book title: " << endl;
            getline(cin, title);

            value = getRating(username, title, users, books, numUsersStored, numBooksStored);
            
            if (value == -3)
            {
                cout << username << " or " << title << " does not exist." << endl;
            }
            else
            {
                cout << username << " rated " << title << " with " << getRating(username, title, users, books, numUsersStored, numBooksStored) << endl;
            }
        }

        if (option == 8)
        {
            cout << "Enter a user name: " << endl;
            cin.ignore();
            getline(cin, username);

            getUserStats(username, users, numUsersStored, numBooksStored);
        }

        if (option == 9)
        {
            cout << "Good bye!" << endl;
        }
    }

    return 0;   
}