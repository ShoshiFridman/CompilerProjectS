
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
    Node* node1 = createNode(NO_ERROR, "$" ,58);
    Node* mynode;
    Node* ret = NULL;
    push(stack, node1);
    
    Token* tokenPtr = headList;

    int mystate = NO_ERROR, action, counter, myindex,newAction;

    

    while (tokenPtr != NULL)

    {
        myindex = tokenPtr->index;

        
       
        action = matrix[mystate][myindex];
        if (action == -999)
        {        
            returnError("syntax error!!!");
            exit(0);

        }

        if (action == 0)//access
        {   
            ret = pop(stack);

            return ret;

        }

        if (action > 0)//shift
        {
            node1 = createNode(action, tokenPtr->value, tokenPtr->index);

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
            for (int i = 0; i < counter; i++)
            {
                Node* childNode = pop(stack);
                addPointer(mynode, childNode);

                childNode->parent = mynode; // Link parent to child
            }

            push(stack, mynode);
        }
        
        mystate = peek(stack)->state;
    }

}
