#include "book.h"
#include "convention.h"
#include "linked.h"
// #include "linked2.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

#define MAX_BOOKS 100

void borrowIt(Book *selected);
// address2 pickWhichBook(Book *books, int *count);
Book *pickWhichBook(Book *books, int count);
void addUser(Book *books, int *count);
void addStok(Book *books, int *count);
void addBook(Book *books, int *count);
void printAll(Book *books, int *count);
void returnBook(Book *books, int *count);
void borrowBook(Book *books, int *count);
void deleteBook(Book *books, int *count);
void deleteStok(Book *books, int *count);
void exitApp(Book *books, int *count);
void printMenu();
address pickWhichUser(Queue *k);
void clearTerminal();

int main() {
  Book books[MAX_BOOKS];
  int count = 0;
  bool isRunning = true;
  void (*tab[])(Book *, int *) = {addUser,    addStok,    addBook,
                                  printAll,   returnBook, borrowBook,
                                  deleteBook, deleteStok, exitApp};
  while (isRunning) {
    printMenu();
    int a;
    printf("\nPilih menu: ");
    scanf("%d", &a);
    if (a >= 1 && a <= 9) {
      tab[a - 1](books, &count);
    }
  }
  return 0;
}

address pickWhichUser(Queue *k) {
  clearTerminal();
  Tampil_List(*k);
  int count = NbElmt(*k);
  printf("Pilih orang yang mana? (1-%d): ", count);
  int a;
  scanf("%d", &a);
  address b = *k;
  for (int i = 1; i < a; i++) {
    b = b->next;
  }
  return b;
}

Book *pickWhichBook(Book *books, int count) {
  clearTerminal();
  for (int i = 0; i < count; i++) {
    printf("%d. [Judul: %s, Stok: %d]\n", i + 1, books[i].title, books[i].stok);
  }
  printf("\nPilih buku yang mana? (1-%d): ", count);
  int a;
  scanf("%d", &a);
  return &books[a - 1];
}

void addBook(Book *books, int *count) {
  clearTerminal();
  if (*count >= MAX_BOOKS) {
    printf("Maximum number of books reached.\n");
    return;
  }
  char kt[MAX_STRING_LENGTH];
  printf("Nama buku (Maksimal 100 char): ");
  scanf("%s", kt);
  int stok;
  printf("Stok: ");
  scanf("%d", &stok);

  Queue users;
  createQueue(&users);
  SLList borrowers;
  createList(&borrowers);

  createBook(&books[*count], kt, stok, &users, &borrowers);
  (*count)++;
}

void addStok(Book *books, int *count) {
  clearTerminal();
  Book *selected = pickWhichBook(books, *count);
  selected->stok += 1;
}

void addUser(Book *books, int *count) {
  clearTerminal();
  Book *selected2 = pickWhichBook(books, *count);
  char orang[MAX_STRING_LENGTH];
  address newNode;
  printf("Nama orang (Max 100 chars): ");
  scanf("%s", orang);
  int pri;
  printf("Level prioritas (1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum): ");
  scanf("%d", &pri);

  Create_Node(&newNode);
  User user;
  createUser(&user, orang, pri);
  Isi_Node_User(&newNode, user);
  insertSortByPriAscendingWrapper(&(selected2->users), newNode);
  if (selected2->stok > 1) {
    borrowIt(selected2);
  }
}

void printAll(Book *books, int *count) {
  bool isRunning = true;
  while (isRunning) {
    clearTerminal();
    for (int i = 0; i < *count; i++) {
      printf("%d. [Judul: %s, Stok: %d]\n", i + 1, books[i].title,
             books[i].stok);
      printf("Antrian: ");
      Tampil_List(books[i].users);
      printf("Sedang Meminjam: ");
      Tampil_List(books[i].borrower);
    }
    char a;
    printf("\nInput q untuk keluar... \n");
    getchar();
    scanf("%c", &a);
    if (a == 'q') {
      isRunning = false;
    }
  }
}

void borrowIt(Book *selected) {
  if (selected->stok > 0) {
    infotype X;
    Dequeue(&selected->users, &X);
    selected->stok -= 1;
    address newNode;
    Create_Node(&newNode);
    Isi_Node_User(&newNode, X.userValue);
    Ins_Awal(&selected->borrower, newNode);
  }
}

void returnBook(Book *books, int *count) {
  clearTerminal();
  Book * selected2 = pickWhichBook(books, *count);
  address selected = pickWhichUser(&selected2->borrower);
  infotype user;
  deleteByAddress(&selected2->borrower, selected, &user);
  selected2->stok += 1;
  if (selected2->stok > 1 && !isEmpty(selected2->users)) {
    borrowIt(selected2);
  }
}

void borrowBook(Book *books, int *count) {
  clearTerminal();
  Book * selected2 = pickWhichBook(books, *count);
  if (selected2->stok > 0 && !isEmpty(selected2->users)) {
    borrowIt(selected2);
  }
}

void deleteBook(Book *books, int *count) {
  clearTerminal();
  Book * selected = pickWhichBook(books, *count);
  DeAlokasi(&selected->users);
  DeAlokasi(&selected->borrower);
  for (int i = (int)(selected - books); i < *count - 1; i++) {
    books[i] = books[i + 1];
  }
  (*count)--;
}

void deleteStok(Book *books, int *count) {
  clearTerminal();
  Book * selected = pickWhichBook(books, *count);
  selected->stok -= 1;
}

void exitApp(Book *books, int *count) {
  for (int i = 0; i < *count; i++) {
    DeAlokasi(&books[i].users);
    DeAlokasi(&books[i].borrower);
  }
  printf("Terima kasih telah menggunakan aplikasi ini.\n");
  exit(0);
}

void clearTerminal() { system("clear"); }

void printMenu() {
  clearTerminal();
  printf("[APLIKASI PEMINJAMAN BUKU]\n");
  printf("(Using array of books)\n");
  printf("1. addUser\n");
  printf("2. addStok\n");
  printf("3. addBook\n");
  printf("4. printAll\n");
  printf("5. returnBook\n");
  printf("6. borrowBook\n");
  printf("7. deleteBook\n");
  printf("8. deleteStok\n");
  printf("9. exitApp\n");
}
