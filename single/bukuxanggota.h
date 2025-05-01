#ifndef BUKUXANGGOTA_H
#define BUKUXANGGOTA_H

#include "../convention.h"

typedef enum {
    BUKU,
    ANGGOTA
} dataType;

typedef struct Element{
    char name[MAX_STRING_LENGTH];
    int stokOrPriority; //1 = Dosen, 2 = Mahasiswa, 3 = Masyarakat Umum
    dataType type;
} Book, Anggota;

#endif
