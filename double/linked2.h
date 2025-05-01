#ifndef linked2_H
#define linked2_H
#include "convention.h"
#include <malloc.h>
#include <stdbool.h>
#include "linked.h"
#include <stdio.h>
// typedef int infotype;
#include "book.h"
typedef union {
    int intValue;
    char strValue[MAX_STRING_LENGTH];
    Book bookValue;
} infotype2;
// typedef struct {
//     nametype kt;
//     SLList p;
// }kota;
// typedef kota infotype2;
typedef struct tElmtList2 *address2;
typedef struct tElmtList2 {
  infotype2 info;
  DataType type;
  address2 next;
} ElmtList2;
typedef address2 DLList;
void Isi_Node_Book(address2 *p, Book nilai);
bool isEmpty2(address2 p);
void Create_Node2(address2 *p);
void createList2(address2 *p);
void Isi_Node_Int2(address2 *p, int nilai);
void Isi_Node_Str2(address2 *p, char *nilai);
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

#endif
