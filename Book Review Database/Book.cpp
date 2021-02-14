#include "Book.h"
#include <string>
using namespace std;

Book::Book()
{
    title = "";
    author = "";
    genre = "";
}

Book::Book(string title1, string author1, string genre1)
{
    title = title1;
    author = author1;
    genre = genre1;
}

string Book::getTitle() const
{
    return title;
}

void Book::setTitle(string title1)
{
    title = title1;
}

string Book::getAuthor() const
{
    return author;
}

void Book::setAuthor(string author1)
{
    author = author1;
}

string Book::getGenre() const
{
    return genre;
}

void Book::setGenre(string genre1)
{
    genre = genre1;
}