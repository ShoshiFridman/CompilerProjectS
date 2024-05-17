//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include "mystring.c"
//#define GARBAGE 0xcdcdcdcdcdcdcdcd
//
//#define END_STATE_SIZE 60
//#define NO_ERROR 0
//#define SIZET 15
//
//
//
//typedef struct EndState
//{
//	int numToken;
//	char nameToken[SIZET];
//	int num;
//	struct EndState* next;
//
//
//};
//struct EndState* pointer;
//struct EndState* end_states_arr[END_STATE_SIZE];
//FILE* fileTokens = NULL;
//
//int x = NO_ERROR;
//
//
////פונקציה שממלאת את מערך המצבים הסופיים
//int FillEndStatesArr() {
//	struct EndState endState;
//
//	errno_t er = fopen_s(fileTokens, "C:/Users/User/Desktop/compilerProject/newTokens.txt", "r");
//	if (fileTokens == NULL)
//	{
//		printf("error in the file tokens.txt \n");
//		exit(1);
//	}
//
//	while (fscanf_s(fileTokens, "%d %s %d", &(endState.numToken), endState.nameToken, &(endState.num)) != EOF && x <= END_STATE_SIZE)
//
//	{
//		x = endState.numToken % END_STATE_SIZE;
//		if (end_states_arr[x] != NULL)
//		{
//			end_states_arr[x] = malloc(sizeof(struct EndState));
//			end_states_arr[x]->numToken = endState.numToken;
//			end_states_arr[x]->next = endState.next;
//			myStrcpy(end_states_arr[x]->nameToken, endState.nameToken);
//			end_states_arr[x]->num = endState.num;
//		}
//		else {
//			pointer = end_states_arr[x];
//			while (pointer->next != NULL && pointer->next != GARBAGE)
//				pointer = pointer->next;
//
//			end_states_arr[x]->next = malloc(sizeof(struct EndState));
//			end_states_arr[x]->next->numToken = endState.numToken;
//			end_states_arr[x]->next->next = NULL;
//			myStrcpy(end_states_arr[x]->next->nameToken, endState.nameToken);
//			end_states_arr[x]->next->num = endState.num;
//		}
//
//
//
//	}
//	fclose(fileTokens);
//	//free(end_states_arr);
//	return NO_ERROR;
//}
//
////פונקציה שמקבלת מצב ומילה ומחפשת במערך המצבים הסופיים את הטוקן שמתאים למילה הספציפית
//int findToken(int* state, char* word)
//{
//	// שימוש בטבלת גיבוב וחיסכון של מעבר על כל המערך
//	int i = *state % END_STATE_SIZE;
//	while (end_states_arr[i]->next != NULL)
//	{
//		x = end_states_arr[i]->numToken;
//		if (x == *state)
//		{
//			MyListOfTokens(word, end_states_arr[i]->nameToken, end_states_arr[i]->num);
//
//			return 1;
//		}
//	}
//
//
//
//
//	return 0;
//}
//
//
