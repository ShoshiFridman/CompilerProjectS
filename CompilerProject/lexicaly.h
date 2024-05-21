#pragma once


typedef struct Token {
	char* value;
	char* nameToken;
	int index;
	struct Token* next;

}Token;


Token* tokenPtr;
Token** headList;
void lexicalAnalysis();

