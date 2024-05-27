
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "mystring.h"


#define TABLE_SIZE 100
#define MAX_STACK_SIZE 50
#define Local_variable_declaration 69
#define Assignment_Operator 7
#define optional_initializer 81
#define ID 0
#define FOR_STATEMENT 72
#define WHILE_STATEMENT 73
#define DO_WHILE_STATEMENT 74
#define FUNCTION_DEFINITION 61
#define BLOCK 64
#define IF_STATEMENT 71
#define RightCurlyBrace 5
#define Semicolon 6
#define binaryOperator 99
#define z 0xFFFFFFFFFFFFFFDF

// Structure to represent a symbol table entry
typedef struct {
    char key[50];//id
    int type;//מספר המבטא את סוג המשתנה
    char value[20];
} Entry;

typedef struct {
    Entry* items[MAX_STACK_SIZE];
    int top;
} MyStack;
MyStack mystack;


// Function to initialize the stack
void initialize_stack(MyStack* stack) {
    stack->top = -1;
}

Entry* getNextItem(MyStack* stack) {
    if (stack->top < 0) {
        return NULL; // Stack is empty
    }

    static int currentIndex = 0; // Static variable to keep track of current index

    if (currentIndex <= stack->top) {
        Entry* currentItem = stack->items[currentIndex];
        currentIndex++;
        return currentItem;
    }
    else {
        return NULL; // Reached end of stack
    }
}

// Function to push an item onto the stack
void push1(MyStack* stack, Entry* item) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// Function to pop an item from the stack
Entry* pop1(MyStack* stack) {
    if (stack->top < 0) {
        printf("Stack is empty\n");
        return NULL;
    }
    return stack->items[stack->top--];
}

Entry* peek1(MyStack* stack) {
    if (stack->top < 0) {
        printf("Stack is empty\n");
        return NULL;
    }
    return stack->items[stack->top];
}

Entry hash_table[TABLE_SIZE];		// Hash table to store symbol table entries
Entry* hash_table_ptr = hash_table; // Pointer to the hash table on the stack

