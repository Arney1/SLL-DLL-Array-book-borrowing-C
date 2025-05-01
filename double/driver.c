#include "book.h"
#include "convention.h"
#include "linked.h"
#include "linked2.h"
#include "user.h"
// #include "linked3.h"
// #include "stok.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// address3 pickWhichBook(List3 *k);
void borrowIt(address2 selected);
address2 pickWhichBook(DLList *p);
void addUser(DLList *k);
void addStok(DLList *k);
void addBook(DLList *k);
void printAll(DLList *k);
void returnBook(DLList *k);
void borrowBook(DLList *k);
void deleteBook(DLList *k);
void deleteStok(DLList *k);
// void delete(DLList *k);
void exitApp(DLList *k);
void printMenu();
address pickWhichUser(Queue *k);
void clearTerminal();

int main() {
  DLList k;
  createList2(&k);
  bool isRunning = true;
  void (*tab[])(DLList *) = {addUser,    addStok,    addBook,
                             printAll,   returnBook, borrowBook,
                             deleteBook, deleteStok, exitApp};
  while (isRunning) {
    printMenu();
    int a;
    printf("\nPilih menu: ");
    scanf("%d", &a);
    if (a >= 1 && a <= 6) {
      tab[a - 1](&k);
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

address2 pickWhichBook(DLList *k) {
  clearTerminal();
  Tampil_List2(*k);
  int kotaCount = NbElmt2(*k);
  printf("\nPilih buku yang mana? (1-%d): ", kotaCount);
  int a;
  scanf("%d", &a);
  address2 temp = *k;
  for (int i = 1; i < a; i++) {
    temp = temp->next;
  }
  return temp;
}

void addBook(DLList *k) {
  clearTerminal();
  address2 newNode;
  Create_Node2(&newNode);
  char kt[MAX_STRING_LENGTH];
  printf("Nama buku (Maksimal 100 char): ");
  scanf("%s", kt);
  int stok;
  printf("Stok: ");
  scanf("%d", &stok);
  // Book book;
  Queue users;
  createQueue(&users);
  SLList borrowers;
  createList(&borrowers);
  // createBook(&book, kt, stok);
  // createList2(&(newNode->info.bookValue.stok));
  // DLList stokList;
  // createList2(&stokList);
  Book book;
  createBook(&book, kt, stok, &users, &borrowers);

  Isi_Node_Book(&newNode, book);
  Ins_Akhir2(k, newNode);
  // for (int i = 0; i < stok; i++) {
  //   address2 newNode2;
  //   Create_Node2(&newNode2);
  //   // printf("nana");
  //   // scanf("%d", &stok);
  //   newNode2->info.StokValue.av = true;
  //   createList(&(newNode2->info.StokValue.users));
  //   Ins_Awal2(&(newNode->info.bookValue.stok), newNode2);
  // }
  // Tampil_List3(*k);
}

void addStok(DLList *k) {
  clearTerminal();
  address2 selected = pickWhichBook(k);
  selected->info.bookValue.stok += 1;
}

void addUser(DLList *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  // printf("%d", selected2);
  char orang[MAX_STRING_LENGTH];
  // address2 selected = pickWhichStok(&(selected2->info.bookValue));
  address newNode;
  printf("Nama orang (Max 100 chars): ");
  scanf("%s", orang);
  int pri;
  printf("Level prioritas (1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum): ");
  scanf("%d", &pri);

  Create_Node(&newNode);
  User stok;
  createUser(&stok, orang, pri);
  Isi_Node_User(&newNode, stok);
  // SLList users;
  // createList(&users);
  // createUser(&stok, orang, pri);
  // Isi_Node_User(&newNode, stok);
  // Ins_Akhir(&(selected->info.StokValue.users), newNode);
  insertSortByPriAscendingWrapper(&(selected2->info.bookValue.users), newNode);
  if (selected2->info.bookValue.stok > 1) {
    borrowIt(selected2);
  }
}

void printAll(DLList *p) {

  clearTerminal();
  bool isRunning = true;
  while (isRunning) {

    DLList temp = *p;
    int i = 1;
    while (temp != NULL) {
      printf("%d. [Judul: %s, Stok: %d]\n", i, temp->info.bookValue.title,
             temp->info.bookValue.stok);
      printf("Antrian: ");
      Tampil_List(temp->info.bookValue.users);
      printf("Sedang Meminjam: ");
      Tampil_List(temp->info.bookValue.borrower);

      // int j = 1;
      // address2 temp2 = temp->info.bookValue.stok;

      temp = temp->next;
      // printf("Stok: %d\n", (*p)->info.StokValue.stok);
      // printf("Users:\n");
      // printAllUsers(&(*p)->info.StokValue.users);
      // p = &(*p)->next;
      i++;
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

void borrowIt(address2 selected) {
  // if (selected->info.bookValue.stok > 1)
  infotype X;
  Dequeue(&(selected->info.bookValue.users), &X);
  selected->info.bookValue.stok -= 1;
  address newNode;
  Create_Node(&newNode);
  Isi_Node_User(&newNode, X.userValue);
  Ins_Awal(&(selected->info.bookValue.borrower), newNode);
}

void returnBook(DLList *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  char orang[MAX_STRING_LENGTH];
  address selected = pickWhichUser(&(selected2->info.bookValue.borrower));
  infotype user;
  deleteByAddress(&(selected2->info.bookValue.borrower), selected, &user);
  selected2->info.bookValue.stok += 1;
  if (selected2->info.bookValue.stok > 1 &&
      !isEmpty(selected2->info.bookValue.users)) {
    borrowIt(selected2);
  }

  // address newNode;
  // Create_Node(&newNode);
  // Isi_Node_User(&newNode, user.userValue);
  // Ins_Awal(address *p, address PNew)
}

void borrowBook(DLList *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  if (selected2->info.bookValue.stok > 0 &&
      !isEmpty(selected2->info.bookValue.users)) {
    borrowIt(selected2);
  }
  // Del_Awal(&selected->info.StokValue.users, &user);
}

// void deleteBook(List3 *k) {
//     address3 selected2 = pickWhichBook(k);
//     char orang[MAX_STRING_LENGTH];
//     address2 selected = pickWhichStok(&(selected2->info.bookValue));
//     // infotype user;
//     selected->info.StokValue.av = FALSE;
//     // Del_Awal(&selected->info.StokValue.users, &user);
// }

void deleteStok(DLList *k) {
  address2 selected = pickWhichBook(k);
  selected->info.bookValue.stok -= 1;
}

void deleteBook(DLList *k) {
  address2 selected = pickWhichBook(k);
  // selected->info.bookValue.stok -= 1;
  DeAlokasi(&(selected->info.bookValue.users));
  DeAlokasi(&(selected->info.bookValue.borrower));
}

void exitApp(DLList *k) {
  address2 temp = *k;
  while (temp != NULL) {
    address2 next = temp->next;
    DeAlokasi(&(temp->info.bookValue.users));
    DeAlokasi(&(temp->info.bookValue.borrower));
    free(temp);
    temp = next;
  }
  DeAlokasi2(k);
}
// void deleteKota(DLList *k) {
//   clearTerminal();
//   address2 selected = pickWhichKota(k);
//   DeAlokasi(&(selected->info.p));  // Free orang-orangnya
//   infotype2 dummy;
//   deleteByAddress2(k, selected, &dummy); // Free kota-nya
// }

// void deleteOrang(DLList *k) {
//   clearTerminal();
//   address2 selected = pickWhichKota(k);
//   infotype dummy;
//   deleteByAddress(&(selected->info.p), pickWhichOrang(selected->info),
//   &dummy);
// }

// void printAllkota(DLList *k) {
//   bool isRunning = true;
//   while (isRunning) {
//     clearTerminal();
//     int totalOrang = 0, kotaIndex = 1;
//     for (address2 p = *k; p != NULL; p = p->next) {
//       int jumlah = NbElmt(p->info.p);
//       printf("%d. %s (Jumlah orang: %d)\n", kotaIndex++, p->info.kt.strValue,
//       jumlah); Tampil_List(p->info.p); totalOrang += jumlah;
//     }
//     printf("Jumlah kota: %d\nJumlah orang semua: %d\n", NbElmt2(*k),
//     totalOrang); char a; printf("\nInput q untuk keluar... \n"); getchar();
//     scanf("%c", &a);
//     if (a == 'q') {
//       isRunning = false;
//     }
//   }
// }

// void exitApp(DLList *k) {
//   clearTerminal();
//   for (address2 p = *k; p != NULL; p = p->next) {
//     DeAlokasi(&(p->info.p)); // Hapus semua orang
//   }
//   DeAlokasi2(k); // Hapus semua kota
//   exit(0);
// }

void clearTerminal() { system("clear"); }

void printMenu() {
  clearTerminal();
  printf("[APLIKASI KOTA DAN WARGA]\n");
  printf("(Menggunakan linked list dinamis)\n");
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
