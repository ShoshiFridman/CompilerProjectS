
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
#define SG 63
#define NA 51
#define LB 32
#define NB 52
#define LG 33
#define NH 55
#define LD 34
#define ND 54


#define z 0xFFFFFFFFFFFFFFDF
#define ACTION_NULL(node) if (IS_NULL(node))
#define ACTION_LOCAL_VAR_DECL(node) if (IS_LOCAL_VAR_DECL(node))
#define ACTION_ID(node) if (IS_ID(node))
#define ACTION_FUNC_DEF(node) if (IS_FUNC_DEF(node))
#define ACTION_ASSIGN_OP(node) if (IS_ASSIGN_OP(node))
#define ACTION_OPT_INITIALIZER(node) if (IS_OPT_INITIALIZER(node))
#define ACTION_FOR_STMT(node) if (IS_FOR_STMT(node))
#define ACTION_WHILE_STMT(node) if (IS_WHILE_STMT(node))
#define ACTION_DO_WHILE_STMT(node) if (IS_DO_WHILE_STMT(node))
#define ACTION_RIGHT_CURLY_BRACE(node) if (IS_RIGHT_CURLY_BRACE(node))
#define ACTION_SEMICOLON(node) if (IS_SEMICOLON(node))
#define ACTION_BINARY_OP(node) if (IS_BINARY_OP(node))

#define IS_NULL(node) (node == NULL)
#define IS_LOCAL_VAR_DECL(node) (node->numOfToken == Local_variable_declaration)
#define IS_ID(node) (node->numOfToken == ID)
#define IS_FUNC_DEF(node) (node->numOfToken == FUNCTION_DEFINITION)
#define IS_ASSIGN_OP(node) (node->numOfToken == Assignment_Operator)
#define IS_OPT_INITIALIZER(node) (node->parent->numOfToken == optional_initializer)
#define IS_FOR_STMT(node) (node->numOfToken == FOR_STATEMENT)
#define IS_WHILE_STMT(node) (node->numOfToken == WHILE_STATEMENT)
#define IS_DO_WHILE_STMT(node) (node->numOfToken == DO_WHILE_STATEMENT)
#define IS_RIGHT_CURLY_BRACE(node) (node->numOfToken == RightCurlyBrace)
#define IS_SEMICOLON(node) (node->numOfToken == Semicolon)
#define IS_BINARY_OP(node) (node->numOfToken == binaryOperator)

// Structure to represent a symbol table entry
typedef struct {
    char key[15];//id
    int type;//מספר המבטא את סוג המשתנה
    char valuee[20];
} Entry;

typedef struct {
    Entry* items[MAX_STACK_SIZE];
    int top;
} MyStack;
MyStack mystack;


// Function to initialize the stack
void initialize_stack() {
    mystack.top = -1;
}

Entry* getNextItem() {
    if (mystack.top < 0) {
        return NULL; // Stack is empty
    }

    static int currentIndex = 0; // Static variable to keep track of current index

    if (currentIndex <= mystack.top) {
        Entry* currentItem = mystack.items[currentIndex];
        currentIndex++;
        return currentItem;
    }
    else {
        return NULL; // Reached end of stack
    }
}

// Function to push an item onto the stack
void push1(/*Entry(*item)[TABLE_SIZE]*/ ) {
    if (mystack.top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    } 
    Entry new_hash_table[TABLE_SIZE];
Entry(*new_hash_table_ptr)[TABLE_SIZE] = new_hash_table;
  mystack.items[++mystack.top] = new_hash_table_ptr;


    /*mystack.items[++mystack.top] = new_hash_table_ptr;
    Entry new_hash_table[TABLE_SIZE];
    Entry(*new_hash_table_ptr)[TABLE_SIZE] = new_hash_table;
    mystack.items[++mystack.top] = &new_hash_table_ptr;*/
 }

