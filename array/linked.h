#ifndef linked_H
#define linked_H
#include "convention.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include "user.h"
// typedef int infotype;
typedef union {
    int intValue;
    char strValue[MAX_STRING_LENGTH];
    User userValue;
} infotype;

// typedef User infotype;
typedef struct tElmtList *address;
typedef struct tElmtList {
  infotype info;
  DataType type;
  address next;
} ElmtList;
typedef address SLList;

bool isEmpty(address p);
void Create_Node(address *p);
void createList(address *p);
void Isi_Node_Int(address *p, int nilai);
void Isi_Node_Str(address *p, char *nilai);
void Isi_Node_User(address *p, User user);
void Tampil_List(address p);
void Ins_Awal(address *p, address PNew);
void Ins_Akhir(address *p, address PNew);
address Search_Int(address p, int nilai);
address Search_Str(address p, char *nilai);
void InsertAfter(address *pBef, address PNew);
void Del_Awal(address *p, infotype *X);
void Del_Akhir(address *p, infotype *X);
void Del_After(address *pBef, infotype *X);
void deleteByAddress(address *p, address pDel, infotype *X);
void DeAlokasi(address *p);
int NbElmt(address p);
infotype Min(address p);
infotype Rerata(address p);
address BalikList(address p);
void insertSortByPriAscendingWrapper(SLList *l, address pNew);
void insertSortByPriDescendingWrapper(SLList *l, address pNew);
#endif
