#ifndef stok_H
#define stok_H
#include "convention.h"
// #include "user.h"
#include "linked.h"
#include <stdbool.h>
typedef struct {
    bool av;
    SLList users;
}Stok;

void createStok(Stok *stok, bool av, SLList users) ;
#endif