// Function to pop an item from the stack
Entry* pop1() {
    if (mystack.top < 0) {
        printf("Stack is empty\n");
        return NULL;
    }
    return mystack.items[mystack.top--];
}

Entry* peek1() {
    if (mystack.top < 0) {
        printf("Stack is empty\n");
        return NULL;
    }
    return mystack.items[mystack.top];
}

Entry hash_table[TABLE_SIZE];		// Hash table to store symbol table entries
Entry(* hash_table_ptr)[TABLE_SIZE] = &hash_table; // Pointer to the hash table on the stack

// Hash function to calculate index for key
int hash_function(char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

// Function to insert an entry into the symbol table
void insert_entry(Entry(*table)[TABLE_SIZE], char* key, int type) {
    int index = hash_function(key);
    myStrcpy((*table)[index].key, key);

    (*table)[index].type = type;
    // Dynamically allocate memory for the value if needed
}

void insert_value(Entry(*table)[TABLE_SIZE], char* key, char* val) {
    int index = hash_function(key);
    myStrcpy((*table)[index].valuee, val);
}

// Function to search for an entry in the symbol table
Entry* search_entry(Entry(*ht)[TABLE_SIZE], char* key)
{
    int index = hash_function(key);
    if (myStrcmp((*ht)[index].key, key) == 0) {
        Entry* ent = (Entry*)malloc(sizeof(Entry));
        myStrcpy(ent->key,  (*ht)[index].key);
        ent->type = (*ht)[index].type;
        myStrcpy(ent->valuee, (*ht)[index].valuee);
        return ent;
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
            e = search_entry(peek1(), node->key);
        if (node->numOfToken == 31 && Item->type != NA || node->numOfToken == LB && Item->type != NB || node->numOfToken == LG && Item->type != NH || node->numOfToken == LD && Item->type != ND || e != NULL && e->type != Item->type)
            returnError("A value was entered that does not match the definition");
        else
            insert_value(peek1(), Item->key, node->key);//הכנסת הערך של ההשמה לשורה בטבלה

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
        e = search_entry(peek1(), node1->key);

    if (node2->numOfToken == 0)
        e1 = search_entry(peek1(), node2->key);

    if (node1->numOfToken != node2->numOfToken || node1->numOfToken + node2->numOfToken != SG || e != NULL && e->type != node2->numOfToken || e1 != NULL && e1->type != node1->numOfToken || e != NULL && e1 != NULL && e->type != e1->type)
        returnError("semantic error:The values are not of the same type");
}

Entry* searchInStack(char* key)//חיפוש בכל טבלאות הסמלים
{
    Entry* found_Entry;
    int degel = 0;

    // Iterate over each symbol table in the stack
    for (int i = mystack.top; i >= 0 && !degel; i--) {
        Entry(*currentItem)[TABLE_SIZE] = mystack.items[i];

        for (int j = 0; j < TABLE_SIZE; j++) {
            found_Entry = search_entry(currentItem, key);
            if (found_Entry != NULL) {
                degel = 1;
                return found_Entry;
            }
        }
    }

    return NULL;
    /*Entry* found_Entry;
    Entry* currentItem;
    int degel = 0;
    while ((currentItem = getNextItem()) != NULL && !degel)
    {
       found_Entry = search_entry(currentItem, key);
        if (found_Entry != NULL)
        {
            degel = 1;
            return found_Entry;
        }

    }
    return NULL;*/
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

//void createNewSymbolTable()
//{
//    
//    Entry new_hash_table[TABLE_SIZE];
//    Entry(*new_hash_table_ptr)[TABLE_SIZE] = new_hash_table;
//    push1(&new_hash_table_ptr);
//
//
//
//}

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
    ACTION_NULL(node) {
        return;
    }

    ACTION_LOCAL_VAR_DECL(node) {
        insert_entry(peek1(), node->pointers[node->numPointers - 2]->key, node->pointers[node->numPointers - 1]->pointers[0]->numOfToken);
    }

    ACTION_ID(node) {
        checkIfDeclared(node->key);
    }

    ACTION_ASSIGN_OP(node) {
        Entry* entry = checkIfDeclared((node->parent->parent->pointers[node->parent->parent->numPointers - 2])->key);

        if (entry != NULL)
            check(node->parent->pointers[0], entry);
    }

    ACTION_FUNC_DEF(node) {
        push1();
        d = 1;
    }

    ACTION_FOR_STMT(node) {
        push1();
        d = searchBlock(node);
        if (!d)
            d = 2;
    }

    ACTION_RIGHT_CURLY_BRACE(node) {
        pop1();
        d = 0;
    }

    ACTION_SEMICOLON(node) {
        if (node->parent->numOfToken != FOR_STATEMENT) {
            pop1();
            d = 0;
        }
    }

    ACTION_BINARY_OP(node) {
        checkOperators(node->parent->pointers[0], node->parent->pointers[node->parent->numPointers - 1]);
    }

    for (int i = node->numPointers - 1; i >= 0; i--) {
        deepSearch(node->pointers[i], d);
    }
   
    //if (node == NULL) {
    //    return;
    //}
    //הצהרה על משתנה
    //if (node->numOfToken == Local_variable_declaration)//local-variable-declaration
    //    insert_entry(peek1(), node->pointers[node->numPointers - 2]->key, node->pointers[node->numPointers-1]->pointers[0]->numOfToken);//הכנסת שורה לטבלת סמלים שמכילה את הערך ואת הסוג

    //בכל התקלות בID בדיקה אם לא מוגדר בטבלת סמלים
    //if (node->numOfToken == ID && node->parent->numOfToken != Local_variable_declaration&& node->parent->numOfToken != FUNCTION_DEFINITION)
    //{
    //    checkIfDeclared(node->key);
    //}
    //השמת ערך במשתנה
    //if (node->numOfToken == Assignment_Operator && node->parent->numOfToken == optional_initializer)
    //{
    //    Entry* entry = checkIfDeclared((node->parent->parent->pointers[node->parent->parent->numPointers - 2])->key);

    //    if (entry != NULL)
    //        check(node->parent->pointers[0], entry);
    //}
    //התחלת סקופ של פונקציה
    //if (node->numOfToken == FUNCTION_DEFINITION)
    //{
    //    push1();
    //    createNewSymbolTable();
    //    d = 1;

    //}
    //התחלת סקופ של לולאה
    //if (node->numOfToken == FOR_STATEMENT || node->numOfToken == WHILE_STATEMENT || node->numOfToken == DO_WHILE_STATEMENT)
    //{
    //    push1();

    //    createNewSymbolTable();
    //    d = searchBlock(node);//אם יש סלסלים בלולאה
    //    if (!d)
    //        d = 2;
    //}

    //if (d == 1 && node->numOfToken == RightCurlyBrace)//הוצאת הטבלה מהמחסנית כשנתקלים בסלסל סוגר
    //{
    //    pop1();
    //    d = 0;

    //}
    //if (d == 2 && node->numOfToken == Semicolon && node->parent->numOfToken != FOR_STATEMENT)//הוצאת הטבלה מהמחסנית כשנתקלים בנקודה פסיק
    //{
    //    pop1();
    //    d = 0;
    //}
    //if (node->numOfToken == binaryOperator)//בדיקת ערכים מ2 עברי האופרטור
    //{

    //    checkOperators(node->parent->pointers[0], node->parent->pointers[node->parent->numPointers-1]);
    //}
    //for (int i = node->numPointers-1; i >=0; i--) {
    //    deepSearch(node->pointers[i], d);

    //}
}

Node* syntactAnalysis();

void semanticAnalysis() {

    Node* node = syntactAnalysis();

    initialize_stack();

    push1();


    deepSearch(node, 0);
}


void main()
{
    semanticAnalysis();
    returnError("The program is finishes!");

}
