#ifndef book_H
#define book_H
#include "convention.h"
#include "queue.h"
// #include "linked2.h"
typedef struct {
    char title[MAX_STRING_LENGTH];
    int stok;
    Queue users;
    SLList borrower;
}Book;

void createBook(Book *book, char *title, int stok, SLList *users, SLList *borrower);
#endif
