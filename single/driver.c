#include "../convention.h"
// #include "linked.h"
#include "linked.h"
#include "linked2.h"
// #include "linked2.h"
// #include "linked3.h"
// #include "stok.h"
#include "bukuxanggota.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

address2 pickWhichBook(SLList2 *k);
void borrowIt(address2 selected2);

// address2 pickWhichStok(Book *p);

// void addUser(SLList2 *k);

void addUser(SLList2 *k);

void addBook(SLList2 *k);

void printAll(SLList2 *k);

void returnBook(SLList2 *k);

void borrowBook(SLList2 *k);

void deleteBook(SLList2 *k);

void deleteStok(SLList2 *k);
void deleteUser(SLList2 *k);

// void delete(Queue *k);
void exitApp(SLList2 *k);

void printMenu();
address pickWhichUser(Queue *k);
void clearTerminal();

int main() {
  Queue k;
  SLList2 firsts;
  createQueue(&k);
  createList2(&firsts);
  bool isRunning = true;
  void (*tab[])(SLList2 *) = {addUser,    addBook,    printAll,
                              returnBook, borrowBook, deleteBook,
                              deleteStok, deleteUser, exitApp};
  while (isRunning) {
    printMenu();
    int a;
    printf("\nPilih menu: ");
    // getchar();
    scanf("%d", &a);
    if (a >= 1 && a <= 6) {
      tab[a - 1](&firsts);
    }
  }
  return 0;
}

address pickWhichUser(Queue *k) {
  clearTerminal();
  Tampil_User(*k);
  int count = NbAnggota(*k);
  printf("Pilih orang yang mana? (1-%d): ", count);
  int a;
  scanf("%d", &a);
  address b = *k;
  for (int i = 1; i < a; i++) {
    b = b->next;
  }
  return b;
}

address2 pickWhichBook(SLList2 *k) {
  clearTerminal();
  Tampil_Buku2(*k);
  int kotaCount = NbElmt2(*k);
  printf("\nPilih buku yang mana? (1-%d): ", kotaCount);
  int a;
  scanf("%d", &a);
  // printf("debug");
  address2 temp = *k;
  for (int i = 1; i < a; i++) {
    temp = temp->next;
  }
  return temp;
}

// address2 pickWhichStok(Book *k) {
//   clearTerminal();
//   Tampil_List2(k->stok);
//   int kotaCount = NbElmt2(k->stok);
//   printf("\nPilih stok yang mana? (1-%d): ", kotaCount);
//   int a;
//   scanf("%d", &a);
//   address2 temp = k->stok;
//   for (int i = 1; i < a; i++) {
//     temp = temp->next;
//   }
//   return temp;
// }

