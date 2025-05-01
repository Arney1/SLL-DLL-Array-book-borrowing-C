#include "linked3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isEmpty3(address3 p) {
  // if (p == NULL) {
  //   return true;
  // }
  // return false;
  return (p == NULL);
}

void createList3(address3 *p) { *p = NULL; }

void Create_Node3(address3 *p) {
  *p = (address3)malloc(sizeof(ElmtList3));
  // if (*p == NULL) {
  //     *p = NULL;
  // }
}

void Isi_Node_Int3(address3 *p, int nilai) {
  if (*p != NULL) {
    (**p).info.intValue = nilai;
    // (**p).info. = NULL;
    (**p).type = INTEGER;
    (**p).next = NULL;
  }
}

void Isi_Node_Str3(address3 *p, char *nilai) {
  if (*p != NULL) {
    strcpy((**p).info.strValue, nilai);
    // (**p).info.StokValue.users = NULL;
    (**p).type = STRING;
    (**p).next = NULL;
  }
}

void Isi_Node_Book(address3 *p, Book nilai) {
  if (*p != NULL) {
    strcpy((**p).info.bookValue.title, nilai.title);
        // (**p).info.bookValue.title = nilai.title;
    (**p).info.bookValue.stok = NULL;
    (**p).type = STOK;
    (**p).next = NULL;
  }
}

void Tampil_List3(address3 p) {
  // while (!isEmpty(p)) {
  //   printf("%d -> ", p->info);
  //   p = p->next;
  // }
  // printf("NULL\n");
  if (isEmpty3(p)) {
    printf("NULL\n");
  } else {
    if ((*p).type == STRING) {
      printf("%s -> ", (*p).info.strValue);
      Tampil_List3((*p).next);
    } else if ((*p).type == INTEGER) {
      printf("%d -> ", (*p).info.intValue);
      Tampil_List3((*p).next);
    } else if ((*p).type == STOK) {
      printf("%s -> ", (*p).info.bookValue.title);
      Tampil_List3((*p).next);
    }
  }
}

void Ins_Awal3(address3 *p, address3 PNew) {
  (*PNew).next = *p;
  *p = PNew;
}

void Ins_Akhir3(address3 *p, address3 PNew) {
  if (isEmpty3(*p)) {
    *p = PNew;
  } else {
    address3 temp = *p;
    while (!isEmpty3((*temp).next)) {
      temp = (*temp).next;
    }
    (*temp).next = PNew;
  }
}

address3 Search_Int3(address3 p, int nilai) {
  while (!isEmpty3(p)) {
    if ((*p).info.intValue == nilai) {
      return p;
    }
    p = (*p).next;
  }
  return NULL;
}
address3 Search_Str3(address3 p, char *nilai) {
  while (!isEmpty3(p)) {
    if (strcmp((*p).info.strValue, nilai) == 0) {
      return p;
    }
    p = (*p).next;
  }
  return NULL;
}

void InsertAfter3(address3 *pBef, address3 PNew) {
  (*PNew).next = (**pBef).next;
  (**pBef).next = PNew;
}

void Del_Awal3(address3 *p, infotype3 *X) {
  if (!isEmpty3(*p)) {
    if ((*p)->type == STRING) {
      strcpy(X->strValue, (**p).info.strValue);
    } else if ((*p)->type == INTEGER) {
      X->intValue = (**p).info.intValue;
    } else {
        strcpy(X->bookValue.title, (*p)->info.bookValue.title);
        X->bookValue.stok = (*p)->info.bookValue.stok;
    }
    // X-> = NULL;
    address3 temp = *p;
    *p = (**p).next;
    (*temp).next = NULL;
    free(temp);
  }
}

void deleteByaddress3(address3 *p, address3 pDel, infotype3 *X) {
  if (isEmpty3(*p) || isEmpty3(pDel))
    return;

  if (*p == pDel) {
    Del_Awal3(p, X);
  } else {
    address3 temp = *p;
    while (temp->next != NULL && temp->next != pDel) {
      temp = temp->next;
    }

    if (temp->next == pDel) {
      Del_After3(&temp, X);
    }
  }
}

void Del_Akhir3(address3 *p, infotype3 *X) {
  if (!isEmpty3(*p)) {
    if (isEmpty3((**p).next)) {
      // printf("yellow!");
      if ((*p)->type == STRING) {
            strcpy(X->strValue, (**p).info.strValue);
          } else if ((*p)->type == INTEGER) {
            X->intValue = (**p).info.intValue;
          } else {
              strcpy(X->bookValue.title, (*p)->info.bookValue.title);
              X->bookValue.stok = (*p)->info.bookValue.stok;
          }
      free(*p);
      *p = NULL;
    } else {
      address3 prev;
      address3 last = *p;
      while (!isEmpty3((*last).next)) {
        prev = last;
        last = (*last).next;
      }
      *X = (*last).info;
      free(last);
      (*prev).next = NULL;
    }
  }
}

void Del_After3(address3 *pBef, infotype3 *X) {
  address3 temp = (**pBef).next;
  // *X = (**pBef).info;
  (**pBef).next = (*temp).next;
  *X = (*temp).info;
  (*temp).next = NULL;
  free(temp);
}

void DeAlokasi3(address3 *p) {
  while (!isEmpty3(*p)) {
    infotype3 i;
    Del_Awal3(p, &i);
  }
}

int NbElmt3(address3 p) {
  // int sum = 0;
  // while (!isEmpty(p)) {
  //     sum += 1;
  //     p = (*p).next;
  // }
  // return sum;
  if (isEmpty3(p)) {
    return 0;
  } else {
    return 1 + NbElmt3((*p).next);
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

address3 BalikList3(address3 p) {
  if (!isEmpty3(p)) {
    address3 prev = NULL;
    address3 this = p;
    address3 next = (*p).next;
    while (!isEmpty3(next)) {
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
