#ifndef linked2_H
#define linked2_H
#include "../convention.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
// #include "bukuxanggota.h"
#include "queue.h"
// typedef int infotype
typedef struct {
    Queue bookQueue;
    SLList borrowerList;
} bookQueue;
typedef union {
    int intValue;
    char strValue[MAX_STRING_LENGTH];
    bookQueue queueValue;
} infotype2;
// typedef User infotype;
typedef struct tElmtList2 *address2;
typedef struct tElmtList2 {
  infotype2 info;
  DataType type;
  address2 next;
} ElmtList2;
typedef address2 SLList2;

bool isEmpty2(address2 p);
void Create_Node2(address2 *p);
void createList2(address2 *p);
void Isi_Node_Int2(address2 *p, int nilai);
void Isi_Node_Str2(address2 *p, char *nilai);
// void Isi_Node_User(address2 *p, User user);
// void Isi_Node_BookOrAnggota(address2 *p, struct Element elemen);

void Isi_Node_Queue(address2 *p, Queue bookQueue, SLList borrowerQueue);
void Tampil_List2(address2 p);
void Ins_Awal2(address2 *p, address2 PNew);
void Ins_Akhir2(address2 *p, address2 PNew);
address2 Search_Int2(address2 p, int nilai);
address2 Search_Str2(address2 p, char *nilai);
void InsertAfter2(address2 *pBef, address2 PNew);
void Del_Awal2(address2 *p, infotype2 *X);
void Del_Akhir2(address2 *p, infotype2 *X);
void Del_After2(address2 *pBef, infotype2 *X);
void deleteByAddress2(address2 *p, address2 pDel, infotype2 *X);
void DeAlokasi2(address2 *p);
int NbElmt2(address2 p);
infotype2 Min2(address2 p);
infotype2 Rerata2(address2 p);
address2 BalikList2(address2 p);
void Tampil_Buku2(address2 k);
#endif
