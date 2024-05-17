
#include <stdio.h>
#include <stdlib.h>
#define CELLS 115
typedef struct Deduction
{
    char deduct[15];
    int valueNumber;
    int numToCut;

}Deduction;
Deduction deductions[CELLS]; // Assuming a maximum of 115 rows

void CFG()
{
    FILE* file = NULL;
    errno_t er = fopen_s(file, "C:/Users/User/Desktop/compilerProject/matrixValues.txt", "r"); // Open the file for reading
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }


    int i = 0;
    while (fscanf_s(file, "%s %d %d", deductions[i].deduct, &deductions[i].valueNumber, &deductions[i].numToCut) == 3) {
        i++;
    }


    fclose(file); // Close the file

    return 0;
}


