
#include <stdio.h>
#include <stdlib.h>

#include "lexicaly.h"
#include "Stack.h"
#include "mystring.h"



#define MAX_LINES_NUM 20 // Maximum number of lines to read
#define MAX_STR_SIZE  50 // Maximum size for the string

#define NO_ERROR 0
#define specialTavArr 24
#define sizeOfNameTOK_OP 10
#define row 12
#define column 12
#define dollarValue 58

#define DEGEL 0
#define NUM_STATES 210
#define GARBAGE 0xcdcdcdcdcdcdcdcd

#define END_STATE_SIZE 40
#define SIZET 25

typedef struct EndState
{
	int numToken;
	char nameToken1[SIZET];
	int num;
	struct EndState* next;
} EndState;

EndState* pointer;
EndState* end_states_arr[END_STATE_SIZE] = { NULL };
FILE* fileTokens = NULL;

int x = NO_ERROR;

//����� ���� ������
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
};	struct Data dataArray[MAX_LINES_NUM];

int mat[row][column];


Token* token1;

char characters[specialTavArr];


int automate()
{//����� ���� �������

	FILE* fileStates = NULL;
	int index;

	errno_t er = fopen_s(&fileStates, "C:/Users/User/Desktop/compilerProject/state.txt", "r");

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

	while (fscanf(fileStates, "%d %c %d", &index, &(cs.letter), &(cs.nextIndex)) != EOF)
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

//������� ������ ����� �� ������ 

void MyListOfTokens(char* value1, char* nameTokenn, int index) {
	FILE* writeFile = NULL;

	// Allocate memory for the new token
	Token* newToken = malloc(sizeof(Token));
	if (newToken == NULL) {
		printf("Error allocating memory for newToken\n");
		exit(1);
	}

	// Fill in the new token data
	newToken->value = malloc(myStrlen(value1));
	myStrcpy(newToken->value, value1);
	newToken->nameToken = malloc(myStrlen(nameTokenn));
	myStrcpy(newToken->nameToken, nameTokenn);
	newToken->index = index;
	newToken->next = NULL;

	// If the list is empty, set the new token as both head and tail
	if (headList == NULL||headList->value==GARBAGE) {
		headList = newToken;
		tailList = newToken;
		newToken->prev = NULL;
	}
	else {
		// Add the new token to the end of the list
		if (tailList != NULL) {
			tailList->next = newToken;
		}
		newToken->prev = tailList;
		tailList = newToken;
	}

	// Opening the target file for writing
	errno_t er = fopen_s(&writeFile, "C:/Users/User/Desktop/compilerProject/myTokens.txt", "a");
	if (writeFile == NULL) {
		printf("error in the file tokens.txt \n");
		exit(1);
	}

	// Writing the token data to the file
	fprintf(writeFile, " %s %s \n", value1, nameTokenn);
	fclose(writeFile);
}
int hashFunction(int x)
{
	return x % END_STATE_SIZE;
}

// ������ ��� ����� ������ ����� ������ ������� �� ����� ������ ����� ���������������
int findToken(int* state, char* word)
{
	
	// ����� ����� ����� ������� �� ���� �� �� �����
	int i = hashFunction(*state);
	EndState * ptr= end_states_arr[i];
	while (ptr != NULL)
	{
		x = ptr->numToken;
		if (x == *state)
		{
			MyListOfTokens(word, ptr->nameToken1,ptr->num);
			return 1;
		}
		ptr = ptr->next;
	}

	return 0;
}

//������� ���� �� ������� ��� ����� �������
void overTheWord(char* word)
{
	int i = 0, w = DEGEL, degel = DEGEL, j;
	
	while (cs.nextIndex <= NUM_STATES && cs.nextIndex >= 0 && word[w] != '\0')

	{
		cs = *currentStateArr[i];
		while (cs.csptr != NULL && ((int)cs.letter != (int)word[w]) && !degel)
		{
			if (cs.letter < 0)
				degel = 1;
			else
			cs = *(cs.csptr);

		}

		w++;
		j = i;

		i = cs.nextIndex;
		if (cs.nextIndex != -999)
			j = cs.nextIndex;
	}
	cs.nextIndex = 0;
	if (((int)cs.letter == (int)word[w - 1]))
		//����� ����� ����� ������ �� ����� ���� ����
		degel = findToken(&j, &word[0]);
	if (!degel || ((int)cs.letter != (int)word[w - 1]))
	{
		MyListOfTokens(word, "TOK_ID", DEGEL);
		return;
	}
}

//void fillMat()
//{
//	FILE* file = NULL;
//
//	//����� ������ ���� ����� �� ������� �������� �� �� ������� �2 ����� ���� ������ ����� ������
//	int num;
//	int rows = 0, cols;
//	errno_t er = fopen_s(&file, "C:/Users/User/Desktop/compilerProject/mat.txt", "r");
//	if (file == NULL)
//	{
//		printf("error in the file mat.txt \n");
//		exit(1);
//	}
//	while (fscanf(file, "%d", &num) == 1 && rows < row) {
//		cols = 0;
//		mat[rows][cols] = num;
//		cols++;
//
//		// Continue reading numbers from the same row
//		while (fscanf(file, "%d", &num) == 1 && cols < column) {
//			mat[rows][cols] = num;
//			cols++;
//		}
//
//		rows++;
//	}
//
//	fclose(file); // Close the file
//}
void fillMat() {
	FILE* file = NULL;
	int num;
	int rows = 0, cols = 0;

	errno_t er = fopen_s(&file, "C:/Users/User/Desktop/compilerProject/mat.txt", "r");
	if (file == NULL) {
		printf("error in the file mat.txt \n");
		exit(1);
	}

	// ����� �� ������� ������
	while (fscanf(file, "%d", &num) == 1) {
		mat[rows][cols] = num;
		cols++;

		// ����� ��' ������� ����� �����
		if (cols == column) {
			rows++;
			cols = 0;
		}
	}

	fclose(file); // ����� �����
}
void fillSpecialTavArr()
{
	FILE* file = NULL;
	int index = 0;

	errno_t er = fopen_s(&file, "C:/Users/User/Desktop/compilerProject/specialTavs.txt", "r"); // Open the file in read mode

	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}

	// Read characters from the file and store them in the array
	while ((characters[index] = fgetc(file)) != EOF && index < specialTavArr) {
		index++;
	}

	characters[index - 1] = '\0'; // Add null terminator at the end

	fclose(file); // Close the file

}
void fillDuplicateTavs() {


	FILE* file = NULL;
	int index = 0;

	errno_t er = fopen_s(&file, "C:/Users/User/Desktop/compilerProject/duplicateCharacters.txt", "r"); // Open the file in read mode

	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}

	// Read values from the file and store them in the array of structures
	while (fscanf(file, "%s %d", dataArray[index].str, &dataArray[index].num) == 2 && index < MAX_LINES_NUM) {
		index++;
	}

	fclose(file); // Close the file

}



