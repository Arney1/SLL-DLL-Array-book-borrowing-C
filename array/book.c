#include "book.h"
#include "linked.h"
// #include "linked2.h"
#include <string.h>

void createBook(Book *book, char *title, int stok, Queue *list, SLList *borrower) {
    strcpy(book->title, title);
    book->stok = stok;
    book->users = *list;
    book->borrower = *borrower;
}
