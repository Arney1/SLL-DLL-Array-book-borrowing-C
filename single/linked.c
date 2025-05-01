#include "linked.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isEmpty(address p) {
  // if (p == NULL) {
  //   return true;
  // }
  // return false;
  return (p == NULL);
}

void createList(address *p) { *p = NULL; }

void Create_Node(address *p) {
  *p = (address)malloc(sizeof(ElmtList));
  // if (*p == NULL) {
  //     *p = NULL;
  // }
}

void Isi_Node_Int(address *p, int nilai) {
  if (*p != NULL) {
    (**p).info.intValue = nilai;
    (**p).type = INTEGER;
    (**p).next = NULL;
  }
}

void Isi_Node_Str(address *p, char *nilai) {
  if (*p != NULL) {
    strcpy((**p).info.strValue, nilai);
    (**p).type = STRING;
    (**p).next = NULL;
  }
}

int compareDescending(int a, int b) { return a - b; }

int compareAscending(int a, int b) { return b - a; }

void insertAnggotaSortedByPri(address *headRef, address pNew,
                              int (*cmp)(int, int)) {
  if (pNew == NULL)
    return; // Don't insert NULL node

  // If list is empty or pNew has higher priority than head
  if (*headRef == NULL ||
      cmp(pNew->info.elemenValue.stokOrPriority,
          (*headRef)->info.elemenValue.stokOrPriority) > 0) {
    pNew->next = *headRef;
    *headRef = pNew;
    return;
  }

  address curr = *headRef;
  address prev = NULL;

  // Traverse the list to find the correct position for pNew
  while (curr != NULL && cmp(pNew->info.elemenValue.stokOrPriority,
                             curr->info.elemenValue.stokOrPriority) < 0) {
    prev = curr;
    curr = curr->next;
  }

  // If we reached the end of the list, insert pNew as the new last node
  if (curr == NULL) {
    prev->next = pNew;
    pNew->next = NULL;
  } else {
    // Insert pNew before curr
    pNew->next = curr;
    if (prev != NULL) {
      prev->next = pNew;
    } else {
      *headRef = pNew; // If pNew is the new head
    }
  }
}

void insertAnggotaSortDescendingByPriWrapper(address *l, address pNew) {
  insertAnggotaSortedByPri(l, pNew, compareDescending);
}
void insertAnggotaSortAscendingByPriWrapper(address *l, address pNew) {
  insertAnggotaSortedByPri(l, pNew, compareAscending);
}

// void Isi_Node_User(address *p, User user) {
//   if (*p != NULL) {
//     (**p).info.userValue = user;
//     (**p).type = USER;
//     (**p).next = NULL;
//   }
// }
void Isi_Node_BookOrAnggota(address *p, struct Element elemen) {
  if (*p != NULL) {
    (**p).info.elemenValue = elemen;
    (**p).type = ELEMEN;
    (**p).next = NULL;
  }
}

void Tampil_List(address p) {
  // while (!isEmpty(p)) {
  //   printf("%d -> ", p->info);
  //   p = p->next;
  // }
  // printf("NULL\n");
  if (isEmpty(p)) {
    printf("NULL\n");
  } else {
    if ((*p).type == STRING) {
      printf("%s -> ", (*p).info.strValue);
      Tampil_List((*p).next);
    } else if (p->type == INTEGER) {
      printf("%d -> ", (*p).info.intValue);
      Tampil_List((*p).next);
    } else if ((*p).type == ELEMEN) {
      printf("[%s, %i] -> ", (*p).info.elemenValue.name,
             (*p).info.elemenValue.stokOrPriority);
      Tampil_List((*p).next);
    }
  }
}

void Tampil_User(address p) {
  // while (!isEmpty(p)) {
  //   printf("%d -> ", p->info);
  //   p = p->next;
  // }
  // printf("NULL\n");
  if (isEmpty(p)) {
    printf("NULL\n");
  } else if (p->info.elemenValue.type == BUKU) {
    printf("Buku");
    printf("\n");
  } else {
    if (p->info.elemenValue.type == ANGGOTA) {
      printf("[%s, %i] -> ", (*p).info.elemenValue.name,
             (*p).info.elemenValue.stokOrPriority);
      Tampil_User((*p).next);
    }
    // if ((*p).type == STRING) {
    //   printf("%s -> ", (*p).info.strValue);
    //   Tampil_List((*p).next);
    // } else if (p->type == INTEGER){
    //   printf("%d -> ", (*p).info.intValue);
    //   Tampil_List((*p).next);
    // } else if ((*p).type == ELEMEN){
    //   printf("[%s, %i] -> ", (*p).info.elemenValue.name,
    //   (*p).info.elemenValue.stokOrPriority); Tampil_List((*p).next);
    // }
  }
}
void Tampil_Buku(address p) {
  if (!isEmpty(p)) {

    while (!isEmpty(p->next)) {
      // printf("%d -> ", p->info);
      p = p->next;
    }
    printf("[%s, %i]", p->info.elemenValue.name,
           p->info.elemenValue.stokOrPriority);
  }
  // printf("NULL\n");
  // // if (isEmpty(p)) {
  //   printf("NULL\n");
  // } else if (p->info.elemenValue.type == BUKU) {
  //   printf("Buku: [Judul: %s, Stok: %i] -> ", p->info.elemenValue.name,
  //          p->info.elemenValue.stokOrPriority);
  //   printf("\n");
  // } else {
  //   if (p->info.elemenValue.type == ANGGOTA) {
  //     printf("[%s, %i] -> ", (*p).info.elemenValue.name,
  //            (*p).info.elemenValue.stokOrPriority);
  //     Tampil_User((*p).next);
  //   }
  // if ((*p).type == STRING) {
  //   printf("%s -> ", (*p).info.strValue);
  //   Tampil_List((*p).next);
  // } else if (p->type == INTEGER){
  //   printf("%d -> ", (*p).info.intValue);
  //   Tampil_List((*p).next);
  // } else if ((*p).type == ELEMEN){
  //   printf("[%s, %i] -> ", (*p).info.elemenValue.name,
  //   (*p).info.elemenValue.stokOrPriority); Tampil_List((*p).next);
  // }
}

