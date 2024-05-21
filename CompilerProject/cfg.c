
#include <stdio.h>
#include <stdlib.h>

#include "cfg.h"


void CFG()
{
    FILE* file = NULL;
    errno_t er = fopen_s(&file, "C:/Users/User/Desktop/compilerProject/matrixValues.txt", "r"); // Open the file for reading
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%s %d %d", deductions[i].deduct, &deductions[i].valueNumber, &deductions[i].numToCut) == 3 && i < CELLS) {
        i++;
    }

    fclose(file); // Close the file
}
