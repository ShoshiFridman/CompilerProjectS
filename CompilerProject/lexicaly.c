
#include <stdio.h>
#include <stdlib.h>

#define GARBAGE 0xdcdcdcdcdcdcdcd

#define MAX_SIZE 20 // Maximum number of lines to read
#define MAX_STR_SIZE 50 // Maximum size for the string


//#include "lexemes.c"
#include "lexicaly.h"

#define NO_ERROR 0
#define specialTavArr 24
#define sizeOfNameTOK_OP 10
#define row 12
#define column 7
#define dollarValue 58

#define DEGEL 0
#define NUM_STATES 220
#define GARBAGE 0xcdcdcdcdcdcdcdcd

#define END_STATE_SIZE 60
#define SIZET 15



typedef struct EndState
{
	int numToken;
	char nameToken[SIZET];
	int num;
	struct EndState* next;


};
struct EndState* pointer;
struct EndState* end_states_arr[END_STATE_SIZE];
FILE* fileTokens = NULL;

int x = NO_ERROR;












//מילוי מערך המצבים
typedef struct CurrentState {
	char letter;
	int nextIndex;
	struct CurrentState* csptr;

}CurrentState;
CurrentState cs;
CurrentState* currentStateArr[NUM_STATES];
CurrentState* ptr;
struct Data {
	char str[MAX_STR_SIZE];
	int num;
};	struct Data dataArray[MAX_SIZE];
int mat[row][column];


typedef struct Token {
	char* value;
	char* nameToken;
	int index;
	struct Token* next;

}Token;



Token* token1;
Token* tokenPtr;
Token** headList;

char characters[specialTavArr];






int automate()
{//מילוי מבנה האוטומט

	FILE* fileStates = NULL;
	int index;

	errno_t er = fopen_s(fileStates, "C:/Users/User/Desktop/compilerProject/state.txt", "r");

	if (fileStates == NULL)
	{
		printf("error in the file states.txt \n");
		exit(1);
	}
	for (int i = 0; i < NUM_STATES; i++)
	{
		currentStateArr[i] = malloc(sizeof(CurrentState));
		currentStateArr[i]->nextIndex = -999;
	}

	while (fscanf_s(fileStates, "%d %c %d", &index, &(cs.letter), &(cs.nextIndex)) != EOF)
	{

		if (currentStateArr[index] != NULL && currentStateArr[index]->nextIndex == -999)
		{
			currentStateArr[index] = malloc(sizeof(CurrentState));
			currentStateArr[index]->letter = cs.letter;
			currentStateArr[index]->nextIndex = cs.nextIndex;
			currentStateArr[index]->csptr = cs.csptr;
		}


		else
		{
			ptr = currentStateArr[index];
			while (ptr->csptr != NULL && ptr->csptr != GARBAGE)
				ptr = ptr->csptr;

			ptr->csptr = malloc(sizeof(CurrentState));
			ptr->csptr->letter = cs.letter;
			ptr->csptr->nextIndex = cs.nextIndex;
			ptr->csptr->csptr = NULL;
		}

	}

	fclose(fileStates);
	//free(currentStateArr);
	//free(pointer->csptr->csptr);
	return 0;
}

//פונקציה שיוצרת רשימה של טוקנים 
void MyListOfTokens(char* value, char* nameToken, int index)
{
	FILE* writeFile = NULL;

	tokenPtr = malloc(sizeof(Token));
	if (tokenPtr == NULL)
	{
		printf("Error allocating memory for tokenPtr\n");
		exit(1);
	}

	token1 = malloc(sizeof(Token));
	if (token1 == NULL)
	{
		printf("Error allocating memory for token1\n");
		exit(1);
	}
	tokenPtr = token1;

	token1->value = value;
	token1->nameToken = nameToken;
	token1->index = index;

	token1->next = NULL;
	if (tokenPtr != NULL && tokenPtr != GARBAGE)

		tokenPtr->next = token1;
	else
		*headList = tokenPtr;



	errno_t er = fopen_s(writeFile, "C:/Users/User/Desktop/compilerProject/myTokens.txt", "a");

	if (writeFile == NULL)
	{
		printf("error in the file tokens.txt \n");
		exit(1);
	}
	fprintf(writeFile, " %s %s \n", value, nameToken);
	fclose(writeFile);

}
// שמקבלת מצב ומילה ומחפשת במערך המצבים הסופיים את הטוקן שמתאים למילה הספציפיתפונקציה
int findToken(int* state, char* word)
{
	// שימוש בטבלת גיבוב וחיסכון של מעבר על כל המערך
	int i = *state % END_STATE_SIZE;
	while (end_states_arr[i]->next != NULL)
	{
		x = end_states_arr[i]->numToken;
		if (x == *state)
		{
			MyListOfTokens(word, end_states_arr[i]->nameToken, end_states_arr[i]->num);

			return 1;
		}
	}




	return 0;
}

//פונקצית מעבר על האוטומט לפי המילה המתקבלת
void overTheWord(char* word)
{
	int i = 0, w = DEGEL, degel = DEGEL, j;
	while (cs.nextIndex <= NUM_STATES && cs.nextIndex >= 0 && word[w] != '\0')

	{
		//if(currentStateArr[i]!= 0x0000000000000000)
		cs = *currentStateArr[i];
		while (cs.csptr != NULL && ((int)cs.letter != (int)word[w]))
			cs = *(cs.csptr);

		w++;

		j = i;
		i = cs.nextIndex;

	}
	//חיפוש בטבלת מצבים סופיים אם הגענו למצב סופי

	degel = findToken(&j, &word[0]);
	if (!degel)
	{

		MyListOfTokens(word, "TOK_ID", DEGEL);

		return 1;



	}



}

