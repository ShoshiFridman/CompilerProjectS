#pragma once


typedef struct Token {
	char* value;
	char* nameToken;
	int index;
	struct Token* next;
	struct Token* prev;


}Token;


Token* tokenPtr;
//Token** headList;
Token* headList;
Token* tailList ;

void lexicalAnalysis();

