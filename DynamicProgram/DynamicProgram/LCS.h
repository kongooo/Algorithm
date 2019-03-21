#pragma once

#define A_LENGTH 17
#define B_LENGTH 17

typedef int** Array;
typedef char* string;

Array getLength(string a, string b, int an, int bn);
string getString(Array c, string a, string b, int an, int bn);
void printStr(string temp, int length);
void printArray(Array A, int y, int x);
void LCS_test();