// Hash function to calculate index for key
int hash_function(char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

// Function to insert an entry into the symbol table
void insert_entry(Entry* table, char* key, int type) {
    int index = hash_function(key);
    myStrcpy(table[index].key, key);

    table[index].type = type;
    // Dynamically allocate memory for the value if needed
}

void insert_value(Entry* table, char* key, char* val) {
    int index = hash_function(key);
    myStrcpy(table[index].value, val);
}

// Function to search for an entry in the symbol table
Entry* search_entry(Entry* ht, char* key)
{
    int index = hash_function(key);
    if (myStrcmp(ht[index].key, key) == 0) {
        return &ht[index];
    }
    else {
        return NULL;
    }
}

void returnError(char*);

void check(struct Node* node, Entry* Item)
{
    //בדיקת התאמה בין סוגים ע"י מעבר על העלים של צומת הביטוי 
    Entry* e = NULL;
    if (node == NULL) {
        return;
    }

    if (node->numPointers == 0) {
        if (node->numOfToken == 0)
            e = search_entry(peek1(&mystack), node->key);
        if (node->numOfToken == 31 && Item->type != 51 || node->numOfToken == 32 && Item->type != 52 || node->numOfToken == 33 && Item->type != 55 || node->numOfToken == 34 && Item->type != 54 || e != NULL && e->type != Item->type)
            returnError("A value was entered that does not match the definition");
        else
            insert_value(peek1(&mystack), Item->key, node->key);//הכנסת הערך של ההשמה לשורה בטבלה

    }
    else {
        // Recursively check children for leaf nodes
        for (int i = 0; i < node->numPointers; i++) {
            check(node->pointers[i], Item);
        }
    }
}

void checkOperators(struct Node* node1, struct Node* node2)
{
    //בדיקת התאמה בין סוגים ע"י מעבר על העלים של צומת הביטוי 
    Entry* e = NULL;
    Entry* e1 = NULL;

    if (node1 == NULL || node2 == NULL||node2==z) {
        return;
    }

    if (node1->numPointers != 0 && node2->numPointers != 0)
    {
        // Recursively check children for leaf nodes
        for (int i = 0, j = 0; i < node1->numPointers && j < node2->numPointers; i++, j++) {
            checkOperators(node1->pointers[i], node2->pointers[j]);
        }
    }

    if (node1->numOfToken == 0)
        e = search_entry(peek1(&mystack), node1->key);

    if (node2->numOfToken == 0)
        e1 = search_entry(peek1(&mystack), node2->key);

    if (node1->numOfToken != node2->numOfToken || node1->numOfToken + node2->numOfToken != 63 || e != NULL && e->type != node2->numOfToken || e1 != NULL && e1->type != node1->numOfToken || e != NULL && e1 != NULL && e->type != e1->type)
        returnError("semantic error:The values are not of the same type");
}

Entry* searchInStack(char* key)//חיפוש בכל טבלאות הסמלים
{
    Entry* found_Entry;
    Entry* currentItem;
    int degel = 0;
    while ((currentItem = getNextItem(&mystack)) != NULL && !degel)
    {
        found_Entry = search_entry(currentItem, key);
        if (found_Entry != NULL)
        {
            degel = 1;
            return found_Entry;
        }

    }
    return NULL;
}

//פונקצייה שבודקת האם משתנה מוגדר בטבלת סמלים
Entry* checkIfDeclared(char* key)
{
    Entry* entry = searchInStack(key);


    if (entry == NULL)
    {
        returnError("semantic error:Variable not defined!!!");

    }
    return entry;
}

void createNewSymbolTable()
{
    Entry new_hash_table[TABLE_SIZE];
    Entry* new_hash_table_ptr = new_hash_table;
    push1(&mystack, new_hash_table_ptr);

}

int searchBlock(struct Node* node)
{
    if (node == NULL) {
        return 0;
    }
    if (node->numOfToken == IF_STATEMENT)
        return 0;

    if (node->numOfToken == BLOCK)
        return 1;
    else
    {
        // Recursively check children for leaf nodes
        for (int i = 0; i < node->numPointers; i++) {
            searchBlock(node->pointers[i]);
        }
    }

    return 0;
}

void deepSearch(struct Node* node, int d)
{
    if (node == NULL) {
        return;
    }
    //הצהרה על משתנה
    if (node->numOfToken == Local_variable_declaration)//local-variable-declaration
        insert_entry(peek1(&mystack), node->pointers[node->numPointers - 2]->key, node->pointers[node->numPointers-1]->pointers[0]->numOfToken);//הכנסת שורה לטבלת סמלים שמכילה את הערך ואת הסוג

    //בכל התקלות בID בדיקה אם לא מוגדר בטבלת סמלים
    if (node->numOfToken == ID && node->parent->numOfToken != Local_variable_declaration&& node->parent->numOfToken != FUNCTION_DEFINITION)
    {
        checkIfDeclared(node->key);
    }
    //השמת ערך במשתנה
    if (node->numOfToken == Assignment_Operator && node->parent->numOfToken == optional_initializer)
    {
        Entry* entry = checkIfDeclared((node->parent->parent->pointers[node->parent->parent->numPointers - 2])->key);

        if (entry != NULL)
            check(node->parent->pointers[0], entry);
    }
    //התחלת סקופ של פונקציה
    if (node->numOfToken == FUNCTION_DEFINITION)
    {
        createNewSymbolTable();
        d = 1;

    }
    //התחלת סקופ של לולאה
    if (node->numOfToken == FOR_STATEMENT || node->numOfToken == WHILE_STATEMENT || node->numOfToken == DO_WHILE_STATEMENT)
    {

        createNewSymbolTable();
        d = searchBlock(node);//אם יש סלסלים בלולאה
        if (!d)
            d = 2;
    }

    if (d == 1 && node->numOfToken == RightCurlyBrace)//הוצאת הטבלה מהמחסנית כשנתקלים בסלסל סוגר
    {
        pop1(&mystack);
        d = 0;

    }
    if (d == 2 && node->numOfToken == Semicolon && node->parent->numOfToken != FOR_STATEMENT)//הוצאת הטבלה מהמחסנית כשנתקלים בנקודה פסיק
    {
        pop1(&mystack);
        d = 0;
    }
    if (node->numOfToken == binaryOperator)//בדיקת ערכים מ2 עברי האופרטור
    {

        checkOperators(node->parent->pointers[0], node->parent->pointers[node->parent->numPointers-1]);
    }
    for (int i = node->numPointers-1; i >=0; i--) {
        deepSearch(node->pointers[i], d);

    }
}

Node* syntactAnalysis();

void semanticAnalysis() {

    Node* node = syntactAnalysis();

    initialize_stack(&mystack);

    push1(&mystack, hash_table_ptr);

    deepSearch(node, 0);
}


void main()
{
    semanticAnalysis();
}
