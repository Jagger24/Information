
#include "ciphers.h"

const char* CharMap = \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int LowercaseIndex = 0;
const int UppercaseIndex = 26;
const int NumIndex 	= 52;
const int CharMapSize	= 62;

const char* BlockCharMap = \
	"bnztFRL0WgamysEQKV19fhlxrDPJU28eqkwICOZT37dpjvHBNYS46coiuGAMX5";

char num_to_letter(int num)
{
	return CharMap[num];
}

int letter_to_num(char letter)
{
	int num = 0;
	while (CharMap[num] != letter)
	{
		num++;
	}
	return num;
}