void fillMat()
{
	FILE* file = NULL;

	//יצירת מטריצה עבור בדיקה של ביטויים חשבוניים אם הם מורכבים מ2 תווים ברצף והוצאת הטוקן המתאים
	int num;
	int rows = 0, cols;
	errno_t er = fopen_s(file, "C:/Users/User/Desktop/compilerProject/mat.txt", "r");
	if (file == NULL)
	{
		printf("error in the file mat.txt \n");
		exit(1);
	}
	while (fscanf_s(file, "%d", &num) == 1 && rows < row) {
		cols = 0;
		mat[rows][cols] = num;
		cols++;

		// Continue reading numbers from the same row
		while (fscanf_s(file, "%d", &num) == 1 && cols < column) {
			mat[rows][cols] = num;
			cols++;
		}

		rows++;
	}

	fclose(file); // Close the file
}
void fillSpecialTavArr()
{
	FILE* file = NULL;
	int index = 0;

	errno_t er = fopen_s(file, "C:/Users/User/Desktop/compilerProject/specialTavs.txt", "r"); // Open the file in read mode

	if (file == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	// Read characters from the file and store them in the array
	while ((characters[index] = fgetc(file)) != EOF && index < specialTavArr) {
		index++;
	}

	characters[index] = '\0'; // Add null terminator at the end

	fclose(file); // Close the file

}
void fillDuplicateTavs() {


	FILE* file = NULL;
	int index = 0;

	errno_t er = fopen_s(file, "C:/Users/User/Desktop/compilerProject/duplicateCharacters.txt", "r"); // Open the file in read mode

	if (file == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	// Read values from the file and store them in the array of structures
	while (fscanf_s(file, "%s %d", dataArray[index].str, &dataArray[index].num) == 2 && index < MAX_SIZE) {
		index++;
	}

	fclose(file); // Close the file

}

//פונקציה שממלאת את מערך המצבים הסופיים
int FillEndStatesArr() {
	struct EndState endState;

	errno_t er = fopen_s(fileTokens, "C:/Users/User/Desktop/compilerProject/newTokens.txt", "r");
	if (fileTokens == NULL)
	{
		printf("error in the file tokens.txt \n");
		exit(1);
	}

	while (fscanf_s(fileTokens, "%d %s %d", &(endState.numToken), endState.nameToken, &(endState.num)) != EOF && x <= END_STATE_SIZE)

	{
		x = endState.numToken % END_STATE_SIZE;
		if (end_states_arr[x] != NULL)
		{
			end_states_arr[x] = malloc(sizeof(struct EndState));
			end_states_arr[x]->numToken = endState.numToken;
			end_states_arr[x]->next = endState.next;
			myStrcpy(end_states_arr[x]->nameToken, endState.nameToken);
			end_states_arr[x]->num = endState.num;
		}
		else {
			pointer = end_states_arr[x];
			while (pointer->next != NULL && pointer->next != GARBAGE)
				pointer = pointer->next;

			end_states_arr[x]->next = malloc(sizeof(struct EndState));
			end_states_arr[x]->next->numToken = endState.numToken;
			end_states_arr[x]->next->next = NULL;
			myStrcpy(end_states_arr[x]->next->nameToken, endState.nameToken);
			end_states_arr[x]->next->num = endState.num;
		}



	}
	fclose(fileTokens);
	free(end_states_arr);
	return NO_ERROR;
}


//פונקציה ראשית לניהול הניתוח הלקסיקלי
void lexicalAnalysis()
{
	int degel = NO_ERROR;

	FILE* file = NULL;

	automate();
	FillEndStatesArr();

	fillMat();
	fillSpecialTavArr();
	fillDuplicateTavs();



	char tav;
	int size = NO_ERROR;

	char* word = malloc(size);
	if (word == NULL) {
		perror("Error allocating memory");
		return 1;
	}
	headList = malloc(sizeof(Token*));
	if (headList == NULL) {
		perror("Error allocating memory");
		return 1;
	}

	errno_t er = fopen_s(file, "C:/Users/User/Desktop/compilerProject/text.txt", "r");
	if (file == NULL)
	{
		printf("error in the file text.txt \n");
		exit(1);
	}

	tav = fgetc(file);
	while (tav != EOF)
	{

		size++;
		for (int i = 0, j = 0; i < specialTavArr; i++)

			if (characters[i] == tav)
			{


				if (size != 0) {
					word = realloc(word, size + 1);
					word[size] = '\0';
					overTheWord(word);

					word = NULL;
				}
				while (tav != ' ' && i < row && j < column)
				{
					if (characters[j] == peek(file)) {
						word = realloc(word, 2);
						word[0] = tav;
						word[1] = fgetc(file);

						MyListOfTokens(word, dataArray[mat[i][j]].str, dataArray[mat[i][j]].num);
						word = NULL;
						degel = 1;
					}

					j++;
				}

				if (!degel)
					overTheWord(&tav);

				size = 0;
			}


		if (size)
		{
			word = realloc(word, size);
			word[size - 1] = tav;

		}

		tav = fgetc(file);
	}
	if (word) {
		word = realloc(word, size + 1);
		word[size] = '\0';
		overTheWord(word);
		free(word);
	}
	fclose(file);

	free(word);
	// משתמשת בזה בתחביריfree(headList);
	MyListOfTokens('$', "dollar", dollarValue);

}











