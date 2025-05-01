#include "linked2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isEmpty2(address2 p) {
  // if (p == NULL) {
  //   return true;
  // }
  // return false;
  return (p == NULL);
}

void createList2(address2 *p) { *p = NULL; }

void Create_Node2(address2 *p) {
  *p = (address2)malloc(sizeof(ElmtList2));
  // if (*p == NULL) {
  //     *p = NULL;
  // }
}

void Isi_Node_Int2(address2 *p, int nilai) {
  if (*p != NULL) {
    (**p).info.intValue = nilai;
    // (**p).info. = NULL;
    (**p).type = INTEGER;
    (**p).next = NULL;
  }
}

void Isi_Node_Str2(address2 *p, char *nilai) {
  if (*p != NULL) {
    strcpy((**p).info.strValue, nilai);
    // (**p).info.StokValue.users = NULL;
    (**p).type = STRING;
    (**p).next = NULL;
  }
}

void Isi_Node_Book(address2 *p, Book nilai) {
  if (*p != NULL) {
    (**p).info.bookValue.stok = nilai.stok;
    (**p).info.bookValue.borrower = nilai.borrower;
    (**p).info.bookValue.users = nilai.users;
    (**p).type = BOOK;
    // (**p).info. = STOK;
    strcpy((*p)->info.bookValue.title, nilai.title);
    // (**p).next = NULL;
  }
}

void Tampil_List2(address2 p) {
  // while (!isEmpty(p)) {
  //   printf("%d -> ", p->info);
  //   p = p->next;
  // }
  // printf("NULL\n");
  if (isEmpty2(p)) {
    printf("NULL\n");
  } else {
    if ((*p).type == STRING) {
      printf("%s -> ", (*p).info.strValue);
      Tampil_List2((*p).next);
    } else if ((*p).type == INTEGER) {
      printf("%d -> ", (*p).info.intValue);
      Tampil_List2((*p).next);
    } else if ((*p).type == BOOK) {
      printf("[Judul: %s, Stok: %d] -> ", (*p).info.bookValue.title, (*p).info.bookValue.stok);
      Tampil_List2((*p).next);
    }
  }
}

void Ins_Awal2(address2 *p, address2 PNew) {
  (*PNew).next = *p;
  *p = PNew;
}

void Ins_Akhir2(address2 *p, address2 PNew) {
  if (isEmpty2(*p)) {
    *p = PNew;
  } else {
    address2 temp = *p;
    while (!isEmpty2((*temp).next)) {
      temp = (*temp).next;
    }
    (*temp).next = PNew;
  }
}

address2 Search_Int2(address2 p, int nilai) {
  while (!isEmpty2(p)) {
    if ((*p).info.intValue == nilai) {
      return p;
    }
    p = (*p).next;
  }
  return NULL;
}
address2 Search_Str2(address2 p, char *nilai) {
  while (!isEmpty2(p)) {
    if (strcmp((*p).info.strValue, nilai) == 0) {
      return p;
    }
    p = (*p).next;
  }
  return NULL;
}

void InsertAfter2(address2 *pBef, address2 PNew) {
  (*PNew).next = (**pBef).next;
  (**pBef).next = PNew;
}

void Del_Awal2(address2 *p, infotype2 *X) {
  if (!isEmpty2(*p)) {
    if ((*p)->type == STRING) {
      strcpy(X->strValue, (**p).info.strValue);
    } else if ((*p)->type == INTEGER) {
      X->intValue = (**p).info.intValue;
    } else {
        *X = (*p)->info;
    }
    // X-> = NULL;
    address2 temp = *p;
    *p = (**p).next;
    (*temp).next = NULL;
    free(temp);
  }
}

void deleteByAddress2(address2 *p, address2 pDel, infotype2 *X) {
  if (isEmpty2(*p) || isEmpty2(pDel))
    return;

  if (*p == pDel) {
    Del_Awal2(p, X);
  } else {
    address2 temp = *p;
    while (temp->next != NULL && temp->next != pDel) {
      temp = temp->next;
    }

    if (temp->next == pDel) {
      Del_After2(&temp, X);
    }
  }
}

void Del_Akhir2(address2 *p, infotype2 *X) {
  if (!isEmpty2(*p)) {
    if (isEmpty2((**p).next)) {
      printf("yellow!");
      *X = (**p).info;
      free(*p);
      *p = NULL;
    } else {
      address2 prev;
      address2 last = *p;
      while (!isEmpty2((*last).next)) {
        prev = last;
        last = (*last).next;
      }
      *X = (*last).info;
      free(last);
      (*prev).next = NULL;
    }
  }
}

void Del_After2(address2 *pBef, infotype2 *X) {
  address2 temp = (**pBef).next;
  // *X = (**pBef).info;
  (**pBef).next = (*temp).next;
  *X = (*temp).info;
  (*temp).next = NULL;
  free(temp);
}

void DeAlokasi2(address2 *p) {
  while (!isEmpty2(*p)) {
    infotype2 i;
    Del_Awal2(p, &i);
  }
}

int NbElmt2(address2 p) {
  // int sum = 0;
  // while (!isEmpty(p)) {
  //     sum += 1;
  //     p = (*p).next;
  // }
  // return sum;
  if (isEmpty2(p)) {
    return 0;
  } else {
    return 1 + NbElmt2((*p).next);
  }
}

// infotype Min(address p) {
//   int Min = (*p).info;
//   p = (*p).next;
//   while (!isEmpty(p)) {
//     if ((*p).info < Min) {
//       Min = (*p).info;
//     }
//     p = (*p).next;
//   }
//   return Min;
// }

// infotype Rerata(address p) {
//   int sum = 0, count = 0;
//   while (!isEmpty(p)) {
//     sum += (*p).info;
//     count++;
//     p = (*p).next;
//   }
//   return (count != 0) ? sum / count : 0;
// }

address2 BalikList2(address2 p) {
  if (!isEmpty2(p)) {
    address2 prev = NULL;
    address2 this = p;
    address2 next = (*p).next;
    while (!isEmpty2(next)) {
      (*this).next = prev;
      prev = this;
      this = next;
      next = (*this).next;
    }
    (*this).next = prev;
    p = this;
  }
  return p;
}
