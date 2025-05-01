#include "convention.h"
#include "linked.h"
#include "linked2.h"
// #include "linked3.h"
// #include "stok.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// address3 pickWhichBook(List3 *k);
address2 pickWhichStok(DLList *p);
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
address pickWhichUser(Book *k);
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

address pickWhichUser(Stok *k) {
  clearTerminal();
  Tampil_List(k->users);
  int count = NbElmt(k->users);
  printf("Pilih orang yang mana? (1-%d): ", count);
  int a;
  scanf("%d", &a);
  address b = k->users;
  for (int i = 1; i < a; i++) {
    b = b->next;
  }
  return b;
}

address3 pickWhichBook(List3 *k) {
  clearTerminal();
  Tampil_List3(*k);
  int kotaCount = NbElmt3(*k);
  printf("\nPilih buku yang mana? (1-%d): ", kotaCount);
  int a;
  scanf("%d", &a);
  address3 temp = *k;
  for (int i = 1; i < a; i++) {
    temp = temp->next;
  }
  return temp;
}

address2 pickWhichStok(Book *k) {
  clearTerminal();
  Tampil_List2(k->stok);
  int kotaCount = NbElmt2(k->stok);
  printf("\nPilih stok yang mana? (1-%d): ", kotaCount);
  int a;
  scanf("%d", &a);
  address2 temp = k->stok;
  for (int i = 1; i < a; i++) {
    temp = temp->next;
  }
  return temp;
}

void addBook(List3 *k) {
  clearTerminal();
  address3 newNode;
  Create_Node3(&newNode);
  char kt[MAX_STRING_LENGTH];
  printf("Nama buku (Maksimal 100 char): ");
  scanf("%s", kt);
  int stok;
  printf("Stok: ");
  scanf("%d", &stok);
  strcpy(newNode->info.bookValue.title, kt);
  // createList2(&(newNode->info.bookValue.stok));
  DLList stokList;
  createList2(&stokList);
  Book book;
  createBook(&book, kt, &stokList);

  Isi_Node_Book(&newNode, book);
  Ins_Akhir3(k, newNode);
  for (int i = 0; i < stok; i++) {
    address2 newNode2;
    Create_Node2(&newNode2);
    // printf("nana");
    // scanf("%d", &stok);
    newNode2->info.StokValue.av = true;
    createList(&(newNode2->info.StokValue.users));
    Ins_Awal2(&(newNode->info.bookValue.stok), newNode2);
  }
  Tampil_List3(*k);
}

void addStok(List3 *k) {
  clearTerminal();
  address3 selected = pickWhichBook(k);
  printf("%s", selected->info.bookValue.title);
  // char orang[MAX_STRING_LENGTH];
  address2 newNode;
  // printf("Nama orang (Max 100 chars): ");
  // scanf("%s", orang);
  Create_Node2(&newNode);
  Stok stok;
  SLList users;
  createList(&users);
  createStok(&stok, true, users);
  Isi_Node_Stok(&newNode, stok);
  Ins_Akhir2(&(selected->info.bookValue.stok), newNode);
}

void addUser(List3 *k) {
  clearTerminal();
  address3 selected2 = pickWhichBook(k);
  // printf("%d", selected2);
  char orang[MAX_STRING_LENGTH];
  address2 selected = pickWhichStok(&(selected2->info.bookValue));
  address newNode;
  printf("Nama orang (Max 100 chars): ");
  scanf("%s", orang);
  int pri;
  printf("Level prioritas (1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum): ");
  scanf("%d", &pri);

  Create_Node(&newNode);
  User stok;
  SLList users;
  createList(&users);
  createUser(&stok, orang, pri);
  Isi_Node_User(&newNode, stok);
  Ins_Akhir(&(selected->info.StokValue.users), newNode);
}

void printAll(List3 *p) {
  bool isRunning = true;
  while (isRunning) {

    List3 temp = *p;
    int i = 1;
    while (temp != NULL) {
      printf("%d. Judul: %s\n", i, temp->info.bookValue.title);
      int j = 1;
      address2 temp2 = temp->info.bookValue.stok;
      while (temp2 != NULL) {
        printf("Stok %d: %s", j,
               temp2->info.StokValue.av
                   ? "available\n"
                   : "not available\n");
        Tampil_List(temp2->info.StokValue.users);
        // (*p)->info.bookValue.stok = (*p)->info.bookValue.stok->next;
        temp2 = temp2->next;
        j++;
      }
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

void returnBook(List3 *k) {
  clearTerminal();
  address3 selected2 = pickWhichBook(k);
  char orang[MAX_STRING_LENGTH];
  address2 selected = pickWhichStok(&(selected2->info.bookValue));
  infotype user;
  selected->info.StokValue.av = true;
  Del_Awal(&selected->info.StokValue.users, &user);
  printf("%s\n telah mengembalikan buku %s\n", user.userValue.nm,
         selected2->info.bookValue.title);
  // address newNode;
  // printf("Nama orang (Max 100 chars): ");
  // scanf("%s", orang);
  // int pri;
  // printf("Level prioritas (1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum):
  // "); scanf("%d", &pri);

  // Create_Node(&newNode);
  // User stok;
  // SLList users;
  // createList(&users);
  // createUser(&stok, orang, pri);
  // Isi_Node_User(&newNode, stok);
  // Ins_Akhir(&(selected->info.StokValue.users), newNode);
  // address selectedUser = pickWhichUser(&(selected->info.StokValue));
}

void borrowBook(List3 *k) {
  address3 selected2 = pickWhichBook(k);
  char orang[MAX_STRING_LENGTH];
  address2 selected = pickWhichStok(&(selected2->info.bookValue));
  // infotype user;
  selected->info.StokValue.av = false;
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

void deleteStok(List3 *k) { printf("wawa"); }

void deleteBook(List3 *k) { printf("wawa"); }

void exitApp(List3 *k) { printf("wawa"); }
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
