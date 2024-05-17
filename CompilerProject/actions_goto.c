
#include <stdio.h>
#include <stdlib.h>
#include "Stack.c"

#include "CFG.c"

#ifndef error_c
#define error_c
#endif // !error_c

#include "lexicaly.c"

#define NO_ERROR 0
int** matrix;


int FillTable() {
    FILE* fp = NULL;
    char buffer[1024];
    int num_lines, num_cols;

    // פתיחת קובץ CSV
    errno_t er = fopen_s(fp, "C:/Users/User/Desktop/compilerProject/actions-goto-file.csv", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // ספירת שורות ועמודות
    num_lines = 0;
    num_cols = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        num_lines++;
        int temp_cols = 0;
        char* line = mystrtok(buffer, ",");
        while (line != NULL) {
            temp_cols++;
            line = mystrtok(NULL, ",");
        }
        if (num_cols == 0) {
            num_cols = temp_cols;
        }
        /*else if (num_cols != temp_cols) {
            // שגיאה: מספר העמודות אינו אחיד
            return 1;
        }*/
    }

    // הקצאת זיכרון למטריצה
    matrix = malloc(sizeof(int*) * num_lines);
    if (matrix == NULL) {
        perror("Error allocating memory");
        return 1;
    }
    for (int i = 0; i < num_lines; i++) {
        matrix[i] = malloc(sizeof(int) * num_cols);
        if (matrix[i] == NULL) {
            perror("Error allocating memory");
            return 1;
        }
    }

    // קריאת מספרים מהקובץ והעתקתם למטריצה
    rewind(fp);
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_cols; j++) {
            fscanf_s(fp, "%d", &matrix[i][j]);
        }
    }

    // סגירת קובץ
    fclose(fp);



    // שחרור זיכרון
   /* for (int i = 0; i < num_lines; i++) {
        free(matrix[i]);
    }
    free(matrix);*/

    return 0;
}

Node* syntactAnalysis()
{
    lexicalAnalysis();
    FillTable();
    CFG();

    //פונקציה זו מנהלת את המחסנית ע"י קריאת רשימת הטוקנים,
    //בדיקה בטבלה במיקום המתאים + הטוקן
    //אם המספר חיובי- פעולת שיפט מכניסים את הטוקן הבא מהרשימה
    //אם רדיוס- הולכים לשורה המתאימה בטבלת הדקדוק ומונים כמה טוקנים יש שם 
    // מוציאים פי שניים מהטוקנים מספרים מהמחסנית ומכניסים במקום את הגוזר של הכלל. 
    Stack* stack = createStack();
    Node* node1 = createNode(NO_ERROR, "$", 58);
    Node* mynode;
    Node* ret;
    push(&stack, node1);
    // mynode = peek(&stack);

    Token* tokenPtr = *headList;

    int mystate = NO_ERROR, action, counter, myindex = tokenPtr->index;





    /*push(&stack, tokenPtr->index);
    tokenPtr = tokenPtr->next;*/

    while (tokenPtr != NULL)

    {
        /*state = peek(&stack);
        push(&stack, tokenPtr->index);*/
        action = matrix[mystate][myindex];
        if (action == -999)
            returnError("syntax error!!!");
        //push(&stack,abs( action));
        if (action == 0)//access
            ret = pop(&stack);
        if (action > 0)//shift
        {
            node1 = createNode(action, tokenPtr->nameToken, tokenPtr->index);

            push(&stack, node1);



            tokenPtr = tokenPtr->next;

            //myindex = peek(&stack)->numOfToken;

        }

        else
        {

            counter = deductions[abs(action)].numToCut;
            mystate = peekAt(&stack, counter)->state;
            action = matrix[mystate][deductions[abs(action)].valueNumber];
            mynode = createNode(action, deductions[abs(action)].deduct, deductions[abs(action)].valueNumber);
            for (int i = 0; i < counter; i++)
            {
                Node* childNode = pop(&stack);
                addPointer(mynode, childNode);

                childNode->parent = mynode; // Link parent to child

            }



            push(&stack, mynode);


        }
        mystate = peek(&stack)->state;
        myindex = tokenPtr->index;

    }


}
