#ifndef linked3_H
#define linked3_H
#include "convention.h"
#include <malloc.h>
#include <stdbool.h>
#include "linked.h"
#include <stdio.h>
#include "linked2.h"
// typedef int infotype;
#include "book.h"
typedef union {
    int intValue;
    char strValue[MAX_STRING_LENGTH];
    Book bookValue;
} infotype3;
// typedef struct {
//     nametype kt;
//     SLList p;
// }kota;
// typedef kota infotype2;
typedef struct tElmtList3 *address3;
typedef struct tElmtList3 {
  infotype3 info;
  DataType type;
  address3 next;
} ElmtList3;
typedef address3 List3;

bool isEmpty3(address3 p);
void Create_Node3(address3 *p);
void createList3(address3 *p);
void Isi_Node_Int3(address3 *p, int nilai);
void Isi_Node_Str3(address3 *p, char *nilai);
void Isi_Node_Book(address3 *p, Book nilai);
void Tampil_List3(address3 p);
void Ins_Awal3(address3 *p, address3 PNew);
void Ins_Akhir3(address3 *p, address3 PNew);
address3 Search_Int3(address3 p, int nilai);
address3 Search_Str3(address3 p, char *nilai);
void InsertAfter3(address3 *pBef, address3 PNew);
void Del_Awal3(address3 *p, infotype3 *X);
void Del_Akhir3(address3 *p, infotype3 *X);
void Del_After3(address3 *pBef, infotype3 *X);
void deleteByAddress3(address3 *p, address3 pDel, infotype3 *X);
void DeAlokasi3(address3 *p);
int NbElmt3(address3 p);
infotype3 Min3(address3 p);
infotype3 Rerata3(address3 p);
address3 BalikList3(address3 p);

#endif
