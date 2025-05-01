#include "user.h"
#include <string.h>

void createUser(User *user,char *name, int pri) {
    strcpy(user->nm, name);
    user->pri = pri;
}
