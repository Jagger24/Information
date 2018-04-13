
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