void Ins_Awal(address *p, address PNew) {
  (*PNew).next = *p;
  *p = PNew;
}

void Ins_Akhir(address *p, address PNew) {
  if (isEmpty(*p)) {
    *p = PNew;
  } else {
    address temp = *p;
    while (!isEmpty((*temp).next)) {
      temp = (*temp).next;
    }
    (*temp).next = PNew;
  }
}

address Search_Int(address p, int nilai) {
  while (!isEmpty(p)) {
    if ((*p).info.intValue == nilai) {
      return p;
    }
    p = (*p).next;
  }
  return NULL;
}
address Search_Str(address p, char *nilai) {
  while (!isEmpty(p)) {
    if (strcmp((*p).info.strValue, nilai)) {
      return p;
    }
    p = (*p).next;
  }
  return NULL;
}

void InsertAfter(address *pBef, address PNew) {
  (*PNew).next = (**pBef).next;
  (**pBef).next = PNew;
}

void Del_Awal(address *p, infotype *X) {
  if (!isEmpty(*p)) {
    *X = (**p).info;
    address temp = *p;
    *p = (**p).next;
    (*temp).next = NULL;
    free(temp);
    // DeAlokasi(&temp);
  }
}

void deleteByAddress(address *p, address pDel, infotype *X) {
  if (isEmpty(*p) || isEmpty(pDel))
    return;

  if (*p == pDel) {
    Del_Awal(p, X);
  } else {
    address temp = *p;
    while (temp->next != NULL && temp->next != pDel) {
      temp = temp->next;
    }

    if (temp->next == pDel) {
      Del_After(&temp, X);
    }
  }
}

void Del_Akhir(address *p, infotype *X) {
  if (!isEmpty(*p)) {
    if (isEmpty((**p).next)) {
      printf("yellow!");
      *X = (**p).info;
      free(*p);
      *p = NULL;
    } else {
      address prev;
      address last = *p;
      while (!isEmpty((*last).next)) {
        prev = last;
        last = (*last).next;
      }
      *X = (*last).info;
      free(last);
      (*prev).next = NULL;
    }
  }
}

address getBook(address p) {
  address book = NULL;
  while (p != NULL) {
    if (p->info.elemenValue.type == BUKU) {
      book = p;
      break;
    }
    p = p->next;
  }
  return book;
}

void Del_User_Akhir(address *p, infotype *X) {
  if (!isEmpty(*p)) {
    if ((*p)->next == NULL) {
      // If the list has only one or two nodes
      printf("Cannot delete the second last node.\n");
      return;
    } else if ((*p)->next->next == NULL) {
      Del_Awal(p, X);
    } else {
      // Traverse to the node before the second last
      address prev = NULL;
      address current = *p;

      while (current->next->next->next != NULL) {
        current = current->next;
      }

      address secondLast = current->next;
      *X = secondLast->info;
      current->next = secondLast->next;
      free(secondLast);
    }
  } else {
    printf("List is empty.\n");
  }
}

void Del_After(address *pBef, infotype *X) {
  address temp = (**pBef).next;
  // *X = (**pBef).info;
  (**pBef).next = (*temp).next;
  *X = (*temp).info;
  (*temp).next = NULL;
  free(temp);
}

void DeAlokasi(address *p) {
  while (!isEmpty(*p)) {
    infotype i;
    Del_Awal(p, &i);
  }
}

int NbElmt(address p) {
  // int sum = 0;
  // while (!isEmpty(p)) {
  //     sum += 1;
  //     p = (*p).next;
  // }
  // return sum;
  if (isEmpty(p)) {
    return 0;
  } else {
    return 1 + NbElmt((*p).next);
  }
}
int NbAnggota(address p) {
  // int sum = 0;
  // while (!isEmpty(p)) {
  //     sum += 1;
  //     p = (*p).next;
  // }
  // return sum;
  if (isEmpty(p) || p->info.elemenValue.type == BUKU) {
    return 0;
  } else {
    return 1 + NbElmt((*p).next);
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

address BalikList(address p) {
  if (!isEmpty(p)) {
    address prev = NULL;
    address this = p;
    address next = (*p).next;
    while (!isEmpty(next)) {
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