void FillEndStatesArr() {
	struct EndState endState;

	errno_t er = fopen_s(&fileTokens, "C:/Users/User/Desktop/compilerProject/newTokens.txt", "r");
	if (fileTokens == NULL)
	{
		printf("error in the file tokens.txt \n");
		exit(1);
	}

	while (fscanf(fileTokens, "%d %s %d", &(endState.numToken), endState.nameToken1, &(endState.num)) != EOF && x <= END_STATE_SIZE)

	{
		endState.next = NULL;
		x = hashFunction(endState.numToken);

		if (end_states_arr[x] == NULL)
		{
			//end_states_arr[x] = &endState;
			end_states_arr[x] = malloc(sizeof(EndState));
			end_states_arr[x]->numToken = endState.numToken;
			end_states_arr[x]->num = endState.num;
			end_states_arr[x]->next = NULL;
			myStrcpy(end_states_arr[x]->nameToken1, endState.nameToken1);


		}
		else
		{
			pointer = end_states_arr[x];
			while (pointer->next != NULL)
			{
				pointer = pointer->next;
			}
			pointer->next = malloc(sizeof(EndState));

			pointer->next->numToken = endState.numToken;
			pointer->next->num = endState.num;
			pointer->next->next = NULL;
			myStrcpy(end_states_arr[x]->next->nameToken1, endState.nameToken1);

		}
		
	}
	fclose(fileTokens);
	//free(end_states_arr);
}


