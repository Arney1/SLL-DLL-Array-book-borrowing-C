#ifndef book_H
#define book_H
#include "convention.h"
// #include "linked.h"
#include "linked2.h"
typedef struct {
    char title[MAX_STRING_LENGTH];
    DLList stok;
}Book;

void createBook(Book *book, char *title, DLList *list);
#endif
