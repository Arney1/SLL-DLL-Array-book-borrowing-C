#include "stok.h"
#include "linked.h"

void createStok(Stok *stok, bool av, SLList users) {
  stok->av = av;
  stok->users = users;
}
