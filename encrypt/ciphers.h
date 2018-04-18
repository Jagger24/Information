/*
 * Evan Adamic, Rebecca Hu, Jeffrey Jagger, 
 * 	Abdikarim Mohamed, Catherine Wang
 * CSE 4471
 * Last update: 4/17/18
 */


#ifndef CIPHERS_H_
#define CIPHERS_H_

const char* BlockCharMap;
const char* CharMap;

const int LowercaseIndex;
const int UppercaseIndex;
const int NumIndex;
const int CharMapSize;


char num_to_letter(int num);
int letter_to_num(char letter);

#endif
