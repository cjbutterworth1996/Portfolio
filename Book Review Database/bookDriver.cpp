#include "Book.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
    Book book1;
    Book book2("The Hobbit", "Tolkien", "Fantasy");
    string title;
    string author;
    string genre;

    cout << book1.getTitle() << book1.getAuthor() << book1.getGenre() << endl;
    cout << book2.getTitle() << book2.getAuthor() << book2.getGenre() << endl;

    cout << "Enter title: " << endl;
    getline(cin, title);
    cout << "Enter author: " << endl;
    getline(cin, author);
    cout << "Enter genre: " << endl;
    getline (cin, genre);

    book1.setTitle(title);
    book1.setAuthor(author);
    book1.setGenre(genre);

    cout << book1.getTitle() << book1.getAuthor() << book1.getGenre() << endl;

    return 0;
}