void addBook(SLList2 *k) {
  clearTerminal();
  address newNode;
  Create_Node(&newNode);
  char kt[MAX_STRING_LENGTH];
  printf("Nama buku (Maksimal 100 char): ");
  scanf("%s", kt);
  int stok = 0;
  while (stok <= 0) {
    printf("Stok: ");
    scanf("%d", &stok);
  }
  strcpy(newNode->info.elemenValue.name, kt);
  Book w;
  createBuku(kt, stok, &w);
  Isi_Node_BookOrAnggota(&newNode, w);
  Queue q;
  createQueue(&q);
  Ins_Akhir(&q, newNode);
  SLList borrowerList;
  createList(&borrowerList);
  address2 newNode2;
  Create_Node2(&newNode2);
  Isi_Node_Queue(&newNode2, q, borrowerList);
  Ins_Akhir2(k, newNode2);
  // createList2(&(newNode->info.bookValue.stok));
  // DLList stokList;
  // createList2(&stokList);
  // Book book;
  // createBook(&book, kt, &stokList);

  // Isi_Node_Book(&newNode, book);
  // Ins_Akhir3(k, newNode);
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

void addStok(SLList2 *k) {
  clearTerminal();
  // address3 selected = pickWhichBook(k);
  // printf("%s", selected->info.bookValue.title);
  // // char orang[MAX_STRING_LENGTH];
  // address2 newNode;
  // // printf("Nama orang (Max 100 chars): ");
  // // scanf("%s", orang);
  // Create_Node2(&newNode);
  // Stok stok;
  // SLList users;
  // createList(&users);
  // createStok(&stok, true, users);
  // Isi_Node_Stok(&newNode, stok);
  // Ins_Akhir2(&(selected->info.bookValue.stok), newNode);
}

void addUser(SLList2 *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  address selected = getBook(selected2->info.queueValue.bookQueue);
  int stokBuku = selected->info.elemenValue.stokOrPriority;
  // printf("%d", selected2);
  char orang[MAX_STRING_LENGTH];
  // address2 selected = pickWhichStok(&(selected2->info.bookValue));
  address newNode;
  printf("Nama orang (Max 100 chars): ");
  scanf("%s", orang);
  int pri;
  printf("Level prioritas (1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum): ");
  scanf("%d", &pri);
  Anggota anggota;
  createAnggota(orang, pri, &anggota);
  Create_Node(&newNode);
  Isi_Node_BookOrAnggota(&newNode, anggota);
  if (stokBuku > 1) {
    // Masih ada stok: langsung pinjam
    selected->info.elemenValue.stokOrPriority -= 1;
    printf("Stok tersedia. Langsung masuk ke borrowerList.\n");
    Ins_Akhir(&(selected2->info.queueValue.borrowerList), newNode);
  } else {
    // Tidak cukup stok: masuk antrean
    printf("Stok habis. Masuk ke antrian.\n");
    Enqueue(&(selected2->info.queueValue.bookQueue), newNode);
  }
  // User stok;
  // SLList users;
  // createList(&users);
  // Enqueue(&(selected2->info.queueValue.bookQueue), newNode);
  // createUser(&stok, orang, pri);
  // Isi_Node_User(&newNode, stok);
  // Ins_Akhir(&(selected->info.StokValue.users), newNode);
}

void printAll(SLList2 *k) {
  clearTerminal();
  bool isRunning = true;
  while (isRunning) {

    SLList2 temp = *k;
    int i = 1;
    while (temp != NULL) {
      printf("%d. Buku: ", i);
      // Tampil_List(temp->info.queueValue.bookQueue);
      Tampil_Buku(temp->info.queueValue.bookQueue);
      printf("\n Antrian user: ");
      // printf("%d. Judul: %s\n", i, temp->info.bookValue.title);
      Tampil_User(temp->info.queueValue.bookQueue);
      // printf()
      printf("Yang sedang meminjam: ");
      Tampil_List(temp->info.queueValue.borrowerList);

      // address book;
      int j = 1;
      // address2 temp2 = temp->info.bookValue.stok;
      // while (temp2 != NULL) {
      //   printf("Stok %d: %s", j,
      //          temp2->info.StokValue.av ? "available\n" : "not available\n");
      //   Tampil_List(temp2->info.StokValue.users);
      //   // (*p)->info.bookValue.stok = (*p)->info.bookValue.stok->next;
      //   temp2 = temp2->next;
      //   j++;
      // }
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

void returnBook(SLList2 *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  // if (selected2 == NULL) {
  //   printf("Buku tidak ditemukan.\n");
  //   return;
  // }

  if (!isEmpty(selected2->info.queueValue.borrowerList)) {
    address user = pickWhichUser(&selected2->info.queueValue.borrowerList);
    // if (user == NULL) {
    //   printf("User tidak ditemukan dalam borrower list.\n");
    //   return;
    // }
    infotype userInfo;
    deleteByAddress(&(selected2->info.queueValue.borrowerList), user,
                    &userInfo);
    address book = getBook(selected2->info.queueValue.bookQueue);
    book->info.elemenValue.stokOrPriority += 1;
    printf("Buku telah dikembalikan.\n");

    if (book->info.elemenValue.stokOrPriority > 1 &&
        (NbElmt(selected2->info.queueValue.bookQueue) - 1) > 0) {
      borrowIt(selected2);
    }
  } else {
    printf("Tidak ada user yang sedang meminjam buku ini.\n");
  }
  char s;
  printf("Input q untuk keluar... \n");
  // getchar();
  scanf("%c", &s);
  // getchar();
}

void borrowIt(address2 selected2) {
  address selected = getBook(selected2->info.queueValue.bookQueue);
  int stokBuku = selected->info.elemenValue.stokOrPriority;
  if (stokBuku > 0 && !isEmpty(selected2->info.queueValue.bookQueue)) {
    address user;
    infotype userInfo;
    Dequeue(&(selected2->info.queueValue.bookQueue), &userInfo);
    Anggota muser = userInfo.elemenValue;
    selected->info.elemenValue.stokOrPriority -= 1;
    address newNode;
    Create_Node(&newNode);
    Isi_Node_BookOrAnggota(&newNode, muser);
    Ins_Akhir(&(selected2->info.queueValue.borrowerList), newNode);
    printf("Buku telah dipinjam.\n");
  } else {
    printf("Tidak ada user dalam antrian atau stok buku habis.\n");
  }
  char s;
  printf("Input q untuk keluar... \n");
  // getchar();
  scanf("%c", &s);
  // getchar();
}

void borrowBook(SLList2 *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  address selected = getBook(selected2->info.queueValue.bookQueue);
  int stokBuku = selected->info.elemenValue.stokOrPriority;

 borrowIt(selected2);
}

// void deleteBook(List3 *k) {
//     address3 selected2 = pickWhichBook(k);
//     char orang[MAX_STRING_LENGTH];
//     address2 selected = pickWhichStok(&(selected2->info.bookValue));
//     // infotype user;
//     selected->info.StokValue.av = FALSE;
//     // Del_Awal(&selected->info.StokValue.users, &user);
// }

void deleteBook(SLList2 *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  if (selected2 == NULL) {
    printf("Buku tidak ditemukan.\n");
    return;
  }

  // if (*k == selected2) {
  //   *k = selected2->next;
  // } else {
  //   address2 temp = *k;
  //   while (temp != NULL && temp->next != selected2) {
  //     temp = temp->next;
  //   }
  //   if (temp == NULL) {
  //     printf("Buku tidak ditemukan.\n");
  //     return;
  //   }
  //   temp->next = selected2->next;
  // }

  address selected = getBook(selected2->info.queueValue.bookQueue);
  DeAlokasi(&(selected2->info.queueValue.bookQueue));
  // while (!isEmpty(selected2->info.queueValue.bookQueue)) {
  //   // address user;
  //   Dequeu(&(selected2->info.queueValue.bookQueue), &user);
  //   // DeAlokasi(&user);
  // }
  // while (!isEmpty(selected2->info.queueValue.borrowerList)) {
  //   address user;
  //   Del_Akhir(&(selected2->info.queueValue.borrowerList), &user);
  //   DeAlokasi(&user);
  // }
  DeAlokasi(&(selected2->info.queueValue.borrowerList));
  // DeAlokasi(&selected);
  // DeAlokasi2(&selected2);
  infotype2 yes;
  deleteByAddress2(k, selected2, &yes);

  printf("Buku telah dihapus.\n");
}
// void deleteBook(SLList2 *k) { printf("wawa"); }

void exitApp(SLList2 *k) {
    address2 temp = *k;
    while (!isEmpty2(temp)) {
        // address2 selected2 = pickWhichBook(k);
        // address selected = getBook(selected2->info.queueValue.bookQueue);
        DeAlokasi(&(temp->info.queueValue.bookQueue));
        DeAlokasi(&(temp->info.queueValue.borrowerList));
        // infotype2 yes;
        // deleteByAddress2(k, selected2, &yes);
        temp = temp->next;
    }
    DeAlokasi2(k);
    exit(0);
}
void deleteStok(SLList2 *k) {
  clearTerminal();
  address2 selected2 = pickWhichBook(k);
  address selected = getBook(selected2->info.queueValue.bookQueue);
  int stokBuku = selected->info.elemenValue.stokOrPriority;
  if (stokBuku > 0) {
    selected->info.elemenValue.stokOrPriority -= 1;
    printf("Stok buku telah dikurangi.\n");
  } else {
    printf("Stok buku sudah habis.\n");
  }
}
void deleteUser(SLList2 *k) { printf("wawa"); }
// void exitApp(SLList2 *k) { printf("wawa"); }
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
  printf("[APLIKASI PEMINJAMAN BUKU]\n");
  printf("(Single Linked List)\n");
  printf("1. addUser\n");
  // printf("2. addStok\n");
  printf("2. addBook\n");
  printf("3. printAll\n");
  printf("4. returnBook\n");
  printf("5. borrowBook\n");
  printf("6. deleteBook\n");
  printf("7. deleteStok\n");
  printf("8. deleteUser\n");
  printf("9. exitApp\n");
}
