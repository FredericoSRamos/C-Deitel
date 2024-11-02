#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (50 * 1024 * 1024)
#define CEP_SIZE 8
#define FILENAME_SIZE 12

typedef struct _Address {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
} Address;

int compare(const void * arg1, const void * arg2) {
    return strncmp(((Address *) arg1)->cep, ((Address *) arg2)->cep, CEP_SIZE);
}

int main() {
    char temp[100];

    printf("Type the path to the file to be sorted:\n");
    scanf("%s", temp);

    FILE * file = fopen(temp, "rb+");

    if (!file) {
        printf("Failed to open 'cep.dat' file\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int buffer_divider = size % BUF_SIZE == 0 ? size / BUF_SIZE : size / BUF_SIZE + 1;
    FILE ** temp_files = malloc(buffer_divider * sizeof(FILE *));

    long arr_size = BUF_SIZE / sizeof(Address);

    char ** char_buf = malloc(buffer_divider * sizeof(char *));

    for (int i = 0; i < buffer_divider; i++) {
        Address * arr = malloc(arr_size * sizeof(Address));

        fread(arr, sizeof(Address), arr_size, file);

        qsort(arr, arr_size, sizeof(Address), compare);

        char_buf[i] = malloc(FILENAME_SIZE * sizeof(char));
        sprintf(char_buf[i], "temp-%d.dat", i + 1);

        temp_files[i] = fopen(char_buf[i], "wb+");

        if (!temp_files[i]) {
            printf("Failed to open '%s' file\n", char_buf[i]);
            return 0;
        }

        fwrite(arr, sizeof(Address), arr_size, temp_files[i]);

        free(arr);
    }

    char ** cep = malloc(buffer_divider * sizeof(char *));
    Address ** address_buf = malloc(buffer_divider * sizeof(Address *));

    fseek(file, 0, SEEK_SET);

    long split = arr_size / buffer_divider;
    int * track = malloc(buffer_divider * sizeof(int));
    int * max_elements = malloc(buffer_divider * sizeof(int));

    for (int i = 0; i < buffer_divider; i++) {
        cep[i] = malloc(CEP_SIZE * sizeof(char));
        address_buf[i] = malloc(split * sizeof(Address));
        track[i] = 0;
        max_elements[i] = split;
        fseek(temp_files[i], 0, SEEK_SET);
        fread(address_buf[i], sizeof(Address), split, temp_files[i]);
        strncpy(cep[i], address_buf[i][0].cep, CEP_SIZE);
    }

    int div_size = buffer_divider;

    while (buffer_divider > 0) {
        int min = 0;

        while (min < div_size && max_elements[min] == 0) 
            min++;

        for (int i = min + 1; i < buffer_divider; i++) {
            if (max_elements[i] == 0) {
                continue;
            }

            if (strncmp(cep[i], cep[min], CEP_SIZE) < 0) {
                min = i;
            }
        }

        fwrite(&(address_buf[min][track[min]]), sizeof(Address), 1, file);
        (track[min])++;

        if (track[min] == max_elements[min]) {
            max_elements[min] = fread(address_buf[min], sizeof(Address), split, temp_files[min]);

            if (max_elements[min] == 0) {
                fclose(temp_files[min]);
                remove(char_buf[min]);

                buffer_divider--;
            } else {
                track[min] = 0;
                strncpy(cep[min], address_buf[min][0].cep, CEP_SIZE);
            }
        } else {
            strncpy(cep[min], address_buf[min][track[min]].cep, CEP_SIZE);
        }
    }

    for (int i = 0; i < div_size; i++) {
        free(cep[i]);
        free(char_buf[i]);
        free(address_buf[i]);
    }

    printf("File sorted successfully\n");

    free(char_buf);
    free(cep);
    free(address_buf);
    free(track);
    free(max_elements);
    free(temp_files);

    fclose(file);
}