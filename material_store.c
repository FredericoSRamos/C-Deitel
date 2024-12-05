#include <stdio.h>
#include <string.h>

typedef struct _Material {
    char name[18];
    int amount;
    float price;
} Material;

int main() {
    FILE * file = fopen("tools.dat", "wb+");

    Material emptyRegister;
    strcpy(emptyRegister.name, "");
    emptyRegister.amount = 0;
    emptyRegister.price = 0;

    for (int i = 0; i < 100; i++) {
        fwrite(&emptyRegister, sizeof(Material), 1, file);
    }

    int registerNumber;

    printf("Input the register number, tool name, amount and price:\n");
    scanf("%d %s %d %f", &registerNumber, emptyRegister.name, &emptyRegister.amount, &emptyRegister.price);

    Material temp;

    fseek(file, registerNumber * sizeof(Material), SEEK_SET);
    fread(&temp, sizeof(Material), 1, file);

    if (temp.name[0] == '\0') {
        printf("There's already an item at that position.");
        return 1;
    }

    fseek(file, registerNumber * sizeof(Material), SEEK_SET);
    fwrite(&emptyRegister, sizeof(Material), 1, file);

    fseek(file, 0, SEEK_SET);
    fread(&temp, sizeof(Material), 1, file);

    int counter, totalAmount;
    counter = totalAmount = 0;

    while(!feof(file)) {
        if (temp.name[0] == '\0') {
            fread(&temp, sizeof(Material), 1, file);
            continue;
        }

        counter++;
        totalAmount += temp.amount;
        fread(&temp, sizeof(Material), 1, file);
    }

    printf("%d itens registered. Total amount of items: %d.\n", counter, totalAmount);
}