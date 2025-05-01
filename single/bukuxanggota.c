#include "bukuxanggota.h"
#include <string.h>

void createBuku(char* judul, int stok, Book* buku) {
    strcpy(buku->name, judul);
    buku->stokOrPriority = stok;
    buku->type = BUKU;
}
void createAnggota(char* judul, int stok, Anggota* buku) {
    strcpy(buku->name, judul);
    buku->stokOrPriority = stok;
    buku->type = ANGGOTA;
}