void* RealocAndOverwrite(void* address, size_t new_size)
{
	size_t old_size = new_size - 1;
	void* buffer = malloc(old_size);
	memcpy(buffer, address, old_size * sizeof(char));
	address = realloc(address, new_size);
	memcpy(address, buffer, old_size * sizeof(char));
}


//������� ����� ������ ������ ��������
void lexicalAnalysis()
{

	int degel = NO_ERROR, sign = NO_ERROR;

	FILE* file = NULL;

	automate();
	FillEndStatesArr();

	fillMat();
	fillSpecialTavArr();
	fillDuplicateTavs();

	FILE* writeFile = NULL;
	errno_t er1 = fopen_s(&writeFile, "C:/Users/User/Desktop/compilerProject/myTokens.txt", "wt");

	if (writeFile == NULL)
	{
		printf("error in the file tokens.txt \n");
		exit(1);
	}
	fprintf(writeFile, "");

	fclose(writeFile);
	char tav, nextTav;
	int size = NO_ERROR;

	char* word = malloc(size);
	if (word == NULL) {
		perror("Error allocating memory");
		return;
	}
	headList = malloc(sizeof(Token*));
	if (headList == NULL) {
		perror("Error allocating memory");
		return;
	}

	errno_t er = fopen_s(&file, "C:\\Users\\User\\Desktop\\compilerProject\\text.txt", "r");
	if (file == NULL)
	{
		printf("error in the file text.txt \n");
		exit(1);
	}
	tav = fgetc(file);
	while (tav != EOF && tav > 0)
	{

		size++;
		for (int i = 0, j = 0; i < specialTavArr; i++)

			if (characters[i] == tav || tav == ' ' || tav == '\n')
			{

				if (size > 1) {
					word = RealocAndOverwrite(word, size);
					word[size - 1] = '\0';
					overTheWord(word);
					degel = DEGEL;
					word = NULL;
				}
				if (size == 1)
				{
					degel = DEGEL;
				}
				if (tav == ' ' || tav == '\n')
				{
					degel = 1;
					i = specialTavArr;
				}
				nextTav = fgetc(file);

				while (tav != ' ' && tav != '\n' && i < row && j < column && sign != 2)
				{
					sign = 1;

					if (characters[j] == nextTav)
					{
						char tavWord[2];
						tavWord[0] = tav;
						tavWord[1] = nextTav;

						MyListOfTokens(tavWord, dataArray[mat[i][j]].str, dataArray[mat[i][j]].num);

						degel = 1;
						sign = 2;
					}
					/*else
						ungetc(characters[j], file);*/

					j++;
				}
				
				if (nextTav != EOF && nextTav > 0 && sign != 2)
					fseek(file, -1, SEEK_CUR);
				sign = NO_ERROR;

				if (!degel)
				{
					char tavWord[2];
					tavWord[0] = tav;
					tavWord[1] = '\0';
					overTheWord(tavWord);
				}

				size = 0;
			}


		if (size)
		{
			word = RealocAndOverwrite(word, size);
			word[size - 1] = tav;

		}
		tav = fgetc(file);
	}
	
		free(word);

	fclose(file);

	// ������ ��� �������free(headList);
	MyListOfTokens((char*)"$", (char*)"dollar", dollarValue);
}
