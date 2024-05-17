
#include <stdio.h>
#include <stdlib.h>
#define COLUMN 11
#define ROW 113
#define SIZE_BUFFER 1024
#define NUM 10
#define NO_ERROR 0


FILE* fileGrammar = NULL;
void Grammar()
{
    errno_t er = fopen_s(fileGrammar, "C:/Users/User/Desktop/compilerProject/CFG.txt", "r");
    if (fileGrammar == NULL)
    {
        printf("error in the file CFG.txt \n");
        exit(1);
    }
    char buffer[SIZE_BUFFER];
    char* matrix[ROW][COLUMN]; // Assuming a maximum of 113 rows and 11 strings per row
    int row = NO_ERROR;
    char* tokens[NUM];
    int num_tokens = NO_ERROR;
    char* start;
    char* end;
    char* ptr;

    while (fgets(buffer, sizeof(buffer), fileGrammar) != EOF) {
        num_tokens = NO_ERROR;
        ptr = buffer; // Pointer to iterate over the buffer array
        start = ptr;
        end = ptr; // Allocate memory for end pointer
        while (*ptr != '\0') {
            if (*ptr == '>' || *ptr == ' ') {
                *end = '\0';
                tokens[num_tokens++] = start;
                start = ptr + 1;
            }
            ptr++;
            end++; // Move end pointer with buffer
        }
        tokens[num_tokens++] = start;
        _itoa_s(num_tokens, matrix[row][NO_ERROR], NUM, 0);//הכנסת מס' המחרוזות בשורה לאינדקס הראשון במטריצה

        // Store tokens in the matrix
        for (int i = 1; i < num_tokens; i++) {
            matrix[row][i] = tokens[i];
        }
        row++;
    }
    fclose(fileGrammar);

}