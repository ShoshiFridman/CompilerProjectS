#pragma once


#define CELLS	115

typedef struct Deduction
{
	char deduct[15];
	int valueNumber;
	int numToCut;

}Deduction;

Deduction deductions[CELLS]; // Assuming a maximum of 115 rows

void CFG();
