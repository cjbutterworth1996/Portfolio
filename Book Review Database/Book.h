#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;

class Book
{
public:
    Book();
    Book(string title, string author, string genre);
    string getTitle() const;
    void setTitle(string title1);
    string getAuthor() const;
    void setAuthor(string author1);
    string getGenre() const;
    void setGenre(string genre1);

private:
    string title;
    string author;
    string genre;
};
#endif