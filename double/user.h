#ifndef user_H
#define user_H
#include "convention.h"
// #include "linked.h"
typedef struct {
    char nm[MAX_STRING_LENGTH];
    int pri;
}User;
void createUser(User *user,char *name, int pri);
#endif
