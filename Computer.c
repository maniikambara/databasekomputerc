#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max 100

typedef struct {
    unsigned int IP;
    char nama[50];
    char alamat[100];
} Komputer;

Komputer data[max];
int num = 0;

int fungsiHash(unsigned int IP) {
    return IP % max;
}

void tambahData() {
    if (num >= max) {
        printf("Database full, tidak dapat menambahkan data.\n\n");
        return;
    }

    Komputer baru;
    baru.IP = (rand() % 16777216) | (rand() % 256 << 24);
    sprintf(baru.nama, "Komputer %d", num + 1);
    sprintf(baru.alamat, "Lab %d", num + 1);

    int index = fungsiHash(baru.IP);
    int probe = 1;
    while (data[index].IP != 0) {
        index = (index + probe) % max;
        probe = (probe + 1) % max;
    }
    data[index] = baru;
    num++;

    printf("Data baru ditambah dengan sukses.\n\n");
}

void hapusData() {
    unsigned int IP;
    printf("+-----------------------------------------+\n\n");
    printf("\t\tHAPUS DATA\n\n");
    printf("+-----------------------------------------+\n\n");
    printf("Masukkan IP address untuk dihapus: ");
    scanf("%u", &IP);

    int index = fungsiHash(IP);
    while (data[index].IP != IP && data[index].IP != 0) {
        index = (index + 1) % max;
    }

    if (data[index].IP == 0) {
        printf("IP address tidak ditemukan.\n\n");
        return;
    }

    data[index].IP = 0;
    strcpy(data[index].nama, "");
    strcpy(data[index].alamat, "");
    num--;

    printf("Data telah dihapus dengan sukses.\n\n");
}

void tampilkanData() {
    printf("+-----------------------------------------+\n\n");
    printf("\t       DATA KOMPUTER\n\n");
    printf("+-----------------------------------------+\n\n");
    for (int i = 0; i < max; i++) {
        if (data[i].IP != 0) {
            printf("\t  IP Address: %u.%u.%u.%u\n\t  Nama Komputer: %s\n\t  Alamat: %s\n\n",
                   (data[i].IP >> 24) & 0xFF,
                   (data[i].IP >> 16) & 0xFF,
                   (data[i].IP >> 8) & 0xFF,
                   data[i].IP & 0xFF,
                   data[i].nama, data[i].alamat);
        }
    }
}

int main() {
    srand(time(NULL));

    int pilihan;
    while (1) {
        system("cls");
        printf("+-----------------------------------------+\n\n");
        printf("\t PROGRAM DATABASE KOMPUTER\n\n");
        printf("+-----------------------------------------+\n\n");
        printf("\t     1. Tambahkan Data\n");
        printf("\t     2. Hapus Data\n");
        printf("\t     3. Tampilkan Data\n");
        printf("\t     4. Keluar\n\n");
        printf("+-----------------------------------------+\n\n");
        printf("   I Ketut Manik Ambarawan (2308561017)\n\n");
        printf("\tPILIHAN (1-4) : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                system("cls");
                tambahData();
                system("pause");
                break;
            case 2:
                system("cls");
                hapusData();
                system("pause");
                break;
            case 3:
                system("cls");
                tampilkanData();
                system("pause");
                break;
            case 4:
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                system("pause");
                break;
        }
    }
}