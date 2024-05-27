#include <stdio.h>


void returnError(char* message) {
    FILE* file = NULL;
    errno_t er = fopen_s(&file, "C:/Users/User/Desktop/compilerProject/errorFile.txt", "w"); // Open file in append mode ("a" for appending to the file)

    //errno_t er = fopen_s(&file, "C:/Users/User/Desktop/compilerProject/errorFile.txt", "a"); // Open file in append mode ("a" for appending to the file)

    if (file == NULL) {
        printf("Error opening error file.\n");
        return;
    }

    fprintf(file, "%s\n", message); // Write the message to the file

    fclose(file); // Close the file
}
