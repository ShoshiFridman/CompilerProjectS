
#include <stdio.h>
#include <stdlib.h>

#include "lexicaly.h"
#include "mystring.h"
#include "Stack.h"
#include "cfg.h"
#define GARBAGE 0xdcdcdcdcdcdcdcd

#define ROWS 181
#define COLS 102

#define NO_ERROR 0

int matrix[ROWS][COLS];

int FillTable() {
    FILE* fp;


    errno_t er = fopen_s(&fp, "C:/Users/User/Desktop/compilerProject/actions-goto-file.csv", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (fscanf(fp, "%d,", &matrix[i][j]) != 1) {
                printf("Error reading file\n");
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}


//int FillTable() {
//    FILE* fp = NULL;
//    char buffer[1024];
//    int num_lines, num_cols;
//
//    // פתיחת קובץ CSV
//    errno_t er = fopen_s(&fp, "C:/Users/User/Desktop/compilerProject/actions-goto-file.csv", "r");
//    if (fp == NULL) {
//        perror("Error opening file");
//        return 1;
//    }
//
//    // ספירת שורות ועמודות
//    num_lines = 0;
//    num_cols = 0;
//    while (fgets(buffer, sizeof(buffer), fp) && !feof(fp)) {
//        num_lines++;
//        int temp_cols = 0;
//        for (int i = 0; buffer[i] != '\0'; i++) {
//            if (buffer[i] == ',') {
//                temp_cols++;
//            }
//        }
//        if (num_cols == 0) {
//            num_cols = temp_cols;
//        }
//        /*else if (num_cols != temp_cols) {
//            // שגיאה: מספר העמודות אינו אחיד
//            return 1;
//        }*/
//    }
//
//    // הקצאת זיכרון למטריצה
//    matrix = malloc(sizeof(int*) * num_lines);
//    if (matrix == NULL) {
//        perror("Error allocating memory");
//        return 1;
//    }
//    for (int i = 0; i < num_lines; i++) {
//        matrix[i] = malloc(sizeof(int) * num_cols);
//        if (matrix[i] == NULL) {
//            perror("Error allocating memory");
//            return 1;
//        }
//    }
//
//    // קריאת מספרים מהקובץ והעתקתם למטריצה
//    rewind(fp);
//    for (int i = 0; i < num_lines; i++) {
//        for (int j = 0; j < num_cols; j++) {
//            fscanf(fp, "%d", &matrix[i][j]);
//        }
//    }
//
//    // סגירת קובץ
//    fclose(fp);
//
//    // שחרור זיכרון
//   /* for (int i = 0; i < num_lines; i++) {
//        free(matrix[i]);
//    }
//    free(matrix);*/
//
//    return 0;
//}

void returnError(char*);

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
    Node* ret = NULL;
    push(stack, node1);
    // mynode = peek(&stack);

   // Token* tokenPtr = *headList;
    Token* tokenPtr = headList;

    int mystate = NO_ERROR, action, counter, myindex,newAction;

    /*push(&stack, tokenPtr->index);
    tokenPtr = tokenPtr->next;*/

    while (tokenPtr != NULL)

    {
        myindex = tokenPtr->index;

        /*state = peek(&stack);
        push(&stack, tokenPtr->index);*/
        if (mystate == -999 || myindex == -999)
            action = -999;
        else
        action = matrix[mystate][myindex];
        if (action == -999)
        {        
            returnError("syntax error!!!");
            return;


        }

        //push(&stack,abs( action));
        if (action == 0)//access
        {   
            ret = pop(stack);

            return ret;

        }

        if (action > 0)//shift
        {
            node1 = createNode(action, tokenPtr->nameToken, tokenPtr->index);

            push(stack, node1);

            tokenPtr = tokenPtr->next;

            //myindex = peek(&stack)->numOfToken;
        }
        else
        {
            counter = deductions[abs(action)].numToCut;
            mystate = peekAt(stack, counter+1)->state;
            newAction = matrix[mystate][deductions[abs(action)].valueNumber];
            mynode = createNode(newAction, deductions[abs(action)].deduct, deductions[abs(action)].valueNumber);
           // action = newAction;
            for (int i = 0; i < counter; i++)
            {
                Node* childNode = pop(stack);
                addPointer(mynode, childNode);

                childNode->parent = mynode; // Link parent to child
            }

            push(stack, mynode);
        }
        /*if (peek(stack)->state == -999)
            mystate = -999;*/
        mystate = peek(stack)->state;
    }

}
