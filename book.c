#include "book.h"
#include "linked2.h"
#include <string.h>

void createBook(Book *book, char *title, DLList *list) {
    strcpy(book->title, title);
    book->stok = *list;
}
